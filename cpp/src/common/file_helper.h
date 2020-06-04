#ifndef _COMMON_FILE_HELPER_H_
#define _COMMON_FILE_HELPER_H_

#include <memory>
#include <string>
#include <map>
#include "Eigen/Dense"
#include "primitive/surface_primitive.h"
#include "csg/csg_node.h"
#include "mesh/level_set_helper.h"

namespace common {

const bool HasExtension(const std::string& file_name,
  const std::string& extension);
const bool IsEmptyLine(const std::string& line,
  const std::string& white_space);
const std::string StripLine(const std::string& line);
// Eigen matrix file IO.
const Eigen::MatrixXd ReadMatrixFromBinaryFile(const std::string& file_name);
void WriteMatrixToBinaryFile(const Eigen::MatrixXd& A,
  const std::string& file_name);

// PRIM file.
void ReadPrimFile(const std::string& file_name,
  std::vector<std::shared_ptr<primitive::SurfacePrimitive>>& primitives);
void WritePrimFile(
  const std::vector<std::shared_ptr<primitive::SurfacePrimitive>>& primitives,
  const std::string& file_name);
// META file.
void ReadMetaFile(const std::string& file_name,
  std::vector<std::pair<Eigen::Vector3d, int>>& points);
void WriteMetaFile(const std::vector<std::pair<Eigen::Vector3d, int>>& points,
  const std::string& file_name);
// DATA file.
void ReadDataFile(const std::string& file_name,
  std::vector<Eigen::Vector3d>& points);
void WriteDataFile(const std::vector<Eigen::Vector3d>& points,
  const std::string& file_name);
// SCAD file.
void ReadScadFile(const std::string& file_name,
  std::shared_ptr<csg::CsgNode>& root);
void WriteScadFile(const std::shared_ptr<csg::CsgNode>& root,
  const std::string& file_name);
// LS file.
void ReadLevelSetFile(const std::string& file_name,
  std::shared_ptr<mesh::LevelSetHelper>& level_set);
void WriteLevelSetFile(const mesh::LevelSetHelper& level_set,
  const std::string& file_name);
// OFF file.
void ReadOffFile(const std::string& file_name,
  Eigen::Matrix3Xd& vertices, Eigen::Matrix3Xi& faces);
void WriteOffFile(const Eigen::Matrix3Xd& vertices,
  const Eigen::Matrix3Xi& faces, const std::string& file_name);
void WriteOffFile(const Eigen::Matrix3Xd& vertices,
  const Eigen::Matrix3Xi& faces, const Eigen::Matrix3Xd& face_colors,
  const std::string& file_name);
// CONF file.
void ReadConfFile(const std::string& file_name,
  std::map<std::string, std::string>& kv_pairs);
// Cluster file.
void ReadClusterFile(const std::string& file_name,
  std::vector<std::vector<int>>& clusters);
void WriteClusterFile(const std::vector<std::vector<int>>& clusters,
  const std::string& file_name);

// Replace all '\' with '/'.
const std::string RegularizeFilePath(const std::string& path);
// Concatenate folder and file paths.
const std::string AppendFileToPath(const std::string& folder,
  const std::string& file_name);
const std::string AppendFolderToPath(const std::string& folder,
  const std::string& subfolder);
const std::string GetParentFolder(const std::string path);
void PrepareToCreateFile(const std::string& file_path);
const bool FileExist(const std::string& file_path);

// Colorful print.
const std::string GreenHead();
const std::string RedHead();
const std::string CyanHead();
const std::string GreenTail();
const std::string RedTail();
const std::string CyanTail();
// use return_code = -1 unless you want to customize it.
void PrintError(const std::string& message, const int return_code = -1);
void PrintWarning(const std::string& message);
void PrintSuccess(const std::string& message);

// Render a mesh file using segmentation results.
void VisualizeMeshSegmentation(const mesh::TriMesh& shape,
  const std::vector<std::vector<int>>& clusters,
  const std::string& file_name_prefix, const bool use_color = true);

}

#endif
