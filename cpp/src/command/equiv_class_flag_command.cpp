#include "command/command.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <map>
#include "common/file_helper.h"
#include "common/math_helper.h"
#include "mesh/tri_mesh.h"
#include "mesh/level_set_helper.h"

namespace command {

static void CheckEquivClassFlagCommandFileName(
  const std::string& pos_equiv_file, const std::string& input_data_file,
  const std::string& level_set_file, const std::string& mesh_file,
  const std::string& neg_file, const std::string& pos_file,
  const std::string& prim_file, const std::string& neg_equiv_file) {
  if (!common::HasExtension(pos_equiv_file, ".data")) {
    std::cerr << common::RedHead()
      << "command::CheckEquivClassFlagCommandFileName: wrong data file: "
      << pos_equiv_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(input_data_file, ".data")) {
    std::cerr << common::RedHead()
      << "command::CheckEquivClassFlagCommandFileName: wrong data file: "
      << input_data_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(level_set_file, ".ls")) {
    std::cerr << common::RedHead()
      << "command::CheckEquivClassFlagCommandFileName: wrong level set file: "
      << level_set_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(mesh_file, ".off")) {
    std::cerr << common::RedHead()
      << "command::CheckEquivClassFlagCommandFileName: wrong mesh file: "
      << mesh_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(neg_file, ".data")) {
    std::cerr << common::RedHead()
      << "command::CheckEquivClassFlagCommandFileName: wrong data file: "
      << neg_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(pos_file, ".data")) {
    std::cerr << common::RedHead()
      << "command::CheckEquivClassFlagCommandFileName: wrong data file: "
      << pos_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(prim_file, ".prim")) {
    std::cerr << common::RedHead()
      << "command::CheckEquivClassFlagCommandFileName: wrong prim file: "
      << prim_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(neg_equiv_file, ".data")) {
    std::cerr << common::RedHead()
      << "command::CheckEquivClassFlagCommandFileName: wrong data file: "
      << neg_equiv_file << common::RedTail() << std::endl;
    exit(-1);
  }
}

void EquivClassFlagCommand(const double min_dist,
  const std::string& pos_equiv_file, const bool help,
  const std::string& input_data_file, const std::string& level_set_file,
  const std::string& mesh_file, const std::string& neg_file,
  const std::string& pos_file, const std::string& prim_file,
  const std::string& neg_equiv_file, const bool verbose) {
  if (help) {
    std::cout
      << "equiv-class-flag    Use equivalence classes to classify samples."
      << std::endl
      << "  -d <double>       Minimum distance to the primitives." << std::endl
      << "  -e <DATA file>    Output positive equivalence classes." << std::endl
      << "  -h                Print help information." << std::endl
      << "  -i <DATA file>    Input points." << std::endl
      << "  -l <LS file>      Input levelset file." << std::endl
      << "  -m <OFF file>     Input mesh file." << std::endl
      << "  -n <DATA file>    Output negative points." << std::endl
      << "  -o <DATA file>    Output positive points." << std::endl
      << "  -p <PRIM file>    Input primitive file." << std::endl
      << "  -q <DATA file>    Output negative equivalence classes." << std::endl
      << "  -v                Verbose mode." << std::endl << std::endl
      << "Merge points using primitives and label each equivalence" << std::endl
      << "class with the same inside/outside property."
      << std::endl << std::endl;
    return;
  }

  CheckEquivClassFlagCommandFileName(pos_equiv_file, input_data_file,
    level_set_file, mesh_file, neg_file, pos_file, prim_file, neg_equiv_file);
  // Read mesh.
  mesh::TriMesh shape;
  shape.Initialize(mesh_file);
  // Read level set.
  std::shared_ptr<mesh::LevelSetHelper> level_set = nullptr;
  common::ReadLevelSetFile(level_set_file, level_set);
  // Read data.
  std::vector<Eigen::Vector3d> points(0);
  common::ReadDataFile(input_data_file, points);
  // Read primitives.
  std::vector<std::shared_ptr<primitive::SurfacePrimitive>> primitives(0);
  common::ReadPrimFile(prim_file, primitives);

  // Thanks to C++11 we can use decltype to wrap CompareEigenVectorXi. In this
  // way there is no need to introduce a separate struct.
  auto less = [](const Eigen::VectorXi& a, const Eigen::VectorXi& b) {
    assert(a.size() == b.size());
    for (auto i = 0; i < a.size(); ++i) {
      if (a(i) < b(i)) return true;
      if (a(i) > b(i)) return false;
    }
    return false;
  };
  struct PointInfo {
  public:
    Eigen::Vector3d point;
    bool is_inside;
    double min_dist_to_surface;
  };
  std::map<Eigen::VectorXi, std::vector<PointInfo>, decltype(less)>
    unique_points_map(less);
  const int prim_num = static_cast<int>(primitives.size());
  if (verbose) {
    std::cout << "command::EquivClassFlagCommand: processing " << points.size()
      << " points." << std::endl;
  }
  int verbose_process = 0;
  int cnt = 0;
  const int sample_num = static_cast<int>(points.size());
  for (const auto& p : points) {
    const int process = cnt / (sample_num / 10);
    if (verbose && (process > verbose_process)) {
      verbose_process = process;
      std::cout << "command::EquivClassFlagCommand: " << verbose_process * 10
        << "%..." << std::endl;
    }
    ++cnt;
    // Skip if it is too close to the mesh.
    if (level_set->IsCloseToMesh(p)) continue;
    // Compute its representative.
    Eigen::VectorXi index = Eigen::VectorXi::Zero(prim_num);
    bool too_close = false;
    double min_point_dist = common::Infinity();
    for (int i = 0; i < prim_num; ++i) {
      const auto& surface = primitives[i];
      const double f_val = surface->DistToSurface(p);
      const double f_val_abs = std::fabs(f_val);
      if (f_val_abs <= min_dist) {
        too_close = true;
        if (verbose) {
          std::cout << "command::EquivClassFlagCommand: points too close to the"
            << " surface: " << f_val << ". point = " << p.transpose()
            << ", surface = " << surface->WriteToString() << std::endl;
        }
        break;
      }
      if (f_val_abs < min_point_dist) min_point_dist = f_val_abs;
      if (f_val > 0) index(i) = 1;
    }
    // Skip if it is too close.
    if (too_close) continue;
    const bool is_inside = shape.IsInside(p);
    unique_points_map[index].push_back({ p, is_inside, min_point_dist });
  }

  // Write points back to the file.
  std::vector<Eigen::Vector3d> pos_points, neg_points,
    pos_equiv_points, neg_equiv_points;
  for (const auto& pair: unique_points_map) {
    // Determine whether it should be inside or outside.
    int inside_cnt = 0, outside_cnt = 0;
    for (const auto& p : pair.second) {
      if (p.is_inside) ++inside_cnt;
      else ++outside_cnt;
    }
    if (inside_cnt > outside_cnt) {
      double max_dist = -1.0;
      Eigen::Vector3d max_dist_point(0, 0, 0);
      for (const auto& p : pair.second) {
        pos_points.push_back(p.point);
        if (p.min_dist_to_surface > max_dist) {
          max_dist = p.min_dist_to_surface;
          max_dist_point = p.point;
        }
      }
      pos_equiv_points.push_back(max_dist_point);
    } else {
      double max_dist = -1.0;
      Eigen::Vector3d max_dist_point(0, 0, 0);
      for (const auto& p : pair.second) {
        neg_points.push_back(p.point);
        if (p.min_dist_to_surface > max_dist) {
          max_dist = p.min_dist_to_surface;
          max_dist_point = p.point;
        }
      }
      neg_equiv_points.push_back(max_dist_point);
    }
  }
  common::WriteDataFile(pos_points, pos_file);
  common::WriteDataFile(neg_points, neg_file);
  common::WriteDataFile(pos_equiv_points, pos_equiv_file);
  common::WriteDataFile(neg_equiv_points, neg_equiv_file);
}

}
