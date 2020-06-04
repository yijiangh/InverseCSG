#include "primitive/surface_primitive.h"
#include <cmath>
#include "common/math_helper.h"

namespace primitive {

std::vector<std::shared_ptr<SurfacePrimitive>>
SurfacePrimitive::primitive_instances
  = std::vector<std::shared_ptr<SurfacePrimitive>>(0);

SurfacePrimitive::SurfacePrimitive(const std::string& type_name,
  const Eigen::VectorXd& parameters)
  : parameters_(parameters), type_name_(type_name) {}

SurfacePrimitive::~SurfacePrimitive() {}

const std::string SurfacePrimitive::type_name() const {
  return type_name_;
}

const Eigen::VectorXd SurfacePrimitive::parameters() const {
  return parameters_;
}

const double SurfacePrimitive::Fit(const Eigen::Matrix3Xd& points,
  const Eigen::Matrix3Xd& normals) {
  // Gauss-Newton.
  const int n = static_cast<int>(parameters_.size());
  const int m = static_cast<int>(points.cols());
  assert(points.cols() == normals.cols());
  Eigen::VectorXd beta = InitialGuess(points, normals);
  const double inf = common::Infinity();
  if (!beta.allFinite()) {
    // Our initial guess is usually very good. If it fails, we think it is very
    // unlikely to fit the equation.
    return inf;
  }
  assert(beta.size() == parameters_.size());

  const int max_iter_num = 10;
  int iter_num = 0;
  const int max_ls_num = 10;
  const double eps = common::Epsilon();
  parameters_ = beta;
  Normalize();
  while (true) {
    // Evaluate r.
    Eigen::VectorXd r(m);
    for (int i = 0; i < m; ++i) {
      r(i) = Evaluate(points.col(i));
    }
    if (!r.allFinite()) {
      // Failure.
      return inf;
    }
    // Check if r is small enough.
    const double residual = r.squaredNorm();
    const double residual_l1 = r.cwiseAbs().maxCoeff();
    // Compute J and direction.
    Eigen::MatrixXd J(m, n);
    for (int i = 0; i < m; ++i) {
      J.row(i) = Gradient(points.col(i));
    }
    if (!J.allFinite()) {
      // Failure.
      return inf;
    }
    const Eigen::MatrixXd Jt = J.transpose();
    const Eigen::VectorXd dir = (Jt * J).ldlt().solve(Jt * r);
    if (!dir.allFinite() ||
      (Jt * J * dir - Jt * r).cwiseAbs().maxCoeff() >= eps) {
      return inf;
    }
    if (iter_num == max_iter_num || residual_l1 < eps ||
      dir.cwiseAbs().maxCoeff() < eps) {
      // We have used up all iterations, or we have a solution.
      return residual_l1;
    }
    // Line search.
    int ls_iter = 0;
    double step = 1.0;
    // Cache the old result.
    const Eigen::VectorXd old_parameter = parameters_;
    while (ls_iter < max_ls_num) {
      parameters_ = old_parameter - step * dir;
      Normalize();
      // Compute new r.
      Eigen::VectorXd new_r = r;
      for (int i = 0; i < m; ++i) {
        new_r(i) = Evaluate(points.col(i));
      }
      if (new_r.allFinite() && new_r.squaredNorm() < residual) {
        break;
      }
      step *= 0.5;
      ++ls_iter;
    }
    if (ls_iter == max_ls_num) {
      // Failed. Revert to the old result.
      parameters_ = old_parameter;
      return residual_l1;
    }
    ++iter_num;
  }
}

const bool SurfacePrimitive::IsOnSurface(const Eigen::Vector3d& point,
  const Eigen::Vector3d& normal, const double point_eps,
  const double normal_eps) const {
  const double f_val = std::fabs(Evaluate(point));
  if (f_val >= point_eps) return false;
  // Now check normal.
  const Eigen::Vector3d expected_normal = SurfaceNormal(point);
  const Eigen::Vector3d unit_normal = normal.normalized();
  return expected_normal.cross(unit_normal).norm() < normal_eps;
}

void SurfacePrimitive::Normalize() {
  // For most primitives just do nothing.
}

}
