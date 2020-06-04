#include "quadratic_surface.h"
#include <algorithm>
#include <sstream>
#include <cmath>
#include <unordered_set>
#include "common/math_helper.h"
#include "common/file_helper.h"
#include "common/polynomial.h"

namespace vsa {

static const bool Close(const Eigen::VectorXd& a, const Eigen::VectorXd& b) {
  const double eps = common::Epsilon();
  const double abs_error = (a - b).norm();
  const double rel_error = abs_error
    / (std::min(a.norm(), b.norm()) + eps);
  // TODO: remove this magic number.
  return abs_error < 1e-3 * std::sqrt(static_cast<double>(a.size()))
    || rel_error < 5e-2;
}

// Find the minimum lambda for A * c = lambda * B * c.
static const bool SolveGeneralizedEigenProblem(const Eigen::MatrixXd& A,
  const Eigen::MatrixXd& B, double& lambda, Eigen::VectorXd& c) {
  lambda = 0.0;
  c = Eigen::VectorXd::Zero(B.cols());
  if (!A.allFinite() || !B.allFinite()) {
    return false;
  }
  // Scale A and B for better numerical stability.
  const double scale = 1.0 / std::max(B.norm(), common::Epsilon());
  // Casting them to doubles for better numerical stabilities.
  const Eigen::GeneralizedEigenSolver<Eigen::MatrixXd> solve(
    A * scale, B * scale);
  const Eigen::VectorXcd alphas = solve.alphas();
  const Eigen::VectorXcd betas = solve.betas();
  const Eigen::MatrixXcd eigenvectors = solve.eigenvectors();
  if (!alphas.allFinite() || !betas.allFinite() || !eigenvectors.allFinite()) {
    return false;
  }
  // Now loop over and pick the smallest eigenvalue.
  lambda = common::Infinity();
  const double eps = common::Epsilon();
  for (auto i = 0; i < alphas.size(); ++i) {
    const Eigen::VectorXcd v = eigenvectors.col(i);
    if (v.imag().cwiseAbs().maxCoeff() > eps) continue;
    // Now v is (almost) real, the eigenvalues must be real as well.
    const double alpha_real = alphas(i).real(), alpha_imag = alphas(i).imag();
    const double beta_real = betas(i).real(), beta_imag = betas(i).imag();
    const double alpha_norm = std::sqrt(alpha_real * alpha_real
      + alpha_imag * alpha_imag);
    const double beta_norm = std::sqrt(beta_real * beta_real
      + beta_imag * beta_imag);
    if (beta_norm < common::Epsilon()) continue;
    const double candidate = alpha_norm / beta_norm;
    if (candidate < lambda) {
      lambda = candidate;
      c = v.real();
    }
  }
  // Check lambda and c.
  const Eigen::VectorXd left = (A * scale) * c,
    right = lambda * (B * scale) * c;
  const bool good = lambda != common::Infinity() && Close(left, right);
  return good;
}

QuadraticSurface::QuadraticSurface(const VsaTriMeshWrapper& shape)
  : shape_(shape), parameters_(Eigen::VectorXd::Zero(10)) {}

const Eigen::VectorXd QuadraticSurface::parameters() const {
  return parameters_;
}

void QuadraticSurface::set_parameters(const Eigen::VectorXd& parameters) {
  parameters_ = parameters;
}

void QuadraticSurface::InitializeSurfaceParameters(
  const std::vector<int>& region) {
  Eigen::MatrixXd Mt, Nt;
  const int dim = 10;
  Mt = Nt = Eigen::MatrixXd::Zero(dim, dim);
  for (const int idx : region) {
    Mt += shape_.l2_matrix(idx);
    Nt += shape_.l21_matrix(idx);
  }
  if (!Mt.allFinite() || !Nt.allFinite()) {
    common::PrintError("vsa::QuadraticSurface::InitializeSurfaceParameters: "
      "inf or nan in Mt or Nt.");
  }
  // Minimizing lambda := (c' * Mt * c) / (c' * Nt * c).
  // Both Mt and Nt are symmetric, nonnegative matrices because of the way they
  // are constructed.
  // Taking the derivative gives us:
  // Mt * c * (c' * Nt * c) = Nt * c * (c' * Mt * c).
  // or equivalently Mt * c = lambda * Nt * c.
  // As a result, our goal is to find the smallest eigenvalue.
  // In theory, as long as the triangle area is positive, we are certain Mt is
  // strictly positive definite. On the other hand, Nt is semi-definite for
  // sure. So it is actually easier to solve:
  // Nt * c = mu * Mt * c.
  // In practice, however, this does not work very well due to numerical issues.
  // As a result, we will use the generalized eigen solver in Eigen.
  double lambda = 0.0;
  Eigen::VectorXd c;
  if (!SolveGeneralizedEigenProblem(Mt, Nt, lambda, c)) {
    // Failed to use the generalized eigensolver.
    common::PrintWarning("vsa::QuadraticSurface::InitializeSurfaceParameters: "
      "failed to solve the generalized eigen problem, switched to linear "
      "least square fit.");
    std::unordered_set<int> pool;
    for (const int fid : region)
      for (int i = 0; i < 3; ++i)
        pool.insert(shape_.shape().face(fid)(i));
    Eigen::MatrixXd A(pool.size(), 10);
    int count = 0;
    for (const int vid : pool) {
      A.row(count) = AugmentedPoint(shape_.shape().vertex(vid));
      ++count;
    }
    // min |Ac| s.t. |c| = 1.
    const Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> solve(
      A.transpose() * A);
    if (!solve.eigenvalues().allFinite()) {
      common::PrintError("vsa::QuadraticSurface::InitializeSurfaceParameters: "
        "failed to find the eigenvalues");
    }
    int idx = -1;
    solve.eigenvalues().minCoeff(&idx);
    c = solve.eigenvectors().col(idx);
  }
  parameters_ = c / c.norm();
}

void QuadraticSurface::LeastSquareFit(const std::vector<int>& region,
  const double omega) {
  // First, attempt to fit a plane based on the L2 and L21 energy.
  // See section 3.3 for details.
  Eigen::Vector4d plane = Eigen::Vector4d::Zero();
  double energy = 0.0;
  LinearLeastSquarePlaneFit(region, omega, plane, energy);
  if (energy < common::Epsilon()) {
    parameters_.setZero();
    parameters_.head(4) = plane;
    parameters_ /= parameters_.norm();
    return;
  }

  // If the above plane fails, we try quadratic surfaces.
  Eigen::MatrixXd A = Eigen::MatrixXd::Zero(10, 10);
  Eigen::VectorXd B = Eigen::VectorXd::Zero(10);
  for (const int idx : region) {
    const Eigen::Vector3d c = shape_.shape().Triangle(idx).rowwise().mean();
    const Eigen::Vector3d grad_fc = Gradient(c);
    const double inv_grad_fc = 1.0 / grad_fc.norm();
    const double inv_grad_fc_sq = inv_grad_fc * inv_grad_fc;
    A += inv_grad_fc_sq * shape_.l2_matrix(idx);
    A += omega * inv_grad_fc_sq * shape_.l21_matrix(idx);
    B += omega * inv_grad_fc * shape_.grad_norm_vector(idx);
  }
  // A * C = B.
  // As long as at least one triangle has nonzero area, A is positive definite.
  // Otherwise it is positive semi-definite.
  if (!A.allFinite() || !B.allFinite()) {
    common::PrintError("vsa::QuadraticSurface::LeastSquareFit: nan in A and B");
  }
  const Eigen::VectorXd c = A.colPivHouseholderQr().solve(B);
  // Verify the solution.
  const Eigen::VectorXd left = A * c, right = B;
  if (!c.allFinite() || !Close(left, right)) {
    std::cerr << common::RedHead() << "vsa::LeastSquareFit: "
      "failed to solve the linear system." << std::endl
      << "left: " << left.norm() << ", right: " << right.norm()
      << ", diff: " << (left - right).norm() << common::RedTail() << std::endl;
    exit(-1);
  }
  parameters_ = c / c.norm();
}

const double QuadraticSurface::Energy(const std::vector<int>& region,
  const double omega) const {
  double energy = 0.0;
  for (const int idx : region) {
    const Eigen::Vector3d c = shape_.shape().Triangle(idx).rowwise().mean();
    const Eigen::Vector3d grad_fc = Gradient(c);
    const double grad_fc_norm = grad_fc.norm();
    const double inv_grad_fc = 1.0 / grad_fc_norm;
    const double inv_grad_fc_sq = inv_grad_fc * inv_grad_fc;
    // If grad is singular, we skip this mesh.
    if (!Eigen::Vector2d(inv_grad_fc, inv_grad_fc_sq).allFinite()) continue;
    const Eigen::VectorXd& p = parameters_;
    // L2 energy.
    energy += inv_grad_fc_sq * p.dot(shape_.l2_matrix(idx) * p);
    // L21 energy.
    const Eigen::Vector3d nt = shape_.shape().face_normal(idx);
    energy += omega * (inv_grad_fc_sq * p.dot(shape_.l21_matrix(idx) * p) -
      2.0 * inv_grad_fc * p.dot(shape_.grad_norm_vector(idx)) +
      nt.squaredNorm() * shape_.shape().area(idx));
  }
  return energy;
}

const double QuadraticSurface::Energy(const int triangle_id,
  const double omega) const {
  return Energy(std::vector<int>(1, triangle_id), omega);
}

const Eigen::VectorXd QuadraticSurface::AugmentedPoint(
  const Eigen::Vector3d& point) const {
  const double x = point.x(), y = point.y(), z = point.z();
  Eigen::VectorXd f(10);
  f << 1.0, x, y, z, x * x, x * y, x * z, y * y, y * z, z * z;
  return f;
}

const double QuadraticSurface::Evaluate(const Eigen::Vector3d& point) const {
  return parameters_.dot(AugmentedPoint(point));
}

const Eigen::Vector3d QuadraticSurface::Gradient(
  const Eigen::Vector3d& point) const {
  const double x = point.x(), y = point.y(), z = point.z();
  Eigen::Vector3d grad;
  Eigen::VectorXd fx(10), fy(10), fz(10);
  fx << 0.0, 1.0, 0.0, 0.0, 2.0 * x, y, z, 0.0, 0.0, 0.0;
  fy << 0.0, 0.0, 1.0, 0.0, 0.0, x, 0.0, 2.0 * y, z, 0.0;
  fz << 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, x, 0.0, y, 2.0 * z;
  grad.x() = parameters_.dot(fx);
  grad.y() = parameters_.dot(fy);
  grad.z() = parameters_.dot(fz);
  return grad;
}

const Eigen::Vector3d QuadraticSurface::ProjectPointToSurface(
  const Eigen::Vector3d& point) const {
  // Not sure Vector3d can be directly converted to Matrix3Xd so I will do it
  // in the safest way.
  Eigen::Matrix3Xd points = Eigen::Matrix3Xd::Zero(3, 1);
  points.col(0) = point;
  return ProjectPointsToSurface(points).col(0);
}

const Eigen::Matrix3Xd QuadraticSurface::ProjectPointsToSurface(
  const Eigen::Matrix3Xd& points) const {
  // Write the surface as 0.5 * x'Ax + bx + c.
  const double c = parameters_(0);
  Eigen::Vector3d b = parameters_.segment(1, 3);
  Eigen::Matrix3d A0 = Eigen::Matrix3d::Zero();
  A0.row(0) = parameters_.segment(4, 3);
  A0.row(1).tail(2) = parameters_.segment(7, 2);
  A0(2, 2) = parameters_(9);
  // Now f(x) = x'Ax + bx + c.
  const Eigen::Matrix3d A = A0 + A0.transpose();
  // Now f(x) = 0.5x'Ax + bx + c.
  const Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> solve(A);
  const Eigen::Matrix3d V = solve.eigenvectors();
  const Eigen::Vector3d S = solve.eigenvalues();
  // Now AV = VS, or A = VSV'.
  // Let x = Vy.
  // g(y) = f(x) = 0.5x'VSV'x + bx + c = 0.5y'Sy + bVy + c.
  b = V.transpose() * b;
  // Now g(y) = 0.5y'Sy + by + c.
  const Eigen::Matrix3Xd new_points = V.transpose() * points;
  // Now you want to see min |y - new_points| s.t. 0.5y'Sy + by + c = 0.
  // Taking the derivatives gives us:
  // 2 * (y - new_points) + u * (Sy + b) = 0.
  // 0.5y'Sy + by + c = 0.
  const int point_num = static_cast<int>(new_points.cols());
  Eigen::VectorXd u = Eigen::VectorXd::Zero(point_num);
  Eigen::Matrix3Xd projected = Eigen::Matrix3Xd::Zero(3, point_num);
  for (int i = 0; i < point_num; ++i) {
    const Eigen::Vector3d p = new_points.col(i);
    // 2y - 2p + uSy + ub = 0.
    // (2 + uS)y = 2p - ub.
    // Define y = (2p - ub) / (2 + uS) := a(u) / b(u).
    const common::Polynomial a0(2 * p(0), -b(0)), a1(2 * p(1), -b(1)),
      a2(2 * p(2), -b(2));
    const common::Polynomial b0(2, S(0)), b1(2, S(1)), b2(2, S(2));
    const common::Polynomial a0sq = a0 * a0, a1sq = a1 * a1, a2sq = a2 * a2;
    const common::Polynomial b0sq = b0 * b0, b1sq = b1 * b1, b2sq = b2 * b2;
    // Solving \sum_i ai^2 * Si * 0.5 / bi^2 + b(i) * ai / bi + c.
    const common::Polynomial poly = S(0) * 0.5 * a0sq * b1sq * b2sq
      + S(1) * 0.5 * a1sq * b0sq * b2sq + S(2) * 0.5 * a2sq * b0sq * b1sq
      + b(0) * a0 * b0 * b1sq * b2sq + b(1) * a1 * b0sq * b1 * b2sq
      + b(2) * a2 * b0sq * b1sq * b2 + c * b0sq * b1sq * b2sq;
    const std::vector<double> roots = poly.Roots();
    if (roots.empty()) {
      std::ostringstream ss;
      ss << "vsa::ProjectPointsToSurface: failed to solve the polynomials. "
        << "point = " << p.transpose()
        << " surface = " << parameters_.transpose();
      common::PrintError(ss.str());
    }
    // Pick the best one.
    double min_dist = common::Infinity();
    Eigen::Vector3d min_y = Eigen::Vector3d::Constant(common::Infinity());
    for (const double u : roots) {
      const Eigen::Vector3d y = (2 * p - u * b).array() / (u * S.array() + 2);
      if (y.allFinite() && (y - p).squaredNorm() < min_dist) {
        min_dist = (y - p).squaredNorm();
        min_y = y;
      }
    }
    if (!min_y.allFinite()) {
      std::ostringstream ss;
      ss << "vsa::ProjectPointsToSurface: failed to project the point. "
        << "point = " << p.transpose()
        << " surface = " << parameters_.transpose();
      common::PrintError(ss.str());
    }
    projected.col(i) = V * min_y;
  }
  return projected;
}

// This function has not been fully tested. Use it with caution!
void QuadraticSurface::NonlinearLeastSquarePlaneFit(
  const std::vector<int>& region, const double omega, Eigen::Vector4d& plane,
  double& energy) const {
  Eigen::Vector3d c = Eigen::Vector3d::Zero();
  double d_factor = 0.0;
  for (const int idx : region) {
    const double t = shape_.shape().area(idx);
    const Eigen::Matrix3d triangle = shape_.shape().Triangle(idx);
    for (int i = 0; i < 3; ++i) {
      const Eigen::Vector3d vi = triangle.col(i);
      for (int j = i; j < 3; ++j) {
        const Eigen::Vector3d vj = triangle.col(j);
        d_factor += t / 3.0;
        c += (vi + vj) * t / 6.0;
      }
    }
  }
  // Now c.dot(n) + d * d_factor = 0.
  c /= -d_factor;
  // Now d = c.dot(n).
  if (!c.allFinite()) {
    common::PrintError("vsa::QuadraticSurface::NonlinearLeastSquarePlaneFit: "
      "singular triangles.");
  }
  // Now we want to take the derivative of n.
  Eigen::Matrix3d A = Eigen::Matrix3d::Zero();
  Eigen::Vector3d b = Eigen::Vector3d::Zero();
  for (const int idx : region) {
    const double t = shape_.shape().area(idx);
    const Eigen::Matrix3d triangle = shape_.shape().Triangle(idx);
    const Eigen::Vector3d nt = shape_.shape().face_normal(idx);
    for (int i = 0; i < 3; ++i) {
      const Eigen::Vector3d vi = triangle.col(i) + c;
      for (int j = i; j < 3; ++j) {
        const Eigen::Vector3d vj = triangle.col(j) + c;
        A += t / 6.0 * (vi * vj.transpose() + vj * vi.transpose());
      }
    }
    b += 2.0 * t * omega * nt;
  }
  // We solve A * n + lambda * n = b and |n| = 1.
  // Here we are sure A is strictly positive definite.
  const Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> solver(A);
  const Eigen::Vector3d sigma = solver.eigenvalues();
  const Eigen::Matrix3d V = solver.eigenvectors();
  // A * V = V * sigma.
  // A = V * sigma * V'.
  // Now (sigma + lambda) * V'n = V'b.
  const Eigen::Vector3d vb = V.transpose() * b;
  // Let x = V'n, we have:
  // (sigma + lambda) x = vb.
  // Now we are solving:
  // \sum_i vb(i)^2 / (sigma(i) + lambda)^2 = 1.
  const common::Polynomial vb0(vb(0) * vb(0)), vb1(vb(1) * vb(1)),
    vb2(vb(2) * vb(2));
  const common::Polynomial sl0(sigma(0), 1), sl1(sigma(1), 1), sl2(sigma(2), 1);
  const common::Polynomial sl0sq = sl0 * sl0, sl1sq = sl1 * sl1,
    sl2sq = sl2 * sl2;
  common::Polynomial poly = vb0 * sl1sq * sl2sq + vb1 * sl0sq * sl2sq
    + vb2 * sl0sq * sl1sq - sl0sq * sl1sq * sl2sq;
  const std::vector<double> roots = poly.Roots();
  if (roots.size() < 2u) {
    common::PrintError("vsa::QuadraticSurface::NonlinearLeastSquarePlaneFit: "
      "expect to see at least two roots.");
  }
  const double eps = common::Epsilon();
  energy = common::Infinity();
  plane.setZero();
  for (const double lambda : roots) {
    const Eigen::Vector3d x = vb.array() / (sigma.array() + lambda);
    const Eigen::Vector3d n = V.transpose() * x;
    if (std::fabs(n.norm() - 1.0) > eps) {
      common::PrintError("vsa::QuadraticSurface::NonlinearLeastSquarePlaneFit: "
        "expect to see a unit norm.");
    }
    const double d = c.dot(n);
    // Evaluate.
    double n_energy = 0.0;
    for (const int idx : region) {
      const double t = shape_.shape().area(idx);
      const Eigen::Matrix3d triangle = shape_.shape().Triangle(idx);
      const Eigen::Vector3d nt = shape_.shape().face_normal(idx);
      for (int i = 0; i < 3; ++i) {
        const Eigen::Vector3d vi = triangle.col(i);
        for (int j = i; j < 3; ++j) {
          const Eigen::Vector3d vj = triangle.col(j);
          n_energy += t / 6.0 * (n.dot(vi) + d) * (n.dot(vj) + d);
        }
      }
      n_energy += omega * t * (n - nt).squaredNorm();
    }
    if (n_energy < energy) {
      energy = n_energy;
      plane = Eigen::Vector4d(d, n.x(), n.y(), n.z());
    }
  }
}

void QuadraticSurface::LinearLeastSquarePlaneFit(const std::vector<int>& region,
  const double omega, Eigen::Vector4d& plane, double& energy) const {
  std::unordered_set<int> vid;
  for (const int idx : region) {
    for (int j = 0; j < 3; ++j) {
      vid.insert(shape_.shape().face(idx)(j));
    }
  }
  // Now collect all vertices.
  Eigen::MatrixX3d A = Eigen::MatrixX3d::Zero(vid.size(), 3);
  int count = 0;
  for (const int v : vid) {
    A.row(count) = shape_.shape().vertex(v);
    ++count;
  }
  // min |A * n + d| s.t. |n| = 1.
  // Easy to see d = -mean(A * n).
  // min |A * n - mean(A) * n| s.t. |n| = 1.
  const Eigen::RowVector3d A_mean = A.colwise().mean();
  A.rowwise() -= A_mean;
  // Now it becomes |A * n| s.t. |n| = 1.
  // So n corresponds to the minimal eigenvalues of A' * A.
  const Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> solve(A.transpose() * A);
  if (!solve.eigenvalues().allFinite() || !solve.eigenvectors().allFinite()) {
    common::PrintError("vsa::QuadraticSurface::LinearLeastSquarePlaneFit: failed"
      " to solve eigenvalues.");
  }
  int idx = -1;
  solve.eigenvalues().minCoeff(&idx);
  const Eigen::Vector3d n = solve.eigenvectors().col(idx);
  const double d = -A_mean.dot(n);
  plane(0) = d; plane.tail(3) = n;
  // Now compute the L2 + L21 energy. We have two options: plane and -plane. We
  // test both and pick the one with the smaller error. Note that we only need
  // to compute the L21 energy because L2 energy is the same for both.
  energy = 0.0;
  for (const int idx : region) {
    const double t = shape_.shape().area(idx);
    const Eigen::Matrix3d triangle = shape_.shape().Triangle(idx);
    for (int i = 0; i < 3; ++i) {
      const Eigen::Vector3d vi = triangle.col(i);
      for (int j = i; j < 3; ++j) {
        const Eigen::Vector3d vj = triangle.col(j);
        energy += t / 6.0 * (n.dot(vi) + d) * (n.dot(vj) + d);
      }
    }
  }
  double flip_energy = energy;
  for (const int idx : region) {
    const double t = shape_.shape().area(idx);
    const Eigen::Vector3d nt = shape_.shape().face_normal(idx);
    energy += omega * t * (n - nt).squaredNorm();
    flip_energy += omega * t * (n + nt).squaredNorm();
  }
  // Swap sign if flip_energy is smaller.
  if (flip_energy < energy) {
    energy = flip_energy;
    plane = -plane;
  }
}

}
