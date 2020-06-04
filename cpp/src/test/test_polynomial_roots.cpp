#include <algorithm>
#include <iostream>
#include <cmath>
#include <string>
#include "Eigen/Dense"
#include "unsupported/Eigen/Polynomials"
#include "common/file_helper.h"
#include "common/math_helper.h"
#include "common/polynomial.h"

namespace test {

// Conf file:
// sample: 1000000
// abs_threshold: 1e-6
void TestPolynomialRoots(const std::string& conf_file) {
  if (!common::HasExtension(conf_file, ".conf")) {
    std::ostringstream ss;
    ss << "test::TestPolynomialRoots: incorrect conf file name: " << conf_file;
    common::PrintError(ss.str());
  }
  std::cout << "test::TestPolynomialRoots:" << std::endl;
  // Read conf file.
  std::map<std::string, std::string> kv_pairs;
  common::ReadConfFile(conf_file, kv_pairs);
  const int sample_num = std::stoi(kv_pairs.at("sample"));
  const double abs_threshold = std::stod(kv_pairs.at("abs_threshold"));

  // Easy cases.
  std::vector<double> solution;
  const common::Polynomial linear(1, 2);
  solution = linear.Roots();
  if (solution.size() != 1u || std::fabs(solution[0] + 0.5) > abs_threshold) {
    std::ostringstream ss;
    ss << "test::TestPolynomialRoots: expect root: -0.5, actual root: "
      << solution[0];
    common::PrintError(ss.str());
  }
  const common::Polynomial quadratic = linear * linear;
  solution = quadratic.Roots();
  if (solution.empty()) {
    common::PrintError("test::TestPolynomialRoots: expect to see -0.5 "
      "but got none.");
  }
  for (const double d : solution) {
    if (std::fabs(d + 0.5) > abs_threshold) {
      std::ostringstream ss;
      ss << "test::TestPolynomialRoots: expect root: -0.5, actual root: "
        << d;
      common::PrintError(ss.str());
    }
  }
  const common::Polynomial linear2(1, -2);
  const common::Polynomial quadratic2 = linear * linear2;
  solution = quadratic2.Roots();
  if (solution.size() != 2u || std::fabs(solution[0] + 0.5) > abs_threshold ||
    std::fabs(solution[1] - 0.5) > abs_threshold) {
    std::ostringstream ss;
    ss << "test::TestPolynomialRoots: expect root: (-0.5, 0.5), actual root:";
    for (const double d : solution) ss << " " << d;
    common::PrintError(ss.str());
  }
  const common::Polynomial quadratic3 = quadratic2 - 10000;
  solution = quadratic3.Roots();
  if (!solution.empty()) {
    std::ostringstream ss;
    ss << "test::TestPolynomialRoots: expect zero root. actual root:";
    for (const double d : solution) ss << " " << d;
    common::PrintError(ss.str());
  }
  // Random tests.
  for (int i = 0; i < sample_num; ++i) {
    // Randomly generate a 6th order polynomials.
    const Eigen::VectorXd random_roots = Eigen::VectorXd::Random(6);
    // Sort random_roots.
    std::vector<double> sorted_roots(random_roots.data(),
      random_roots.data() + random_roots.size());
    std::sort(sorted_roots.begin(), sorted_roots.end());
    Eigen::VectorXd params;
    Eigen::roots_to_monicPolynomial(random_roots, params);
    const common::Polynomial poly(params);
    const std::vector<double> roots = poly.Roots();
    if (roots.size() != 6u) {
      std::ostringstream ss;
      ss << "test::TestPolynomialRoots: expect to see 6 roots but got "
        << roots.size();
      common::PrintError(ss.str());
    }
    for (int i = 0; i < 6; ++i) {
      if (std::fabs(roots[i] - sorted_roots[i]) > abs_threshold) {
        std::ostringstream ss;
        ss << "test::TestPolynomialRoots: roots are different: " << roots[i]
          << ", " << sorted_roots[i];
        common::PrintError(ss.str());
      }
    }
    for (const double r : roots) {
      const double f_of_r = poly(r);
      if (std::fabs(f_of_r) > abs_threshold) {
        std::ostringstream ss;
        ss << "test::TestPolynomialRoots: " << r << " is not a root. f(" << r
          << ") = " << f_of_r << ". f = " << params.transpose();
        common::PrintError(ss.str());
      }
    }
  }
  std::cout << common::GreenHead() << "test::TestPolynomialRoots: OK."
    << common::GreenTail() << std::endl;
}

}
