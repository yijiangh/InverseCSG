#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include "Eigen/Dense"
#include "common/file_helper.h"
#include "common/math_helper.h"
#include "mesh/tri_mesh.h"
#include "vsa/vsa_tri_mesh_wrapper.h"
#include "vsa/quadratic_surface.h"

namespace test {

// Conf file:
// face_num: 100
// sample: 10000
// abs_threshold: 0.01
// rel_threshold: 0.1
void TestInitializeSurfaceParameters(const std::string& conf_file,
  const std::string& root, const std::string& scene) {
  if (!common::HasExtension(conf_file, ".conf")) {
    std::ostringstream ss;
    ss << "test::TestInitializeSurfaceParameters: invalid conf file: "
      << conf_file;
    common::PrintError(ss.str());
  }
  std::cout << "test::TestInitializeSurfaceParameters:" << std::endl;
  // Read conf file.
  std::map<std::string, std::string> kv_pairs;
  common::ReadConfFile(conf_file, kv_pairs);
  const int face_num = std::stoi(kv_pairs.at("face_num"));
  const int sample_num = std::stoi(kv_pairs.at("sample"));
  const double abs_threshold = std::stod(kv_pairs.at("abs_threshold"));
  const double rel_threshold = std::stod(kv_pairs.at("rel_threshold"));

  // Test 1: check a sphere.
  {
    // Load the sphere.
    mesh::TriMesh shape;
    shape.Initialize(common::AppendFileToPath(
      root, "example/one_sphere/csg_low_res.off"));
    vsa::VsaTriMeshWrapper wrapper(shape);
  
    std::vector<int> region(shape.NumOfFaces());
    for (int i = 0; i < shape.NumOfFaces(); ++i) region[i] = i;
    vsa::QuadraticSurface quad_face(wrapper);
    quad_face.InitializeSurfaceParameters(region);
    Eigen::VectorXd target(10);
    target << -1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0;
    Eigen::VectorXd estimate = quad_face.parameters();
    if (estimate(0) > 0) estimate = -estimate;
    target *= estimate.norm() / target.norm();
    if ((target - estimate).cwiseAbs().maxCoeff() >
      rel_threshold * target.cwiseAbs().maxCoeff()) {
      std::cerr << common::RedHead()
        << "test::TestInitializeSurfaceParameters: failed to estimate a sphere."
        << std::endl
        << "estimate: " << estimate.transpose() << std::endl
        << "expected: " << target.transpose() << common::RedTail() << std::endl;
      exit(-1);
    }
  }

  // Test 2: check real model.
  // Find example folder.
  std::string scene_path = common::AppendFolderToPath(root, "example");
  scene_path = common::AppendFolderToPath(scene_path, scene);
  std::string mesh_path = common::AppendFileToPath(scene_path,
    "csg_low_res.off");
  if (!common::FileExist(mesh_path))
    mesh_path = common::AppendFileToPath(scene_path, "csg_high_res.off");
  mesh::TriMesh shape;
  shape.Initialize(mesh_path);
  vsa::VsaTriMeshWrapper wrapper(shape);

  const auto region = common::GenerateRandomInts(0,
    shape.NumOfFaces(), face_num);
  vsa::QuadraticSurface quad_face(wrapper);
  quad_face.InitializeSurfaceParameters(region);
  const Eigen::VectorXd estimate = quad_face.parameters();
  Eigen::MatrixXd M, N;
  M = N = Eigen::MatrixXd::Zero(10, 10);
  for (const int idx : region) {
    M += wrapper.l2_matrix(idx);
    N += wrapper.l21_matrix(idx);
  }
  const double estimate_M = estimate.dot(M * estimate);
  const double estimate_N = estimate.dot(N * estimate);
  // Skip this check if estimate_N is too close to zero.
  if (std::fabs(estimate_N) < abs_threshold) {
    std::ostringstream ss;
    ss << "test::TestInitializeSurfaceParameters: score seems infinite."
      << estimate / estimate_N;
    common::PrintError(ss.str());
  }
  const double estimate_score = estimate_M / estimate_N;
  // Now randomly generate many surfaces. Hopefully, none of them are better
  // than our estimation.
  for (int i = 0; i < sample_num; ++i) {
    // Randomly generate a surface.
    const Eigen::VectorXd rand_params = Eigen::VectorXd::Random(10);
    const double rand_M = rand_params.dot(M * rand_params);
    const double rand_N = rand_params.dot(N * rand_params);
    // Skip infinite scores.
    if (std::fabs(rand_N) < abs_threshold) continue;
    const double rand_score = rand_M / rand_N;
    // Fail only if rand_score is significantly smaller than estimate_score.
    if (rand_score < estimate_score * (1.0 - rel_threshold) &&
        estimate_score - rand_score > abs_threshold) {
      std::cerr << common::RedHead()
        << "test::TestInitializeSurfaceParameters: estimate score is bigger."
        << std::endl
        << "estimate score: " << estimate_score << std::endl
        << "random score: " << rand_score << common::RedTail() << std::endl;
      exit(-1);
    }
  }

  std::cout << common::GreenHead()
    << "test::TestInitializeSurfaceParameters: OK."
    << common::GreenTail() << std::endl;
}

}
