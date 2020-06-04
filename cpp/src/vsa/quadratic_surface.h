#ifndef _VSA_QUADRATIC_SURFACE_H_
#define _VSA_QUADRATIC_SURFACE_H_

// See paper "Variational mesh segmentation via quadric surface fitting"
// Dong-Ming Yan, Wenping Wang, Yang Liu, Zhuowang Yang
// Computer-Aided Design

#include "Eigen/Dense"
#include "vsa/vsa_tri_mesh_wrapper.h"
#include "test/test.h"

namespace vsa {

class QuadraticSurface {
public:
  QuadraticSurface(const VsaTriMeshWrapper& shape);

  const Eigen::VectorXd parameters() const;
  void set_parameters(const Eigen::VectorXd& parameters);

  // A region consists of a list of indices of triangles that tentatively
  // belong to this quadratic surface. The parameters will get updated at the
  // end of this function. See section 3.2.1 in the paper.
  void InitializeSurfaceParameters(const std::vector<int>& region);
  // Implement the linear least square fitting in section 3.2.2. Make sure to
  // call InitializeSurfaceParameters before calling LeastSquareFit. In this
  // way we will get a good initial guess. The parameters will get updated at
  // the end of this function.
  void LeastSquareFit(const std::vector<int>& region, const double omega);
  // These two functions approximate L2 + omega * L21 using the barycenter of
  // each triangle.
  const double Energy(const std::vector<int>& region, const double omega) const;
  const double Energy(const int triangle_id, const double omega) const;

  // (x, y, z) -> (1, x, y, z, x2, xy, xz, y2, yz, z2).
  const Eigen::VectorXd AugmentedPoint(const Eigen::Vector3d& point) const;
  const double Evaluate(const Eigen::Vector3d& point) const;
  const Eigen::Vector3d Gradient(const Eigen::Vector3d& point) const;

  const Eigen::Vector3d ProjectPointToSurface(
    const Eigen::Vector3d& point) const;
  const Eigen::Matrix3Xd ProjectPointsToSurface(
    const Eigen::Matrix3Xd& points) const;

  // Allow test functions to access private functions.
  friend void test::TestLinearLeastSquarePlaneFit(const std::string& conf_file,
    const std::string& root, const std::string& scene);

private:
  // Fit a plane that is a global minimum of L2 + w * L21. See section 3.3 for
  // more details.
  // plane = [d, nx, ny, nz] represents d + nx * x + ny * y + nz * z = 0.
  // Technically this function gives you the true global minimum but it involves
  // (potentially expensive and unreliable) binary search and golden section
  // search, and it has not been tested.
  void NonlinearLeastSquarePlaneFit(const std::vector<int>& region,
    const double omega, Eigen::Vector4d& plane, double& energy) const;
  // This function uses linear least square method to fit all vertices. It is
  // not exactly the global minimum of the L2 + omega * L21 energy but should
  // be faster and more reliable (and practically very close to the true global
  // minimum if the region is indeed a plane).
  void LinearLeastSquarePlaneFit(const std::vector<int>& region,
    const double omega, Eigen::Vector4d& plane, double& energy) const;

  const VsaTriMeshWrapper& shape_;
  Eigen::VectorXd parameters_;
};

}

#endif
