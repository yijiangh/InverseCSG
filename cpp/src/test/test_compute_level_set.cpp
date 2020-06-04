#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Eigen/Dense"
#include "common/file_helper.h"
#include "common/math_helper.h"
#include "mesh/tri_mesh.h"
#include "mesh/level_set_helper.h"

namespace test {

// Configuration file:
// grid_size: 1.0
// false_positive_threshold: 0.2
void TestComputeLevelSet(const std::string& conf_file,
  const std::string& root, const std::string& scene) {
  std::cout << "test::TestComputeLevelSet:" << std::endl;
  // Find example folder.
  std::string scene_path = common::AppendFolderToPath(root, "example");
  scene_path = common::AppendFolderToPath(scene_path, scene);
  std::string mesh_path = common::AppendFileToPath(scene_path,
    "csg_low_res.off");
  if (!common::FileExist(mesh_path))
    mesh_path = common::AppendFileToPath(scene_path, "csg_high_res.off");

  // Load configuration file.
  if (!common::HasExtension(conf_file, ".conf")) {
    std::cerr << common::RedHead() << "test::TestComputeLevelSet: invalid conf"
      << " file: " << conf_file << common::RedTail() << std::endl;
    exit(-1);
  }
  std::map<std::string, std::string> kv_pairs;
  common::ReadConfFile(conf_file, kv_pairs);
  const double grid_size = std::stod(kv_pairs.at("grid_size"));
  const double fp_threshold =
    std::stod(kv_pairs.at("false_positive_threshold")) * 100.0;
  const int sample_num = std::stoi(kv_pairs.at("sample"));

  // Load mesh.
  mesh::TriMesh shape;
  shape.Initialize(mesh_path);
  const Eigen::Vector3d pmin = shape.box_min(), pmax = shape.box_max();
  std::cout << "Testing " << scene << ". Loaded " << shape.NumOfVertices()
    << " vertices and " << shape.NumOfFaces() << " faces." << std::endl
    << "Bounding box: (" << pmin.transpose() << "), (" << pmax.transpose()
    << ")." << std::endl;

  // Sample random points.
  std::cout << "Sampling " << sample_num << " points." << std::endl;
  const Eigen::Matrix3Xd random_seed = Eigen::Matrix3Xd::Random(3,
    sample_num);
  const Eigen::Matrix3Xd random_points = ((pmax - pmin).asDiagonal() * 0.55 *
    random_seed).colwise() + (pmax + pmin) * 0.5;

  // Compute the level set.
  std::cout << "Computing level-set with grid size = " << grid_size
    << "." << std::endl;
  mesh::LevelSetHelper level_set(shape, grid_size);
  std::cout << "Finished computing the level set." << std::endl;
  const int face_num = shape.NumOfFaces();
  int false_positive_count = 0;
  for (int i = 0; i < sample_num; ++i) {
    if (i % 1000 == 0) {
      std::cout << "Checking " << i << " samples..." << std::endl;
    }
    const Eigen::Vector3d point = random_points.col(i);
    const bool level_set_inside = level_set.IsCloseToMesh(point);
    // Ground truth.
    double dist = common::Infinity();
    int closest_triangle = -1;
    for (int j = 0; j < face_num; ++j) {
      const double dist_to_triangle = common::PointToTriangleDistance(point,
        shape.Triangle(j));
      if (dist_to_triangle < dist) {
        dist = dist_to_triangle;
        closest_triangle = j;
      }
    }
    if (dist <= grid_size) {
      // In this case, level_set_inside has to be true.
      if (!level_set_inside) {
        std::cerr << common::RedHead()
          << "FAILED: point " << i << " (" << point.transpose()
          << "): level set thinks it is outside but dist = " << dist
          << ". Closest triangle (" << closest_triangle << ") = "
          << std::endl << shape.Triangle(closest_triangle)
          << common::RedTail() << std::endl;
        exit(-1);
      }
    } else if (level_set_inside) {
      // We don't want too many points to fall in this branch.
      ++false_positive_count;
    }
  }
  const double false_positive_rate = false_positive_count * 100.0
    / sample_num;
  std::cout << false_positive_count << " false positive points. Rate = "
    << false_positive_rate << "%." << std::endl;
  if (false_positive_rate > fp_threshold) {
    std::cerr << common::RedHead() << "FAILED. Too many false positive points."
      << common::RedTail() << std::endl;
    exit(-1);
  }
  std::cout << common::GreenHead() << "test::TestComputeLevelSet: OK."
    << common::GreenTail() << std::endl;
}

}
