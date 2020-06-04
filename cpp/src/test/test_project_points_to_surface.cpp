#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include "Eigen/Dense"
#include "common/math_helper.h"
#include "common/file_helper.h"
#include "vsa/quadratic_surface.h"
#include "vsa/vsa_tri_mesh_wrapper.h"
#include "mesh/tri_mesh.h"

namespace test {

// CONF file:
// sample: 1000
// abs_threshold: 1e-5
void TestProjectPointsToSurface(const std::string& conf_file) {
  std::cout << "test::TestProjectPointsToSurface:" << std::endl;
  // Read configuration file.
  std::map<std::string, std::string> kv_pairs;
  common::ReadConfFile(conf_file, kv_pairs);
  const int sample_num = std::stoi(kv_pairs.at("sample"));
  const double abs_threshold = std::stod(kv_pairs.at("abs_threshold"));

  mesh::TriMesh dummy_shape;
  vsa::VsaTriMeshWrapper dummy_wrapper(dummy_shape);
  vsa::QuadraticSurface sphere(dummy_wrapper);
  Eigen::VectorXd sp_params = Eigen::VectorXd::Zero(10);
  const double radius = 2.0;
  sp_params(0) = -radius * radius;
  sp_params(4) = sp_params(7) = sp_params(9) = 1;
  sphere.set_parameters(sp_params);
  // x^2 + y^2 + z^2 = 4.
  const Eigen::Matrix3Xd random_points =
    Eigen::Matrix3Xd::Random(3, sample_num) * 3;
  Eigen::Matrix3Xd projected = sphere.ProjectPointsToSurface(random_points);
  for (int i = 0; i < sample_num; ++i) {
    const Eigen::Vector3d p = random_points.col(i);
    const Eigen::Vector3d q = projected.col(i);
    const double f_q = sphere.Evaluate(q);
    if (std::fabs(f_q) > abs_threshold) {
      std::ostringstream ss;
      ss << "test::TestProjectPointsToSurface: point is not on the surface: "
        << "p = " << p.transpose();
      common::PrintError(ss.str());
    }
    const Eigen::Vector3d expected_p = p / p.norm() *radius;
    if ((q - expected_p).norm() > abs_threshold) {
      std::ostringstream ss;
      ss << "test::TestProjectPointsToSurface: projected point is not as "
        "expected: expect = " << expected_p.transpose() << ", actual = "
        << q.transpose();
      common::PrintError(ss.str());
    }
  }
  std::cout << common::GreenHead() << "test::TestProjectPointsToSurface: OK."
    << common::GreenTail() << std::endl;
}

}
