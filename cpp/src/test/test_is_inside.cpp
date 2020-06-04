#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include "Eigen/Dense"
#include "mesh/tri_mesh.h"
#include "mesh/level_set_helper.h"
#include "common/file_helper.h"

namespace test {

void TestIsInside(const std::string& root, const std::string& scene) {
  std::cout << "test::TestIsInside:" << std::endl;
  // Find example folder.
  std::string mesh_path = common::AppendFolderToPath(root, "example");
  mesh_path = common::AppendFolderToPath(mesh_path, scene);
  std::string csg_path = mesh_path;
  mesh_path = common::AppendFileToPath(mesh_path, "csg_low_res.off");
  csg_path = common::AppendFileToPath(csg_path, "csg.scad");

  const int sample_num = 100000;
  // Load mesh.
  mesh::TriMesh shape;
  shape.Initialize(mesh_path);

  // Load CSG.
  std::shared_ptr<csg::CsgNode> csg_root = nullptr;
  common::ReadScadFile(csg_path, csg_root);

  // Compute the level set.
  const Eigen::Vector3d pmin = shape.box_min(), pmax = shape.box_max();
  std::cout << "Testing " << scene << ". Loaded " << shape.NumOfVertices()
    << " vertices and " << shape.NumOfFaces() << " faces." << std::endl
    << "Bounding box: (" << pmin.transpose() << "), (" << pmax.transpose()
    << ")." << std::endl;
  const double grid_size = std::min((pmax - pmin).maxCoeff() * 0.01, 0.1);
  std::cout << "Computing level-set with grid size = " << grid_size
    << "." << std::endl;
  mesh::LevelSetHelper level_set(shape, grid_size);

  // Sample random points.
  std::cout << "Sampling " << sample_num << " points." << std::endl;
  const Eigen::Matrix3Xd random_seed = Eigen::Matrix3Xd::Random(3,
    sample_num);
  const Eigen::Matrix3Xd random_points = ((pmax - pmin).asDiagonal() * 0.55
    * random_seed).colwise() + (pmax + pmin) * 0.5;

  // Check all random points.
  int close_point_count = 0;
  int inside_point_count = 0, outside_point_count = 0;
  for (int i = 0; i < sample_num; ++i) {
    const Eigen::Vector3d point = random_points.col(i);
    if (level_set.IsCloseToMesh(point)) {
      ++close_point_count;
      continue;
    }
    const bool inside_csg = csg_root->IsInside(point);
    const bool inside_mesh = shape.IsInside(point);
    if (inside_csg != inside_mesh) {
      std::cerr << common::RedHead()
        << "Point (" << i << "): (" << point.transpose() << "): csg "
        "thinks this point is " << (inside_csg ? "inside" : "outside")
        << " but mesh thinks it is " << (inside_mesh ? "inside." : "outside.")
        << common::RedTail() << std::endl;
      exit(-1);
    }
    if (inside_mesh) ++inside_point_count;
    else ++outside_point_count;
  }
  const double close_point_rate = close_point_count * 100.0
    / sample_num;
  const double inside_rate = inside_point_count * 100.0 / sample_num,
    outside_rate = outside_point_count * 100.0 / sample_num;
  std::cout << close_point_rate << "% points are too close to the mesh."
    << std::endl
    << inside_rate << "% points are inside." << std::endl
    << outside_rate << "% points are outside." << std::endl;

  std::cout << common::GreenHead() << "test::TestIsInside: OK."
    << common::GreenTail() << std::endl;
}

}
