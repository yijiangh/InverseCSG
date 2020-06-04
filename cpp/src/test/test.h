#ifndef _TEST_TEST_H_
#define _TEST_TEST_H_

#include <string>

namespace test {

void TestCommand(const bool all, const std::string& conf_file,
  const std::string& root, const bool help, const std::string& test_name,
  const std::string& scene);

// All test cases.
void TestComputeLevelSet(const std::string& conf_file, const std::string& root,
  const std::string& scene);
void TestGenerateRandomInts();
void TestGradNormVector(const std::string& conf_file, const std::string& root,
  const std::string& scene);
void TestInitializeSurfaceParameters(const std::string& conf_file,
  const std::string& root, const std::string& scene);
void TestIntegral(const std::string& conf_file, const std::string& root,
  const std::string& scene);
void TestIntersect(const std::string& conf_file, const std::string& root,
  const std::string& scene);
void TestIsInside(const std::string& root, const std::string& scene);
void TestLinearLeastSquarePlaneFit(const std::string& conf_file,
  const std::string& root, const std::string& scene);
void TestL2Matrix(const std::string& conf_file, const std::string& root,
  const std::string& scene);
void TestL21Matrix(const std::string& conf_file, const std::string& root,
  const std::string& scene);
void TestPolynomialRoots(const std::string& conf_file);
void TestProjectPointsToSurface(const std::string& conf_file);
void TestSurfacePrimitiveSample(const std::string& conf_file);

}

#endif
