#include <algorithm>
#include <iostream>
#include <string>
#include "Eigen/Dense"
#include "common/file_helper.h"
#include "common/math_helper.h"
#include "mesh/tri_mesh.h"
#include "mesh/intersection.h"
#include "mesh/level_set_helper.h"

namespace test {

// CONF file:
// grid_size: 1.0
// point_sample: 2000
// dir_sample: 32
// singular_rate: 0.1
void TestIntersect(const std::string& conf_file, const std::string& root,
  const std::string& scene) {
  if (!common::HasExtension(conf_file, ".conf")) {
    std::ostringstream ss;
    ss << "test::TestIntersect: incorrect conf file name: " << conf_file;
    common::PrintError(ss.str());
  }
  std::cout << "test::TestIntersect:" << std::endl;
  // Find example folder.
  std::string scene_path = common::AppendFolderToPath(root, "example");
  scene_path = common::AppendFolderToPath(scene_path, scene);
  std::string mesh_path = common::AppendFileToPath(scene_path,
    "csg_low_res.off");
  if (!common::FileExist(mesh_path))
    mesh_path = common::AppendFileToPath(scene_path, "csg_high_res.off");

  // Read conf file.
  std::map<std::string, std::string> kv_pairs;
  common::ReadConfFile(conf_file, kv_pairs);
  const double grid_size = std::stod(kv_pairs.at("grid_size"));
  const int point_sample_num = std::stoi(kv_pairs.at("point_sample"));
  const int dir_sample_num = std::stoi(kv_pairs.at("dir_sample"));
  const double singular_rate = std::stod(kv_pairs.at("singular_rate")) * 100.0;

  mesh::TriMesh shape;
  shape.Initialize(mesh_path);

  // Compute the bounding box.
  const Eigen::Vector3d pmin = shape.box_min(), pmax = shape.box_max();
  std::cout << "Testing " << scene << ". Loaded " << shape.NumOfVertices()
    << " vertices and " << shape.NumOfFaces() << " faces." << std::endl
    << "Bounding box: (" << pmin.transpose() << "), (" << pmax.transpose()
    << ")." << std::endl;

  // Compute the level set.
  std::cout << "Computing level-set with grid size = " << grid_size
    << "." << std::endl;
  mesh::LevelSetHelper level_set(shape, grid_size);

  // Sample random points and directions.
  const Eigen::Matrix3Xd random_point_seed = Eigen::Matrix3Xd::Random(
    3, point_sample_num);
  const Eigen::Matrix3Xd random_points = ((pmax - pmin).asDiagonal() *
    random_point_seed).colwise() + (pmax + pmin) * 0.5;
  const Eigen::Matrix3Xd random_dir_seed = Eigen::Matrix3Xd::Random(
    3, dir_sample_num);
  const Eigen::Matrix3Xd random_dir = random_dir_seed.array() / (
    Eigen::Vector3d::Ones() * random_dir_seed.colwise().norm()).array();
  std::cout << "Sampling " << point_sample_num << " points and "
    << dir_sample_num << " directions." << std::endl;

  // Checking all points and directions in a brute-force way.
  int kd_singular_count = 0, mesh_singular_count = 0;
  const double eps = common::Epsilon();
  for (int i = 0; i < point_sample_num; ++i) {
    const Eigen::Vector3d point = random_points.col(i);
    for (int j = 0; j < dir_sample_num; ++j) {
      const Eigen::Vector3d dir = random_dir.col(j);
      mesh::Intersection kd_inter;
      const Eigen::Vector2d random_t_seed =
        Eigen::Vector2d::Random().cwiseAbs();
      // Make sure tmax - tmin is strictly nonzero by adding 2 * eps.
      const double tmin = random_t_seed.x();
      const double tmax = (pmax - pmin).norm() * random_t_seed.y() + tmin
        + 2.0f * eps;
      // Skip if the point + tmin * dir is too close to the mesh.
      const Eigen::Vector3d point_min = point + tmin * dir;
      if ((point_min - pmin).minCoeff() > -grid_size
        && (pmax - point_min).minCoeff() > -grid_size
        && level_set.IsCloseToMesh(point_min)) continue;

      // Kd-tree version. 
      shape.kd_tree().Intersect(point, dir, tmin, tmax, kd_inter);
      if (kd_inter.uncertain()) ++kd_singular_count;

      // Ground truth.
      mesh::Intersection mesh_inter =
        mesh::Intersection::UncertainIntersection();
      // If Kd-tree thinks it is certainly a hit, we check (tmin, t).
      double new_tmax = (!kd_inter.uncertain() && kd_inter.hit())
        ? (kd_inter.t() + 2.0 * eps) : tmax;
      for (int k = 0; k < shape.NumOfFaces(); ++k) {
        mesh::Intersection triangle_inter;
        shape.IntersectTriangle(k, point, dir, tmin, new_tmax,
          triangle_inter);
        if (triangle_inter.uncertain()) {
          ++mesh_singular_count;
          break;
        }
        if (triangle_inter.hit()) {
          mesh_inter = triangle_inter;
          new_tmax = triangle_inter.t();
        }
      }

      if (!kd_inter.uncertain() && !mesh_inter.uncertain() &&
        (kd_inter.hit() != mesh_inter.hit() ||
        (kd_inter.hit() && kd_inter.t() != mesh_inter.t()))) {
        std::cerr << common::RedHead()
          << "Point (" << i << ") = " << point.transpose()
          << ", dir (" << j << ") = " << dir.transpose() << ": intersect "
          << "mismatch: " << std::endl
          << "tmin: " << tmin << "; tmax: " << tmax << std::endl
          << "kd-tree intersection: " << kd_inter << std::endl
          << "mesh intersection: " << mesh_inter
          << common::RedTail() << std::endl;
        exit(-1);
      }
    }
  }
  const double kd_singular_rate = kd_singular_count * 100.0 /
    (point_sample_num * dir_sample_num);
  const double mesh_singular_rate = mesh_singular_count * 100.0 /
    (point_sample_num * dir_sample_num);
  std::cout << "Kd singular rate = " << kd_singular_rate << "%, "
    << "mesh singular rate = " << mesh_singular_rate << "%." << std::endl;
  if (kd_singular_rate > singular_rate ||
    mesh_singular_rate > singular_rate) {
    common::PrintError("test::TestIntersect: too many singular intersections. "
      "Please improve the quality of the mesh.");
  }
  std::cout << common::GreenHead() << "test::TestIntersect: OK."
    << common::GreenTail() << std::endl;
}

}
