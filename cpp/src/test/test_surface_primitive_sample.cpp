#include <algorithm>
#include <iostream>
#include <cmath>
#include <string>
#include "Eigen/Dense"
#include "common/file_helper.h"
#include "common/math_helper.h"
#include "primitive/toric_surface.h"
#include "primitive/conical_surface.h"

namespace test {

// Conf file:
// density: 10000
// min_dist: 0.1
// max_dist: 0.5
// rel_threshold: 0.01
void TestSurfacePrimitiveSample(const std::string& conf_file) {
  if (!common::HasExtension(conf_file, ".conf")) {
    common::PrintError("test::TestSurfacePrimitiveSample: incorrect conf file "
      "name: " + conf_file);
  }
  std::cout << "test::TestSurfacePrimitiveSample:" << std::endl;
  // Read conf file.
  std::map<std::string, std::string> kv_pairs;
  common::ReadConfFile(conf_file, kv_pairs);
  const double density = std::stod(kv_pairs.at("density"));
  const double min_dist = std::stod(kv_pairs.at("min_dist"));
  const double max_dist = std::stod(kv_pairs.at("max_dist"));
  const double rel_threshold = std::stod(kv_pairs.at("rel_threshold"));

  // Test cylinder.
  // TODO.

  // Test torus.
  const Eigen::Vector3d center(0, 1, 2);
  const Eigen::Vector3d axis(3, 4, 5);
  const double major_radii = 6.7, minor_radii = 1.89;
  const primitive::ToricSurface torus(center, axis, major_radii, minor_radii);
  // Try a sufficiently large bounding box.
  const Eigen::Vector3d pmin(-1000, -1000, -1000);
  const Eigen::Vector3d pmax(1000, 1000, 1000);
  std::vector<Eigen::Vector3d> samples;
  torus.Sample(min_dist, max_dist, pmin, pmax, density, samples);
  const double pi = common::Pi();
  const double r1 = minor_radii - max_dist, r2 = minor_radii - min_dist,
    r3 = minor_radii + min_dist, r4 = minor_radii + max_dist;
  const double vol = pi * (r4 * r4 - r3 * r3 + r2 * r2 - r1 * r1)
    * 2.0 * pi * major_radii;
  const int expected_sample_num = static_cast<int>(density * vol);
  const int actual_sample_num = static_cast<int>(samples.size());
  if ((expected_sample_num - actual_sample_num) >
    rel_threshold * expected_sample_num) {
    std::ostringstream ss;
    ss << "test::TestSurfacePrimitiveSample: sample number mismatch. Desired: "
      << expected_sample_num << ", actual: " << actual_sample_num;
    common::PrintError(ss.str());
  }
  for (auto& p : samples) {
    double dist = torus.DistToSurface(p);
    dist = (dist > 0) ? dist : -dist;
    if (dist < min_dist || dist > max_dist) {
      std::ostringstream ss;
      ss << "test::TestSurfacePrimitiveSample: sample goes outside band ."
        << "min dist: " << min_dist << ", max dist: " << max_dist
        << ", dist: " << dist;
      common::PrintError(ss.str());
    }
  }

  // Test cone.
  {
    const Eigen::Vector3d apex(-1.0, 2.0, -3.0);
    const Eigen::Vector3d axis(4.0, -5.0, 6.0);
    const double angle = common::Pi() / 6.0;
    const Eigen::Vector3d box_min;
    // TODO: finish this test.
  }
  common::PrintSuccess("test::TestSurfacePrimitiveSample: OK.");
}

}
