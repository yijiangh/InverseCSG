#include "command/command.h"
#include <iostream>
#include <memory>
#include "common/file_helper.h"
#include "common/math_helper.h"
#include "mesh/tri_mesh.h"
#include "mesh/level_set_helper.h"

namespace command {

static void CheckMeshFlagCommandFileName(const std::string& input_data_file,
  const std::string& mesh_file, const std::string& level_set_file,
  const std::string& output_negative_data_file,
  const std::string& output_positive_data_file) {
  if (!common::HasExtension(input_data_file, ".data")) {
    std::cerr << common::RedHead()
      << "command::CheckMeshFlagCommandFileName: wrong data file: "
      << input_data_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(mesh_file, ".off")) {
    std::cerr << common::RedHead()
      << "command::CheckMeshFlagCommandFileName: wrong mesh file: "
      << mesh_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(level_set_file, ".ls")) {
    std::cerr << common::RedHead()
      << "command::CheckMeshFlagCommandFileName: wrong level-set file:"
      << " " << level_set_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(output_negative_data_file, ".data")) {
    std::cerr << common::RedHead()
      << "command::CheckMeshFlagCommandFileName: "
      << "wrong negative data file: " << output_negative_data_file
      << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(output_positive_data_file, ".data")) {
    std::cerr << common::RedHead()
      << "command::CheckMeshFlagCommandFileName: "
      << "wrong positive data file: " << output_positive_data_file
      << common::RedTail() << std::endl;
    exit(-1);
  }
}

void MeshFlagCommand(const std::string& input_data_file, const double min_dist,
  const bool help, const std::string& mesh_file,
  const std::string& level_set_file,
  const std::string& output_negative_data_file,
  const std::string& output_positive_data_file,
  const bool verbose) {
  // Print help information.
  if (help) {
    std::cout
      << "mesh-flag           Check if points are inside mesh or not."
      << std::endl
      << "  -d <DATA file>    Input data file." << std::endl
      << "  -e <double>       Minimum distance to the mesh." << std::endl
      << "  -h                Print help information." << std::endl
      << "  -i <OFF file>     Input triangle mesh." << std::endl
      << "  -l <LS file>      Input level-set file." << std::endl
      << "  -n <DATA file>    Output data file with negative points." << std::endl
      << "  -p <DATA file>    Output data file with positive points." << std::endl
      << "  -v                Verbose mode." << std::endl << std::endl
      << "Given a mesh file, find all the positive and negative" << std::endl
      << "points in the provided point sets. Points are positive" << std::endl
      << "if and only if it is inside the csg." << std::endl << std::endl
      << "If a point is too close to the csg, this command skips" << std::endl
      << "that point." << std::endl;
    return;
  }
  // Sanity check.
  CheckMeshFlagCommandFileName(input_data_file, mesh_file, level_set_file,
    output_negative_data_file, output_positive_data_file);
  if (min_dist <= 0.0) {
    std::cerr << common::RedHead()
      << "command::MeshFlagCommand: wrong min_dist: " << min_dist
      << common::RedTail() << std::endl;
    exit(-1);
  }

  // Read mesh.
  mesh::TriMesh shape;
  shape.Initialize(mesh_file);

  // Read level set.
  std::shared_ptr<mesh::LevelSetHelper> level_set = nullptr;
  common::ReadLevelSetFile(level_set_file, level_set);
  if (level_set->grid_size() < min_dist) {
    std::cerr << common::RedHead()
      << "command::MeshFlagCommand: level-set grid size ("
      << level_set->grid_size() << ") too small. Should be at least the same as"
      << " min_dist (" << min_dist << ")." << common::RedTail() << std::endl;
    exit(-1);
  }

  // Read points.
  std::vector<Eigen::Vector3d> points(0);
  common::ReadDataFile(input_data_file, points);

  // Filter out points.
  std::vector<Eigen::Vector3d> inside_points(0), outside_points(0);
  inside_points.reserve(points.size());
  outside_points.reserve(points.size());
  for (const auto& p : points) {
    if (level_set->IsCloseToMesh(p)) {
      if (verbose) {
        std::cout << "command::MeshFlagCommand: points too close to the mesh: "
          << p.transpose() << std::endl;
      }
      continue;
    }
    if (shape.IsInside(p)) inside_points.push_back(p);
    else outside_points.push_back(p);
  }

  // Write back results.
  common::WriteDataFile(outside_points, output_negative_data_file);
  common::WriteDataFile(inside_points, output_positive_data_file);
}

}
