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
// sample: 10000
// abs_threshold: 1e-3
// rel_threshold: 0.01
// omega: 0.5
void TestLinearLeastSquarePlaneFit(const std::string& conf_file,
  const std::string& root, const std::string& scene) {
  if (!common::HasExtension(conf_file, ".conf")) {
    std::ostringstream ss;
    ss << "test::TestLinearLeastSquarePlaneFit: incorrect conf file name: "
      << conf_file;
    common::PrintError(ss.str());
  }
  std::cout << "test::TestLinearLeastSquarePlaneFit:" << std::endl;
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
  const double abs_threshold = std::stod(kv_pairs.at("abs_threshold"));
  const double rel_threshold = std::stod(kv_pairs.at("rel_threshold"));
  const double omega = std::stod(kv_pairs.at("omega"));

  mesh::TriMesh shape;
  shape.Initialize(mesh_path);
  vsa::VsaTriMeshWrapper wrapper(shape);

  // Fit a single plane.
  const std::vector<int> region = common::GenerateRandomInts(0,
    shape.NumOfFaces(), face_num);
  vsa::QuadraticSurface quad(wrapper);
  Eigen::Vector4d plane;
  double energy = 0.0;
  quad.LinearLeastSquarePlaneFit(region, omega, plane, energy);
  // Now, if I assign plane to the parameter and call Energy, I should see the
  // same energy value.
  Eigen::VectorXd params = Eigen::VectorXd::Zero(10);
  params.head(4) = plane;
  quad.set_parameters(params);
  const double quad_energy = quad.Energy(region, omega);
  if (std::fabs(energy - quad_energy) > std::max(abs_threshold,
    rel_threshold * quad_energy)) {
    std::cerr << common::RedHead() << "test::TestLinearLeastSquarePlaneFit: "
      << "energies mismatch: " << energy << ", " << quad_energy << "."
      << common::RedTail() << std::endl;
    exit(-1);
  }

  // Second, if we ask quad to fit all triangles, the error should be very tiny.
  for (int i = 0; i < sample_num; ++i) {
    const int face_idx = common::GenerateRandomInt(0, shape.NumOfFaces());
    const std::vector<int> region  = { face_idx };
    plane.setZero();
    energy = 0.0;
    quad.LinearLeastSquarePlaneFit(region, omega, plane, energy);
    if (energy > abs_threshold) {
      std::cerr << common::RedHead() << "test::TestLinearLeastSquarePlaneFit: "
        << "failed to fit a perfect plane: " << energy << "."
        << common::RedTail() << std::endl;
      exit(-1);
    }
  }
  std::cout << common::GreenHead() << "test::TestLinearLeastSquarePlaneFit: OK."
    << common::GreenTail() << std::endl;
}

}
