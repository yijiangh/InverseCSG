#include <iostream>
#include <string>
#include "Eigen/Dense"
#include "common/math_helper.h"
#include "common/file_helper.h"

namespace test {

void TestGenerateRandomInts() {
  std::cout << "test::TestGenerateRandomInts:" << std::endl;
  // With replacement.
  {
    const int lower = -10, upper = 10;
    const int sample_num = 1000000;
    const double threshold = 0.05;
    const std::vector<int> samples = common::GenerateRandomInts(lower, upper,
      sample_num, true);
    Eigen::VectorXd frequency = Eigen::VectorXd::Zero(upper - lower);
    for (const int sample : samples) {
      frequency(sample - lower) += 1.0;
    }
    frequency /= static_cast<double>(sample_num);
    const double expected = 1.0 / (upper - lower);
    if ((frequency.array() - expected).cwiseAbs().maxCoeff()
      > threshold * expected) {
      std::cerr << common::RedHead()
        << "test::GenerateRandomInts: samples are not uniform:" << std::endl
        << "expected: " << expected << std::endl
        << "actual: " << frequency.transpose() << std::endl
        << common::RedTail() << std::endl;
      exit(-1);
    }
  }
  // Without replacement.
  {
    const int lower = -10000, upper = 10000;
    const std::vector<int> samples = common::GenerateRandomInts(lower, upper,
      upper - lower);
    std::vector<bool> flag(upper - lower, false);
    if (static_cast<int>(samples.size()) != upper - lower) {
      common::PrintError("test::GenerateRandomInts: not enough samples.");
    }
    for (const int sample : samples) {
      if (flag[sample - lower]) {
        common::PrintError("test::GenerateRandomInts: duplicated samples.");
      }
      flag[sample - lower] = true;
    }
  }
  std::cout << common::GreenHead() << "test::GenerateRandomInts: OK."
    << common::GreenTail() << std::endl;
}

}
