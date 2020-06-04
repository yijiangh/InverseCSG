#include "command/command.h"
#include <iostream>
#include <memory>
#include "common/file_helper.h"
#include "common/math_helper.h"
#include "csg/csg_node.h"
#include "mesh/tri_mesh.h"

namespace command {

static void CheckCsgMeshDiffCommandFileName(const std::string& scad_file,
  const std::string& mesh_file) {
  if (!common::HasExtension(scad_file, ".scad")) {
    std::cerr << common::RedHead() << "command::CheckCsgMeshDiffCommandFileName: "
      << "wrong scad file: " << scad_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(mesh_file, ".off")) {
    std::cerr << common::RedHead() << "command::CheckCsgMeshDiffCommandFileName: "
      << "wrong mesh file: " << mesh_file
      << common::RedTail() << std::endl;
    exit(-1);
  }
}

void CsgMeshDiffCommand(const double grid_size, const bool help,
  const std::string& scad_file, const std::string& mesh_file,
  const bool verbose) {
  // Print help information.
  if (help) {
    std::cout
      << "csg-mesh-diff       Estimate the volumetric difference." << std::endl
      << "  -d <double>       Grid size." << std::endl
      << "  -h                Print help information." << std::endl
      << "  -i <SCAD file>    OpenSCAD file." << std::endl
      << "  -m <OFF file>     Mesh file." << std::endl
      << "  -v                Verbose mode." << std::endl << std::endl
      << "Print the absolute and relative volumetric difference."
      << std::endl << std::endl;
    return;
  }

  // Sanity check.
  CheckCsgMeshDiffCommandFileName(scad_file, mesh_file);
  if (grid_size < 0.0) {
    std::cerr << common::RedHead() << "command::CsgMeshDiffCommand: wrong "
      << "grid_size: " << grid_size << common::RedTail() << std::endl;
    exit(-1);
  }

  // Read shape.
  std::shared_ptr<csg::CsgNode> root(nullptr);
  common::ReadScadFile(scad_file, root);

  // Read mesh.
  mesh::TriMesh shape;
  shape.Initialize(mesh_file);

  // Compute the absolute error.
  const Eigen::Vector3d pmin = shape.box_min(), pmax = shape.box_max();
  const Eigen::Vector3i grid_num = ((pmax - pmin) / grid_size).cast<int>();
  int num_inside_mesh = 0, num_diff = 0, num_unsure = 0;
  int total_num = 0;
  int progress = 0;
  for (int i = 0; i < grid_num.x(); ++i)
    for (int j = 0; j < grid_num.y(); ++j)
      for (int k = 0; k < grid_num.z(); ++k) {
        ++total_num;
        const int cur_progress = total_num / (grid_num.prod() / 10);
        if (verbose && (cur_progress > progress)) {
          progress = cur_progress;
          std::cout << "command::CsgMeshDiffCommand: " << cur_progress * 10
            << "%..." << std::endl;
        }
        // Randomly pick a sample.
        const Eigen::Vector3d sample = Eigen::Vector3d::Random() * 0.5 +
          Eigen::Vector3d(i + 0.5, j + 0.5, k + 0.5) * grid_size + pmin;
        const bool inside_csg = root->IsInside(sample);
        bool inside_mesh = false;
        try {
          inside_mesh = shape.IsInside(sample);
        } catch (int exp_num) {
          ++num_unsure;
          continue;
        } 
        if (inside_mesh) ++num_inside_mesh;
        if (inside_mesh != inside_csg) ++num_diff;
      }
  const double max_abs_error = std::pow(grid_size, 3) * (num_diff + num_unsure); 
  const double mesh_vol = std::pow(grid_size, 3) * num_inside_mesh;
  const double max_rel_error = max_abs_error / mesh_vol;
  std::cout << max_abs_error << " " << max_rel_error << std::endl;
}

}
