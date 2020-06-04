#include "command/command.h"
#include <cmath>
#include <iostream>
#include "common/math_helper.h"
#include "common/file_helper.h"
#include "mesh/tri_mesh.h"
#include "mesh/level_set_helper.h"

namespace command {

static void CheckSurfaceSampleCommandFileName(const std::string& mesh_file,
  const std::string& level_set_file, const std::string& output_data_file,
  const std::string& primitive_file) {
  if (!common::HasExtension(mesh_file, ".off")) {
    std::cerr << common::RedHead()
      << "command::CheckSurfaceSampleCommandFileName: wrong mesh file: "
      << mesh_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(level_set_file, ".ls")) {
    std::cerr << common::RedHead()
      << "command::CheckSurfaceSampleCommandFileName: wrong level-set file: "
      << level_set_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(output_data_file, ".data")) {
    std::cerr << common::RedHead()
      << "command::CheckSurfaceSampleCommandFileName: wrong data file: "
      << output_data_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(primitive_file, ".prim")) {
    std::cerr << common::RedHead()
      << "command::CheckSurfaceSampleCommandFileName: wrong primitive file: "
      << primitive_file << common::RedTail() << std::endl;
    exit(-1);
  }
}

void SurfaceSampleCommand(const double max_dist, const double density,
  const double min_dist, const bool help, const std::string& mesh_file,
  const std::string& level_set_file, const std::string& output_data_file,
  const std::string& primitive_file, const bool verbose) {
  if (help) {
    std::cout
      << "surface-sample      Sample points from primitives and mesh."
      << std::endl
      << "  -b <double>       Maximum sample distance to primitives and mesh."
      << std::endl
      << "  -d <double>       Sampling density (number of points per unit"
      << " volume)." << std::endl
      << "  -e <double>       Minimum sample distance to primitives and mesh."
      << std::endl
      << "  -h                Print help information." << std::endl
      << "  -i <OFF file>     Input triangle mesh." << std::endl
      << "  -l <LS file>      Input level-set file." << std::endl
      << "  -o <DATA file>    Output data file." << std::endl
      << "  -p <PRIM file>    Input primitive file." << std::endl
      << "  -v                Verbose mode." << std::endl << std::endl
      << "Given primitives and triangle meshes, sample points in" << std::endl
      << "a banded volume extruded from each primitive and each" << std::endl
      << "triangle in the mesh. It is guaranteed that no point is" << std::endl
      << "within the distance of min_dist to any primitives or" << std::endl
      << "any triangles." << std::endl << std::endl;
    return;
  }

  // Check inputs.
  CheckSurfaceSampleCommandFileName(mesh_file, level_set_file,
    output_data_file, primitive_file);
  if (min_dist <= 0.0f || max_dist <= min_dist) {
    std::cerr << common::RedHead()
      << "command::SurfaceSampleCommand: invalid min_dist or max_dist: "
      << min_dist << ", " << max_dist << common::RedTail() << std::endl;
    exit(-1);
  }
  if (density <= 0.0) {
    std::cerr << common::RedHead()
      << "command::SurfaceSampleCommand: invalid density: " << density
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
      << "command::SurfaceSampleCommand: level-set grid size ("
      << level_set->grid_size() << ") too small. Should be at least the same as"
      << " min_dist (" << min_dist << ")." << common::RedTail() << std::endl;
    exit(-1);
  }

  // Sample points from all surface primitives.
  Eigen::Vector3d box_min = shape.box_min(), box_max = shape.box_max();
  // Slightly enlarge the bounding boxes.
  const Eigen::Vector3d box_diag = box_max - box_min;
  box_min -= box_diag * 0.1;
  box_max += box_diag * 0.1;
  if (verbose) {
    std::cout << "command::SurfaceSampleCommand: box_min = "
      << box_min.transpose() << ", box_max = " << box_max.transpose()
      << std::endl;
  }
  std::vector<Eigen::Vector3d> sample_points(0);
  std::vector<std::shared_ptr<primitive::SurfacePrimitive>> primitives(0);
  common::ReadPrimFile(primitive_file, primitives);
  for (const auto& surface : primitives) {
    std::vector<Eigen::Vector3d> points;
    surface->Sample(min_dist, max_dist, box_min, box_max, density, points);
    sample_points.insert(sample_points.end(), points.begin(), points.end());
  }
  // Sample points from the triangle mesh.
  for (int i = 0; i < shape.NumOfFaces(); ++i) {
    const Eigen::Matrix3d triangle = shape.Triangle(i);
    const Eigen::Vector3d v0 = triangle.col(0), v1 = triangle.col(1),
      v2 = triangle.col(2);
    Eigen::Vector3d normal = (v1 - v0).cross(v2 - v1);
    const double double_area = normal.norm();
    // Skip singular triangles.
    if (double_area <= 2.0 * common::Epsilon()) continue;
    normal /= double_area;
    const double volume = double_area * (max_dist - min_dist);
    const int num = static_cast<int>(volume * density);
    const Eigen::Matrix3Xd random_seed = Eigen::Matrix3Xd::Random(3, num);
    for (int j = 0; j < num; ++j) {
      double h = random_seed(0, j) * (max_dist - min_dist);
      if (h > 0) h += min_dist;
      else h -= min_dist;
      // Alpha and beta.
      double alpha = random_seed(0, j) * 0.5 + 0.5,
        beta = random_seed(1, j) * 0.5 + 0.5;
      // Flip if it goes outside the triangle.
      if (alpha + beta > 1.0) {
        const double x = alpha, y = beta;
        alpha = 1.0 - y;
        beta = 1.0 - x;
      }
      const Eigen::Vector3d point = v0 + (v1 - v0) * alpha + (v2 - v0) * beta
        + normal * h;
      sample_points.push_back(point);
    }
  }

  // Remove points too close to any primitive or mesh.
  std::vector<Eigen::Vector3d> filtered_sample_points(0);
  filtered_sample_points.reserve(sample_points.size());
  for (const auto& p : sample_points) {
    // Check the triangle mesh.
    if (level_set->IsCloseToMesh(p)) continue;
    // Check primitives.
    bool too_close = false;
    for (const auto& surface : primitives) {
      const double dist = surface->DistToSurface(p);
      if (std::fabs(dist) <= min_dist) {
        too_close = true;
        break;
      }
    }
    if (too_close) continue;
    filtered_sample_points.push_back(p);
  }
  // Write back results to file.
  common::WriteDataFile(filtered_sample_points, output_data_file);
}

}
