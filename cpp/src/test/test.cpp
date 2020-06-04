#include "test/test.h"
#include <iostream>
#include <string>
#include <vector>
#include "common/file_helper.h"

namespace test {

void TestCommand(const bool all, const std::string& conf_file,
  const std::string& root, const bool help, const std::string& test_name,
  const std::string& scene) {
  if (!common::HasExtension(conf_file, ".conf")) {
    std::cerr << common::RedHead() << "test::TestCommand: wrong conf file: "
      << conf_file << common::RedTail() << std::endl;
    exit(-1);
  }

  // Whenever we add a new test case, we need to update this vector of strings.
  const std::vector<std::string> all_test_names = {
    "ComputeLevelSet",
    "GenerateRandomInts",
    "GradNormVector",
    "InitializeSurfaceParameters",
    "Integral",
    "Intersect",
    "IsInside",
    "LinearLeastSquarePlaneFit",
    "L2Matrix",
    "L21Matrix",
    "PolynomialRoots",
    "ProjectPointsToSurface",
    "SurfacePrimitiveSample"
  };

  if (help) {
    std::cout
      << "test                Run test cases." << std::endl
      << "  -a                Run all test cases." << std::endl
      << "  -c <CONF file>    Test configuration file." << std::endl
      << "  -d <directory>    Location of root folder (the one having README.md)."
      << std::endl
      << "  -h                Print help information." << std::endl
      << "  -n <string>       Run one test case with specified name." << std::endl
      << "  -s <string>       Run one example scene with specified name."
      << std::endl << std::endl
      << "All test case names:" << std::endl;
    for (const auto& name : all_test_names) {
      std::cout << name << std::endl;
    }
    std::cout << std::endl;
    return;
  }
  if (all) {
    // Run all tests.
    TestComputeLevelSet(conf_file, root, scene);
    TestGenerateRandomInts();
    TestGradNormVector(conf_file, root, scene);
    TestInitializeSurfaceParameters(conf_file, root, scene);
    TestIntegral(conf_file, root, scene);
    TestIntersect(conf_file, root, scene);
    TestIsInside(root, scene);
    TestLinearLeastSquarePlaneFit(conf_file, root, scene);
    TestL2Matrix(conf_file, root, scene);
    TestL21Matrix(conf_file, root, scene);
    TestPolynomialRoots(conf_file);
    TestProjectPointsToSurface(conf_file);
    TestSurfacePrimitiveSample(conf_file);
    // Add more tests here.
    return;
  }
  // Run one particular test.
  if (test_name == "ComputeLevelSet") {
    TestComputeLevelSet(conf_file, root, scene);
  } else if (test_name == "GenerateRandomInts") {
    TestGenerateRandomInts();
  } else if (test_name == "GradNormVector") {
    TestGradNormVector(conf_file, root, scene);
  } else if (test_name == "InitializeSurfaceParameters") {
    TestInitializeSurfaceParameters(conf_file, root, scene);
  } else if (test_name == "Integral") {
    TestIntegral(conf_file, root, scene);
  } else if (test_name == "Intersect") {
    TestIntersect(conf_file, root, scene);
  } else if (test_name == "IsInside") {
    TestIsInside(root, scene);
  } else if (test_name == "LinearLeastSquarePlaneFit") {
    TestLinearLeastSquarePlaneFit(conf_file, root, scene);
  } else if (test_name == "L2Matrix") {
    TestL2Matrix(conf_file, root, scene);
  } else if (test_name == "L21Matrix") {
    TestL21Matrix(conf_file, root, scene);
  } else if (test_name == "PolynomialRoots") {
    TestPolynomialRoots(conf_file);
  } else if (test_name == "ProjectPointsToSurface") {
    TestProjectPointsToSurface(conf_file);
  } else if (test_name == "SurfacePrimitiveSample") {
    TestSurfacePrimitiveSample(conf_file);
  } else {
    std::cerr << common::RedHead() << "test::TestCommand: unsupported name: "
      << test_name << common::RedTail() << std::endl;
    exit(-1);
  }
}

}
