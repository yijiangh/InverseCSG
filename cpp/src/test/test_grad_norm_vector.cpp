#include <algorithm>
#include <iostream>
#include <string>
#include <cmath>
#include "Eigen/Dense"
#include "common/file_helper.h"
#include "common/math_helper.h"
#include "mesh/tri_mesh.h"
#include "vsa/vsa_tri_mesh_wrapper.h"
#include "vsa/quadratic_surface.h"

namespace test {

// Conf file:
// face_num: 100
// sample: 1000000
// rel_threshold: 0.1
// abs_threshold: 1e-3
void TestGradNormVector(const std::string& conf_file,
  const std::string& root, const std::string& scene) {
  if (!common::HasExtension(conf_file, ".conf")) {
    std::ostringstream ss;
    ss << "test::TestGradNormVector: incorrect conf file name: " << conf_file;
    common::PrintError(ss.str());
  }
  std::cout << "test::TestGradNormVector:" << std::endl;
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
  const int face_num = std::stoi(kv_pairs.at("face_num"));
  const int sample_num = std::stoi(kv_pairs.at("sample"));
  const double rel_threshold = std::stod(kv_pairs.at("rel_threshold"));
  const double abs_threshold = std::stod(kv_pairs.at("abs_threshold"));

  mesh::TriMesh shape;
  shape.Initialize(mesh_path);
  vsa::VsaTriMeshWrapper wrapper(shape);

  const auto faces = common::GenerateRandomInts(0,
    shape.NumOfFaces(), face_num);
  const int faces_size = static_cast<int>(faces.size());
  for (int j = 0; j < faces_size; ++j) {
    if (j % 1000 == 0) {
      std::cout << "test::TestGradNormVector: testing " << j << "/" << face_num
        << " faces..." << std::endl;
    }
    const int i = faces[j];
    // Densely sample points to estimate the integral.
    const Eigen::Matrix3d triangle = shape.Triangle(i);
    const Eigen::Vector3d v0 = triangle.col(0),
      v1 = triangle.col(1), v2 = triangle.col(2);
    const Eigen::Matrix3Xd points =
      common::UniformSampleFromTriangle(v0, v1, v2, sample_num);

    // Randomly generate a quadratic surface.
    const Eigen::VectorXd quad_params = Eigen::VectorXd::Random(10);
    vsa::QuadraticSurface quad(wrapper);
    quad.set_parameters(quad_params);
    const double target = quad_params.transpose() * wrapper.grad_norm_vector(i);
    // Now estimate the integral.
    double estimate = 0.0;
    for (int j = 0; j < sample_num; ++j) {
      const double dfx = quad.Gradient(points.col(j)).dot(shape.face_normal(i));
      estimate += dfx;
    }
    estimate *= shape.area(i) / sample_num;
    const double target_abs = std::fabs(target);
    // Compare.
    if (std::fabs(estimate - target) >=
      std::max(target_abs * rel_threshold, abs_threshold)) {
      std::cerr << common::RedHead()
        << "test::TestGradNormVector: integral differs too much: target = "
        << target << ", estimate = " << estimate << "." << std::endl
        << "Quad: " << quad_params.transpose() << std::endl
        << "Triangle:" << std::endl
        << "v0 = " << v0.transpose() << std::endl
        << "v1 = " << v1.transpose() << std::endl
        << "v2 = " << v2.transpose() << std::endl
        << common::RedTail() << std::endl;
      exit(-1);
    }
  }

  std::cout << common::GreenHead() << "test::TestGradNormVector: OK."
    << common::GreenTail() << std::endl;
}

}
