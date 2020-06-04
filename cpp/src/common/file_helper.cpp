#include "common/file_helper.h"
#include <iostream>
#include <fstream>
#include <sstream>
#if defined(WIN32) || defined(__WIN32)
#include <windows.h>
#elif defined(__linux__)
#include <sys/stat.h>
#endif
#include "csg/scad_file_parser.h"
#include "primitive/surface_primitive.h"
#include "primitive/plane_surface.h"
#include "primitive/cylindrical_surface.h"
#include "primitive/spherical_surface.h"

namespace common {

const bool HasExtension(const std::string& file_name,
  const std::string& extension) {
  if (file_name.size() < extension.size() + 1u) return false;
  const int ext_size = static_cast<int>(extension.size());
  for (int i = 0; i < ext_size; ++i) {
    char a = file_name[file_name.size() - extension.size() + i];
    char b = extension[i];
    if (a >= 'A' && a <= 'Z') a -= 'A' - 'a';
    if (b >= 'A' && b <= 'Z') b -= 'A' - 'a';
    if (a != b) return false;
  }
  return true;
}

const bool IsEmptyLine(const std::string& line,
  const std::string& white_space) {
  for (const char ch : line) {
    if (white_space.find_first_of(ch) == std::string::npos) return false;
  }
  return true;
}

const std::string StripLine(const std::string& line) {
  const std::string space = "\r\n\t ";
  if (IsEmptyLine(line, space)) return "";
  const int len = static_cast<int>(line.size());
  int i = 0;
  while (space.find_first_of(line[i]) != std::string::npos) ++i;
  int j = len - 1;
  while (space.find_first_of(line[j]) != std::string::npos) --j;
  return line.substr(i, j - i + 1);
}

const Eigen::MatrixXd ReadMatrixFromBinaryFile(const std::string& file_name) {
  if (!FileExist(file_name)) {
    std::cerr << common::RedHead() << "common::ReadMatrixFromBinaryFile: file "
      << file_name << " does not exist."
      << common::RedTail() << std::endl;
    exit(-1);
  }
  std::ifstream fin(file_name, std::ios::in | std::ios::binary);
  int row_num = 0, col_num = 0;
  fin.read(reinterpret_cast<char*>(&row_num), sizeof(int));
  fin.read(reinterpret_cast<char*>(&col_num), sizeof(int));
  Eigen::MatrixXd A(row_num, col_num);
  fin.read(reinterpret_cast<char*>(A.data()),
    row_num * col_num * sizeof(double));
  fin.close();
  return A;
}

void WriteMatrixToBinaryFile(const Eigen::MatrixXd& A,
  const std::string& file_name) {
  PrepareToCreateFile(file_name);
  std::ofstream fout(file_name, std::ios::out | std::ios::binary);
  const int row_num = static_cast<int>(A.rows());
  const int col_num = static_cast<int>(A.cols());
  fout.write(reinterpret_cast<const char*>(&row_num), sizeof(int));
  fout.write(reinterpret_cast<const char*>(&col_num), sizeof(int));
  fout.write(reinterpret_cast<const char*>(A.data()),
    row_num * col_num * sizeof(double));
  fout.close();
}

void ReadPrimFile(const std::string& file_name,
  std::vector<std::shared_ptr<primitive::SurfacePrimitive>>& primitives) {
  if (!HasExtension(file_name, ".prim")) {
    std::cerr << common::RedHead()
      << "common::ReadPrimFile: wrong file extension: " << file_name
      << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!FileExist(file_name)) {
    std::cerr << common::RedHead()
      << "common::ReadPrimFile: file " << file_name << " does not exist."
      << common::RedTail() << std::endl;
    exit(-1);
  }
  std::ifstream prim_fin(file_name);
  std::string line;
  primitives.clear();
  while (std::getline(prim_fin, line)) {
    std::istringstream iss(line);
    std::string type;
    iss >> type;
    for (auto& p : primitive::SurfacePrimitive::primitive_instances) {
      if (p->type_name() == type) {
        std::shared_ptr<primitive::SurfacePrimitive> surface = p->Duplicate();
        surface->ReadFromString(line);
        primitives.push_back(surface);
        break;
      }
    }
  }
  prim_fin.close();
}

void WritePrimFile(
  const std::vector<std::shared_ptr<primitive::SurfacePrimitive>>& primitives,
  const std::string& file_name) {
  if (!HasExtension(file_name, ".prim")) {
    std::cerr << common::RedHead()
      << "common::WritePrimFile: wrong file extension: " << file_name
      << common::RedTail() << std::endl;
    exit(-1);
  }
  PrepareToCreateFile(file_name);
  std::ofstream prim_fout(file_name);
  for (const auto& p : primitives) {
    prim_fout << p->WriteToString() << std::endl;
  }
  prim_fout.close();
}

void ReadMetaFile(const std::string& file_name,
  std::vector<std::pair<Eigen::Vector3d, int>>& points) {
  if (!HasExtension(file_name, ".meta")) {
    std::cerr << common::RedHead()
      << "common::ReadMetaFile: wrong file extension: " << file_name
      << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!FileExist(file_name)) {
    std::cerr << common::RedHead()
      << "common::ReadMetaFile: file " << file_name << " does not exist."
      << common::RedTail() << std::endl;
    exit(-1);
  }
  std::ifstream meta_fin(file_name, std::ios::in | std::ios::binary);
  int number = 0;
  meta_fin.read(reinterpret_cast<char*>(&number), sizeof(int));
  points.resize(number);
  Eigen::Matrix3Xd points_loc(3, number);
  Eigen::VectorXi points_prim_id(number);
  meta_fin.read(reinterpret_cast<char*>(points_loc.data()),
    points_loc.size() * sizeof(double));
  meta_fin.read(reinterpret_cast<char*>(points_prim_id.data()),
    points_prim_id.size() * sizeof(int));
  for (int i = 0; i < number; ++i) {
    points[i].first = points_loc.col(i);
    points[i].second = points_prim_id(i);
  }
  meta_fin.close();
}

void WriteMetaFile(const std::vector<std::pair<Eigen::Vector3d, int>>& points,
  const std::string& file_name) {
  if (!HasExtension(file_name, ".meta")) {
    std::cerr << common::RedHead()
      << "common::WriteMetaFile: wrong file extension: " << file_name
      << common::RedTail() << std::endl;
    exit(-1);
  }
  PrepareToCreateFile(file_name);
  std::ofstream meta_fout(file_name, std::ios::out | std::ios::binary);
  const int number = static_cast<int>(points.size());
  meta_fout.write(reinterpret_cast<const char*>(&number), sizeof(int));
  Eigen::Matrix3Xd point_loc(3, number);
  Eigen::VectorXi point_prim_id(number);
  for (int i = 0; i < number; ++i) {
    point_loc.col(i) = points[i].first;
    point_prim_id(i) = points[i].second;
  }
  meta_fout.write(reinterpret_cast<const char*>(point_loc.data()),
    point_loc.size() * sizeof(double));
  meta_fout.write(reinterpret_cast<const char*>(point_prim_id.data()),
    point_prim_id.size() * sizeof(int));
  meta_fout.close();
}

void ReadDataFile(const std::string& file_name,
  std::vector<Eigen::Vector3d>& points) {
  if (!HasExtension(file_name, ".data")) {
    std::cerr << common::RedHead()
      << "common::ReadDataFile: wrong file extension: " << file_name
      << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!FileExist(file_name)) {
    std::cerr << common::RedHead()
      << "common::ReadDataFile: file " << file_name << " does not exist."
      << common::RedTail() << std::endl;
    exit(-1);
  }
  std::ifstream data_fin(file_name, std::ios::in | std::ios::binary);
  int number = 0;
  data_fin.read(reinterpret_cast<char*>(&number), sizeof(int));
  std::vector<double> points_raw(3 * number, 0.0);
  data_fin.read(reinterpret_cast<char*>(points_raw.data()),
    points_raw.size() * sizeof(double));
  points.resize(number);
  for (int i = 0; i < number; ++i) {
    for (int j = 0; j < 3; ++j) {
      points[i](j) = points_raw[3 * i + j];
    }
  }
  data_fin.close();
}

void WriteDataFile(const std::vector<Eigen::Vector3d>& points,
  const std::string& file_name) {
  if (!HasExtension(file_name, ".data")) {
    std::cerr << common::RedHead()
      << "common::WriteDataFile: wrong file extension: " << file_name
      << common::RedTail() << std::endl;
    exit(-1);
  }
  PrepareToCreateFile(file_name);
  std::ofstream data_fout(file_name, std::ios::out | std::ios::binary);
  const int number = static_cast<int>(points.size());
  data_fout.write(reinterpret_cast<const char*>(&number), sizeof(int));
  std::vector<double> points_raw(3 * number, 0.0);
  for (int i = 0; i < number; ++i) {
    for (int j = 0; j < 3; ++j) {
      points_raw[3 * i + j] = points[i](j);
    }
  }
  data_fout.write(reinterpret_cast<const char*>(points_raw.data()),
    points_raw.size() * sizeof(double));
  data_fout.close();
}

void ReadScadFile(const std::string& file_name,
  std::shared_ptr<csg::CsgNode>& root) {
  if (!HasExtension(file_name, ".scad")) {
    std::cerr << common::RedHead()
      << "common::WriteScadFile: wrong file extension: " << file_name
      << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!FileExist(file_name)) {
    std::cerr << common::RedHead()
      << "common::ReadScadFile: file " << file_name << " does not exist."
      << common::RedTail() << std::endl;
    exit(-1);
  }
  csg::ScadFileParser scad_file_parser(file_name);
  root = scad_file_parser.root();
}

void WriteScadFile(const std::shared_ptr<csg::CsgNode>& root,
  const std::string& file_name) {
  if (!HasExtension(file_name, ".scad")) {
    std::cerr << common::RedHead()
      << "common::WriteScadFile: wrong file extension: " << file_name
      << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!root) {
    std::cerr << common::RedHead()
      << "common::WriteScadFile: null pointer." << common::RedTail()
      << std::endl;
    exit(-1);
  }
  PrepareToCreateFile(file_name);
  std::ofstream scad_out(file_name);
  scad_out << root->WriteToString();
  scad_out.close();
}

void ReadLevelSetFile(const std::string& file_name,
  std::shared_ptr<mesh::LevelSetHelper>& level_set) {
  if (!HasExtension(file_name, ".ls")) {
    std::cerr << common::RedHead()
      << "common::ReadLevelSetFile: wrong file extension: "
      << file_name << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!FileExist(file_name)) {
    std::cerr << common::RedHead()
      << "common::ReadLevelSetFile: file " << file_name << " does not exist."
      << common::RedTail() << std::endl;
    exit(-1);
  }
  std::ifstream ls_fin(file_name, std::ios::in | std::ios::binary);
  Eigen::Vector3d pmin(0, 0, 0);
  ls_fin.read(reinterpret_cast<char*>(pmin.data()), sizeof(double) * 3);
  double grid_size = 0.0;
  ls_fin.read(reinterpret_cast<char*>(&grid_size), sizeof(double));
  Eigen::Vector3i dim(0, 0, 0);
  ls_fin.read(reinterpret_cast<char*>(dim.data()), sizeof(int) * 3);
  int idx_size = 0;
  ls_fin.read(reinterpret_cast<char*>(&idx_size), sizeof(int));
  std::vector<long long int> idx(idx_size, 0);
  ls_fin.read(reinterpret_cast<char*>(idx.data()), sizeof(long long int)
    * idx_size);
  std::unordered_set<long long int> close_grid_idx(idx.begin(), idx.end());
  ls_fin.close();

  level_set = std::make_shared<mesh::LevelSetHelper>(pmin, grid_size, dim,
    close_grid_idx);
}

void WriteLevelSetFile(const mesh::LevelSetHelper& level_set,
  const std::string& file_name) {
  if (!HasExtension(file_name, ".ls")) {
    std::cerr << common::RedHead()
      << "common::WriteLevelSetFile: wrong file extension: "
      << file_name << common::RedTail() << std::endl;
    exit(-1);
  }
  PrepareToCreateFile(file_name);
  std::ofstream ls_fout(file_name, std::ios::out | std::ios::binary);
  const Eigen::Vector3d pmin = level_set.pmin();
  ls_fout.write(reinterpret_cast<const char*>(pmin.data()), sizeof(double) * 3);
  const double grid_size = level_set.grid_size();
  ls_fout.write(reinterpret_cast<const char*>(&grid_size), sizeof(double));
  const Eigen::Vector3i dim = level_set.dim();
  ls_fout.write(reinterpret_cast<const char*>(dim.data()), sizeof(int) * 3);
  const int idx_size = static_cast<int>(level_set.close_grid_idx().size());
  ls_fout.write(reinterpret_cast<const char*>(&idx_size), sizeof(int));
  // Unordered set.
  std::vector<long long int> idx(level_set.close_grid_idx().begin(),
    level_set.close_grid_idx().end());
  ls_fout.write(reinterpret_cast<const char*>(idx.data()),
    sizeof(long long int) * idx_size);
  ls_fout.close();
}

void ReadOffFile(const std::string& file_name,
  Eigen::Matrix3Xd& vertices, Eigen::Matrix3Xi& faces) {
  if (!HasExtension(file_name, ".off")) {
    std::cerr << common::RedHead()
      << "common::ReadOffFile: wrong file extension: "
      << file_name << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!FileExist(file_name)) {
    std::cerr << common::RedHead()
      << "common::ReadOffFile: file " << file_name << " does not exist."
      << common::RedTail() << std::endl;
    exit(-1);
  }
  std::ifstream off_fin(file_name);
  std::string line;
  bool header = false;
  bool metadata_region = false;
  bool vertex_region = false;
  bool face_region = false;
  int vertex_num = 0, face_num = 0;
  vertices = Eigen::Matrix3Xd::Zero(3, 0);
  faces = Eigen::Matrix3Xi::Zero(3, 0);
  int vertex_idx = 0, face_idx = 0;
  while (!off_fin.eof()) {
    std::getline(off_fin, line);
    // Ignore comments.
    if (line[0] == '#') continue;
    // Ignore empty lines.
    if (common::IsEmptyLine(line, " \r\n\t")) continue;
    if (!header) {
      // The first line has to be OFF, otherwise we are in trouble.
      if (line.length() < 3 || line.substr(0, 3) != "OFF") {
        std::cerr << common::RedHead()
          << "mesh::TriMesh: incorrect OFF format: "
          << line << common::RedTail() << std::endl;
        exit(-1);
      }
      header = true;
    } else if (!metadata_region) {
      // Metadata.
      std::istringstream metadata(line);
      metadata >> vertex_num >> face_num;
      if (vertex_num <= 0 || face_num <= 0) {
        // Zero vertex.
        std::cerr << common::RedHead()
          << "mesh::TriMesh: incorrect OFF format: " << line
          << common::RedTail() << std::endl;
        exit(-1);
      }
      vertices = Eigen::Matrix3Xd::Zero(3, vertex_num);
      faces = Eigen::Matrix3Xi::Zero(3, face_num);
      metadata_region = true;
    } else if (!vertex_region) {
      // Read vertex info.
      std::istringstream vertex_data(line);
      vertex_data >> vertices(0, vertex_idx) >> vertices(1, vertex_idx)
        >> vertices(2, vertex_idx);
      ++vertex_idx;
      if (vertex_idx == vertex_num) vertex_region = true;
    } else if (!face_region) {
      // Read face info.
      std::istringstream face_data(line);
      int n;
      face_data >> n;
      if (n != 3) {
        std::cerr << common::RedHead()
          << "mesh::TriMesh: expect to see a triangle: " << line
          << common::RedTail() << std::endl;
        exit(-1);
      }
      face_data >> faces(0, face_idx) >> faces(1, face_idx)
        >> faces(2, face_idx);
      ++face_idx;
      if (face_idx == face_num) face_region = true;
    }
  }
  off_fin.close();
}

void WriteOffFile(const Eigen::Matrix3Xd& vertices,
  const Eigen::Matrix3Xi& faces, const std::string& file_name) {
  if (!HasExtension(file_name, ".off")) {
    std::cerr << common::RedHead()
      << "common::WriteOffFile: wrong file extension: "
      << file_name << common::RedTail() << std::endl;
    exit(-1);
  }
  PrepareToCreateFile(file_name);
  std::ofstream off_fout(file_name);
  off_fout << "OFF" << std::endl;
  off_fout << vertices.cols() << " " << faces.cols() << " 0" << std::endl;
  for (auto i = 0; i < vertices.cols(); ++i) {
    off_fout << vertices(0, i) << " " << vertices(1, i) << " "
      << vertices(2, i) << std::endl;
  }
  for (auto i = 0; i < faces.cols(); ++i) {
    off_fout << "3 " << faces(0, i) << " " << faces(1, i) << " "
      << faces(2, i) << std::endl;
  }
  off_fout.close();
}

void WriteOffFile(const Eigen::Matrix3Xd& vertices,
  const Eigen::Matrix3Xi& faces, const Eigen::Matrix3Xd& face_colors,
  const std::string& file_name) {
  if (!HasExtension(file_name, ".off")) {
    std::cerr << common::RedHead()
      << "common::WriteOffFile: wrong file extension: "
      << file_name << common::RedTail() << std::endl;
    exit(-1);
  }
  PrepareToCreateFile(file_name);
  std::ofstream off_fout(file_name);
  off_fout << "OFF" << std::endl;
  off_fout << vertices.cols() << " " << faces.cols() << " 0" << std::endl;
  for (auto i = 0; i < vertices.cols(); ++i) {
    off_fout << vertices(0, i) << " " << vertices(1, i) << " "
      << vertices(2, i) << std::endl;
  }
  for (auto i = 0; i < faces.cols(); ++i) {
    const Eigen::Vector3i int_color = (face_colors.col(i) * 255.0).cast<int>()
      .cwiseMin(255).cwiseMax(0);
    off_fout << "3 " << faces(0, i) << " " << faces(1, i) << " "
      << faces(2, i) << " " << int_color.x() << " "
      << int_color.y() << " " << int_color.z() << std::endl;
  }
  off_fout.close();
}

void ReadConfFile(const std::string& file_name,
  std::map<std::string, std::string>& kv_pairs) {
  if (!HasExtension(file_name, ".conf")) {
    std::cerr << common::RedHead()
      << "common::ReadConfFile: wrong file extension: "
      << file_name << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!FileExist(file_name)) {
    std::cerr << common::RedHead()
      << "common::ReadConfFile: file " << file_name << " does not exist."
      << common::RedTail() << std::endl;
    exit(-1);
  }
  // Each line represents a (key, value) pair, split by a colon.
  std::string line = "";
  std::ifstream conf_in(file_name);
  kv_pairs.clear();
  while (std::getline(conf_in, line)) {
    const auto pos = line.find_first_of(":");
    if (pos == std::string::npos) {
      std::cerr << common::RedHead()
        << "common::ReadConfFile: invalid key value pairs: " << line
        << common::RedTail() << std::endl;
      exit(-1);
    }
    const std::string key = line.substr(0, pos);
    const std::string value = line.substr(pos + 1);
    // Strip key and value.
    kv_pairs[StripLine(key)] = StripLine(value);
  }
}

void ReadClusterFile(const std::string& file_name,
  std::vector<std::vector<int>>& clusters) {
  if (!HasExtension(file_name, ".clu")) {
    std::cerr << common::RedHead()
      << "common::ReadClusterFile: wrong file extension: "
      << file_name << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!FileExist(file_name)) {
    std::cerr << common::RedHead()
      << "common::ReadClusterFile: file " << file_name << " does not exist."
      << common::RedTail() << std::endl;
    exit(-1);
  }
  int cluster_num = 0;
  std::ifstream clu_fin(file_name, std::ios::in | std::ios::binary);
  clu_fin.read(reinterpret_cast<char*>(&cluster_num), sizeof(int));
  clusters.clear();
  clusters.reserve(cluster_num);
  for (int i = 0; i < cluster_num; ++i) {
    int num = 0;
    clu_fin.read(reinterpret_cast<char*>(&num), sizeof(int));
    std::vector<int> cluster(num, 0);
    clu_fin.read(reinterpret_cast<char*>(cluster.data()), num * sizeof(int));
    clusters.push_back(cluster);
  }
}

void WriteClusterFile(const std::vector<std::vector<int>>& clusters,
  const std::string& file_name) {
  if (!HasExtension(file_name, ".clu")) {
    std::cerr << common::RedHead()
      << "common::WriteClusterFile: wrong file extension: "
      << file_name << common::RedTail() << std::endl;
    exit(-1);
  }
  PrepareToCreateFile(file_name);
  // Binary file. First integer is clusters.size(), then for each cluster, it
  // starts with clusters[i].size(), then all integers in clusters[i].
  std::ofstream clu_fout(file_name, std::ios::out | std::ios::binary);
  const int cluster_num = static_cast<int>(clusters.size());
  clu_fout.write(reinterpret_cast<const char*>(&cluster_num), sizeof(int));
  for (const auto& cluster : clusters) {
    const int num = static_cast<int>(cluster.size());
    clu_fout.write(reinterpret_cast<const char*>(&num), sizeof(int));
    clu_fout.write(reinterpret_cast<const char*>(cluster.data()),
      num * sizeof(int));
  }
}

const std::string RegularizeFilePath(const std::string& path) {
  std::string new_path = "";
  bool in_slash = false;
  for (const char ch : path) {
    const bool is_slash = (ch == '\\' || ch == '/');
    if (!is_slash) {
      new_path += ch;
      in_slash = false;
    } else if (!in_slash) {
      new_path += '/';
      in_slash = true;
    }
  }
  return new_path;
}

const std::string AppendFileToPath(const std::string& folder,
  const std::string& file_name) {
  return RegularizeFilePath(folder + "/" + file_name);
}

const std::string AppendFolderToPath(const std::string& folder,
  const std::string& subfolder) {
  return RegularizeFilePath(folder + "/" + subfolder);
}

const std::string GetParentFolder(const std::string path) {
  std::string reg_path = RegularizeFilePath(path);
  // Stop if it is already the root.
  if (reg_path == "/") return reg_path;
  // Ignore the trailing slash.
  if (reg_path.back() == '/')
    reg_path = reg_path.substr(0, reg_path.size() - 1);
  const auto idx = reg_path.find_last_of('/');
  if (idx == std::string::npos) return "./";
  else return reg_path.substr(0, idx);
}

void PrepareToCreateFile(const std::string& file_path) {
  const std::string reg_file_path = RegularizeFilePath(file_path);
  const std::size_t found = reg_file_path.rfind("/");
#if defined(WIN32) || defined(__WIN32)
  if (found != std::string::npos) {
    // Create folder.
    const std::string folder_name = reg_file_path.substr(0, found);
    DWORD attr = GetFileAttributes(folder_name.c_str());
    bool have_folder = (attr != -1) && (attr & FILE_ATTRIBUTE_DIRECTORY);
    if (!have_folder) {
      size_t pos = 0;
      do {
        pos = folder_name.find_first_of('/', pos + 1);
        attr = GetFileAttributes(folder_name.substr(0, pos).c_str());
        have_folder = (attr != -1) && (attr & FILE_ATTRIBUTE_DIRECTORY);
        if (!have_folder) {
          if (!CreateDirectory(folder_name.substr(0, pos).c_str(), NULL) &&
            ERROR_ALREADY_EXISTS != GetLastError()) {
            return;
          }
        }
      } while (pos != std::string::npos);
    }
  }
#elif defined(__linux__)
  if (found != std::string::npos) {
    const std::string folder_name = reg_file_path.substr(0, found + 1);
    size_t pos = 0;
    do {
      pos = folder_name.find_first_of('/', pos + 1);
      mkdir(folder_name.substr(0, pos).c_str(), S_IRWXU);
    } while (pos != std::string::npos);
  }
#else
  common::PrintError("common::PrepareToCreateFile: unsupported platform.");
#endif
  std::ofstream fout(reg_file_path, std::ios::out);
  if (!fout.is_open()) {
    std::cerr << common::RedHead()
      << "common::PrepareToCreateFile: did not create file " << reg_file_path
      << " successfully." << common::RedTail() << std::endl;
    exit(-1);
  }
  fout.close();
}

const bool FileExist(const std::string& file_path) {
  std::ifstream fin;
  fin.open(file_path);
  const bool exists = fin.good();
  fin.close();
  return exists;
}

const std::string GreenHead() {
  return "\x1b[6;30;42m";
}

const std::string RedHead() {
  return "\x1b[6;30;41m";
}

const std::string CyanHead() {
  return "\x1b[6;30;46m";
}

const std::string GreenTail() {
  return "\x1b[0m";
}

const std::string RedTail() {
  return "\x1b[0m";
}

const std::string CyanTail() {
  return "\x1b[0m";
}

void PrintError(const std::string& message, const int return_code) {
  std::cerr << common::RedHead() << message << common::RedTail() << std::endl;
  throw return_code;
}

void PrintWarning(const std::string& message) {
  std::cout << common::CyanHead() << message << common::CyanTail() << std::endl;
}

void PrintSuccess(const std::string& message) {
  std::cout << common::GreenHead() << message << common::GreenTail()
    << std::endl;
}

void VisualizeMeshSegmentation(const mesh::TriMesh& shape,
  const std::vector<std::vector<int>>& clusters,
  const std::string& file_name_prefix, const bool use_color) {
  if (use_color) {
    // Write all segments into a single file but use different colors to
    // distinguish them.
    const std::string file_name = file_name_prefix + ".off";
    std::vector<int> face_raw(0);
    std::vector<double> face_color_raw(0);
    for (const auto& cluster : clusters) {
      const Eigen::Vector3d color =
        Eigen::Vector3d::Random().array() * 0.5 + 0.5;
      for (const int idx : cluster) {
        const Eigen::Vector3i fid = shape.face(idx);
        for (int i = 0; i < 3; ++i) {
          face_raw.push_back(fid(i));
          face_color_raw.push_back(color(i));
        }
      }
    }
    const Eigen::Matrix3Xi face = Eigen::Map<Eigen::Matrix3Xi>(face_raw.data(),
      3, face_raw.size() / 3u);
    const Eigen::Matrix3Xd color = Eigen::Map<Eigen::Matrix3Xd>(
      face_color_raw.data(), 3, face_color_raw.size() / 3u);
    common::WriteOffFile(shape.vertices(), face, color, file_name);
  } else {
    // Write each segment into a separate file.
    const int clusters_size = static_cast<int>(clusters.size());
    for (int i = 0; i < clusters_size; ++i) {
      const std::string file_name = file_name_prefix + "_" + std::to_string(i)
        + ".off";
      Eigen::Matrix3Xi face(3, clusters[i].size());
      const int num = static_cast<int>(clusters[i].size());
      for (int j = 0; j < num; ++j) {
        face.col(j) = shape.face(clusters[i][j]);
      }
      common::WriteOffFile(shape.vertices(), face, file_name);
    }
  }
}

}
