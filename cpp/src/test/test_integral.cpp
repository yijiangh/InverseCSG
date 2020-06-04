#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include "Eigen/Dense"
#include "common/file_helper.h"
#include "common/math_helper.h"
#include "mesh/tri_mesh.h"
#include "vsa/vsa_tri_mesh_wrapper.h"

namespace test {

// Conf file:
// face_num: 100
// sample: 10000
// rel_threshold: 0.1
// abs_threshold: 1e-3
void TestIntegral(const std::string& conf_file,
  const std::string& root, const std::string& scene) {
  if (!common::HasExtension(conf_file, ".conf")) {
    std::ostringstream ss;
    ss << "test::TestIntegral: incorrect conf file name: " << conf_file;
    common::PrintError(ss.str());
  }
  std::cout << "test::TestIntegral:" << std::endl;
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

  // Test the integral.
  const auto faces = common::GenerateRandomInts(0,
    shape.NumOfFaces(), face_num);
  const int faces_size = static_cast<int>(faces.size());
  for (int j = 0; j < faces_size; ++j) {
    if (j % 1000 == 0) {
      std::cout << "test::TestIntegral: testing " << j << "/" << face_num
        << " faces..." << std::endl;
    }
    const int i = faces[j];
    // Densely sample points to estimate the integral.
    const Eigen::Matrix3d triangle = shape.Triangle(i);
    const Eigen::Vector3d v0 = triangle.col(0),
      v1 = triangle.col(1), v2 = triangle.col(2);
    const Eigen::Matrix3Xd points =
      common::UniformSampleFromTriangle(v0, v1, v2, sample_num);

    Eigen::RowVectorXd x[5], y[5], z[5];
    x[0] = y[0] = z[0] = Eigen::VectorXd::Ones(sample_num);
    for (int i = 1; i < 5; ++i) {
      x[i] = x[i - 1].array() * points.row(0).array();
      y[i] = y[i - 1].array() * points.row(1).array();
      z[i] = z[i - 1].array() * points.row(2).array();
    }

    for (int x_deg = 0; x_deg <= 4; ++x_deg)
      for (int y_deg = 0; y_deg <= 4 - x_deg; ++y_deg)
        for (int z_deg = 0; z_deg <= 4 - x_deg - y_deg; ++z_deg) {
          const double target = wrapper.integrals(x_deg, y_deg, z_deg)(i);
          // Estimate the integral using points.
          const double estimate = (x[x_deg].array() * y[y_deg].array()
            * z[z_deg].array()).sum() * shape.area(i) / sample_num;
          const double target_abs = std::fabs(target);
          // Compare.
          if (std::fabs(estimate - target) >= std::max(target_abs * rel_threshold,
            abs_threshold)) {
            std::ostringstream ss;
            ss << "test::TestIntegral: integral differs too much: target = "
              << target << ", estimate = " << estimate << ". Integrating "
              << "x^" << x_deg << "y^" << y_deg << "z^" << z_deg << std::endl
              << "Triangle:" << std::endl
              << "v0 = " << v0.transpose() << std::endl
              << "v1 = " << v1.transpose() << std::endl
              << "v2 = " << v2.transpose();
            common::PrintError(ss.str());
          }
        }
  }

  std::cout << common::GreenHead() << "test::TestIntegral: OK."
    << common::GreenTail() << std::endl;
}

}
