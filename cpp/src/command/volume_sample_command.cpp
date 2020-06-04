#include "command/command.h"
#include <iostream>
#include <string>
#include "common/file_helper.h"
#include "mesh/tri_mesh.h"
#include "mesh/level_set_helper.h"
#include "primitive/surface_primitive.h"

namespace command {

static void CheckVolumeSampleCommandFileName(const std::string& mesh_file,
  const std::string& level_set_file, const std::string& neg_data_file,
  const std::string& pos_data_file, const std::string& prim_file) {
  if (!common::HasExtension(mesh_file, ".off")) {
    std::cerr << common::RedHead()
      << "command::CheckVolumeSampleCommandFileName: wrong scad file: "
      << mesh_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(level_set_file, ".ls")) {
    std::cerr << common::RedHead()
      << "command::CheckVolumeSampleCommandFileName: wrong data file: "
      << level_set_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(neg_data_file, ".data")) {
    std::cerr << common::RedHead()
      << "command::CheckVolumeSampleCommandFileName: wrong neg data file: "
      << neg_data_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(pos_data_file, ".data")) {
    std::cerr << common::RedHead()
      << "command::CheckVolumeSampleCommandFileName: wrong pos data file: "
      << pos_data_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(prim_file, ".prim")) {
    std::cerr << common::RedHead()
      << "command::CheckVolumeSampleCommandFileName: wrong prim file: "
      << prim_file << common::RedTail() << std::endl;
  }
}

void VolumeSampleCommand(const double density, const double min_dist,
  const bool help, const std::string& mesh_file,
  const std::string& level_set_file, const std::string& neg_data_file,
  const std::string& pos_data_file, const std::string& prim_file,
  const bool verbose) {
  if (help) {
    std::cout
      << "volume-sample       Sample points inside the triangle mesh."
      << std::endl
      << "  -d <double>       Sampling density (number of points per unit"
      << " volume)." << std::endl
      << "  -e <double>       Minimum sample distance to primitives and mesh."
      << std::endl
      << "  -h                Print help information." << std::endl
      << "  -i <OFF file>     Input triangle mesh." << std::endl
      << "  -l <LS file>      Input level-set file." << std::endl
      << "  -n <DATA file>    Output negative data file." << std::endl
      << "  -p <DATA file>    Output positive data file." << std::endl
      << "  -r <PRIM file>    Input primitive file." << std::endl
      << "  -v                Verbose mode." << std::endl << std::endl
      << "Given a triangle mesh, sample points in its bounding" << std::endl
      << "box with provided density. Points with distance to the" << std::endl
      << "mesh surface <= min_dist will be ignored." << std::endl << std::endl;
    return;
  }

  // Check inputs.
  CheckVolumeSampleCommandFileName(mesh_file, level_set_file, neg_data_file,
    pos_data_file, prim_file);
  if (min_dist <= 0.0) {
    std::cerr << common::RedHead()
      << "command::VolumeSampleCommand: wrong min_dist: " << min_dist
      << common::RedTail() << std::endl;
    exit(-1);
  }

  // Read level-set.
  std::shared_ptr<mesh::LevelSetHelper> level_set = nullptr;
  common::ReadLevelSetFile(level_set_file, level_set);
  if (level_set->grid_size() < min_dist) {
    std::cerr << common::RedHead()
      << "command::VolumeSampleCommand: level-set grid size ("
      << level_set->grid_size() << ") too small. Should be at least the same as"
      << " min_dist (" << min_dist << ")." << common::RedTail() << std::endl;
    exit(-1);
  }
  // Read primitives.
  std::vector<std::shared_ptr<primitive::SurfacePrimitive>> primitives;
  common::ReadPrimFile(prim_file, primitives);

  // Read mesh.
  mesh::TriMesh shape;
  shape.Initialize(mesh_file);
  const Eigen::Vector3d pmin = shape.box_min(), pmax = shape.box_max();
  const Eigen::Vector3d pmid = (pmin + pmax) * 0.5, psize = pmax - pmid;

  // Generate random points.
  const int sample_num = static_cast<int>(density * psize.prod() * 8);
  if (verbose) {
    std::cout << "command::VolumeSampleCommand: processing " << sample_num
      << " points." << std::endl;
  }
  std::vector<Eigen::Vector3d> pos_points, neg_points;
  int verbose_process = 0;
  for (int i = 0; i < sample_num; ++i) {
    const int process = i / (sample_num / 10);
    if (verbose && (process > verbose_process)) {
      verbose_process = process;
      std::cout << "command::VolumeSampleCommand: " << verbose_process * 10
        << "%..." << std::endl;
    }
    Eigen::Vector3d point = pmid +
      Eigen::Vector3d::Random().cwiseProduct(psize);
    if (level_set->IsCloseToMesh(point)) continue;
    bool too_close = false;
    for (const auto& p : primitives) {
      const double dist = std::fabs(p->DistToSurface(point));
      if (dist <= min_dist) {
        too_close = true;
        break;
      }
    }
    if (too_close) continue;
    if (shape.IsInside(point)) pos_points.push_back(point);
    else neg_points.push_back(point);
  }

  // Write back to file.
  common::WriteDataFile(pos_points, pos_data_file);
  common::WriteDataFile(neg_points, neg_data_file);
}

}
