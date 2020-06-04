#include "primitive/cylindrical_surface.h"
#include <iostream>
#include <cmath>
#include "common/file_helper.h"
#include "common/math_helper.h"

namespace primitive {

void CylindricalSurface::Register() {
  std::shared_ptr<CylindricalSurface> surface =
    std::make_shared<CylindricalSurface>();
  SurfacePrimitive::primitive_instances.push_back(surface);
}

CylindricalSurface::CylindricalSurface()
  : SurfacePrimitive("cylinder", Eigen::VectorXd::Zero(6)) {
  parameters_(5) = 1.0;
  Normalize();
}

CylindricalSurface::CylindricalSurface(const Eigen::Vector3d& center,
  const Eigen::Vector3d& dir, const double radius)
  : SurfacePrimitive("cylinder", Eigen::VectorXd::Zero(6)) {
  const double dir_norm = dir.norm();
  if (dir_norm < common::Epsilon()) return;
  parameters_.head(3) = center;
  parameters_.segment(3, 2) = common::DirToThetaPhi(dir / dir_norm);
  parameters_(5) = radius;
  Normalize();
}

std::shared_ptr<SurfacePrimitive> CylindricalSurface::Duplicate() const {
  std::shared_ptr<CylindricalSurface> copy =
    std::make_shared<CylindricalSurface>();
  *copy = *this;
  return copy;
}

const double CylindricalSurface::Evaluate(const Eigen::Vector3d& point) const {
  const Eigen::Vector3d center = Center();
  const Eigen::Vector3d dir = Direction();
  const double radius = Radius();
  // <c + t * d - point, d> = 0.
  // <c - point, d> + t = 0.
  // t = <point - c, d>.
  // r - |c + <point - c, d> * d - point|.
  return radius - (center - point + (point - center).dot(dir) * dir).norm();
}

const Eigen::VectorXd CylindricalSurface::Gradient(
  const Eigen::Vector3d& point) const {
  Eigen::VectorXd gradient(6);
  const Eigen::Vector3d center = Center();
  const Eigen::Vector3d dir = Direction();
  // Radius.
  gradient(5) = 1.0;
  // Center.
  const Eigen::Vector3d d_norm = (center - point
    + (point - center).dot(dir) * dir).normalized();
  const Eigen::Matrix3d I = Eigen::Matrix3d::Identity();
  gradient.head(3) = -d_norm.transpose() * (I - dir * dir.transpose());
  // Angles.
  gradient.segment(3, 2) = -d_norm.transpose()
    * (dir * (point - center).transpose() + dir.dot(point - center) * I)
    * common::ThetaPhiToDirJacobian(parameters_.segment(3, 2));
  return gradient;
}

const Eigen::VectorXd CylindricalSurface::InitialGuess(
  const Eigen::Matrix3Xd& points, const Eigen::Matrix3Xd& normals) const {
  Eigen::VectorXd guess(6);
  // Direction:
  // min |normals.transpose() * dir| s.t. |dir| = 1.
  const Eigen::Matrix3d AA = normals * normals.transpose();
  Eigen::SelfAdjointEigenSolver<const Eigen::Matrix3d> eig_solver(AA);
  // Eigenvalues here are sorted in increasing order.
  const Eigen::Matrix3d V = eig_solver.eigenvectors();
  // x = Vy = V.col(0).
  Eigen::Vector3d dir = V.col(0);
  if (dir.sum() < 0.0) dir = -dir;
  guess.segment(3, 2) = common::DirToThetaPhi(dir);
  // Point.
  // (c + t1 * dir - p - t2 * n, dir) = 0.
  // (c + t1 * dir - p - t2 * n, n) = 0.
  // <c - p, dir> + t1 - t2 * <n, dir> = 0.
  // <c - p, n> + t1 * <dir, n> - t2 = 0.
  // It's reasonable to assume <n, dir> = 0 now.
  // t1 = <c - p, -dir>.
  // t2 = <c - p, n>.
  // min_c |c + <c - p, -dir>dir - p - <c - p, n>n|
  const int number = static_cast<int>(points.cols());
  assert(points.cols() == normals.cols());
  Eigen::MatrixX3d A(3 * number, 3);
  Eigen::VectorXd b(3 * number);
  for (int i = 0; i < number; ++i) {
    const Eigen::Vector3d p = points.col(i);
    const Eigen::Vector3d n = normals.col(i).normalized();
    b.segment(3 * i, 3) = -(p.dot(dir) * dir - p + p.dot(n) * n);
    A.middleRows(3 * i, 3) = Eigen::Matrix3d::Identity()
      - dir * dir.transpose() - n * n.transpose();
  }
  const Eigen::Vector3d center = (A.transpose() * A
    ).ldlt().solve(A.transpose() * b);
  guess.head(3) = center - center.dot(dir) * dir;
  // Radius.
  Eigen::VectorXd t2(number);
  for (int i = 0; i < number; ++i) {
    t2(i) = (center - points.col(i)).dot(normals.col(i).normalized());
  }
  guess(5) = t2.cwiseAbs().mean();
  return guess;
}

const Eigen::Vector3d CylindricalSurface::SurfaceNormal(
  const Eigen::Vector3d& point_on_surface) const {
  const Eigen::Vector3d center = parameters_.head(3);
  const Eigen::Vector3d dir = common::ThetaPhiToDir(parameters_.segment(3, 2));
  // <center + t * dir - point, dir> = 0.
  // <center - point, dir> + t = 0.
  const double t = (point_on_surface - center).dot(dir);
  return (point_on_surface - center - t * dir).normalized();
}


void CylindricalSurface::Sample(const double min_dist, const double max_dist,
  const Eigen::Vector3d& box_min, const Eigen::Vector3d& box_max,
  const double density, std::vector<Eigen::Vector3d>& samples) const {
  const Eigen::Vector3d center = Center();
  const Eigen::Vector3d dir = Direction();
  const double radius = Radius();
  const Eigen::Vector3d box_center = (box_min + box_max) * 0.5;
  // <center + t * dir - box_center, dir> = 0.
  // <center - box_center, dir> + t = 0.
  const double t = (box_center - center).dot(dir);
  const double t_range_sq = (box_center - box_min).squaredNorm()
    - (center + t * dir - box_center).squaredNorm();
  samples.clear();
  if (t_range_sq <= 0.0) {
    // Empty sample set.
    return;
  }
  const double t_range = std::sqrt(t_range_sq);
  const double max_diag = (box_max - box_min).norm();
  const double tmin = t - t_range - max_diag, tmax = t + t_range + max_diag;
  // Now [tmin, tmax] must be sufficient.
  double R1 = radius - max_dist;
  if (R1 < 0) R1 = 0;
  double R2 = radius - min_dist;
  if (R2 < 0) R2 = 0;
  double R3 = radius + min_dist;
  double R4 = radius + max_dist;
  const double r1 = R1 / R4, r2 = R2 / R4, r3 = R3 / R4, r4 = 1.0;
  const double u1 = r1 * r1, u2 = r2 * r2, u3 = r3 * r3, u4 = r4 * r4;
  const double du21 = u2 - u1, du43 = u4 - u3, u_all = du21 + du43;
  const double du21_ratio = du21 / u_all;
  const double volume = common::Pi() * (R4 * R4 - R3 * R3 + R2 * R2 - R1 * R1)
    * (tmax - tmin);
  const int sample_num = static_cast<int>(volume * density);
  samples.reserve(sample_num);

  // Sample points.
  const Eigen::Matrix3Xd random_seed = Eigen::Matrix3Xd::Random(3, sample_num);
  // Compute the two tangential directions.
  int min_idx = 0;
  dir.cwiseAbs().minCoeff(&min_idx);
  const Eigen::Vector3d x_vec = dir.cross(
    Eigen::Vector3d::Unit(min_idx)).normalized();
  const Eigen::Vector3d y_vec = dir.cross(x_vec).normalized();
  for (int i = 0; i < sample_num; ++i) {
    const double h = (random_seed(0, i) + 1.0) / 2.0f * (tmax - tmin) + tmin;
    const double theta = random_seed(1, i) * common::Pi();
    double u = (random_seed(2, i) + 1.0) / 2.0;
    if (u < du21_ratio) u = u_all * u + u1;
    else u = u_all * u - du21 + u3;
    const double r = std::sqrt(u) * (radius + max_dist);
    const double x = r * std::cos(theta), y = r * std::sin(theta);
    const Eigen::Vector3d sample = x * x_vec + y * y_vec + h * dir + center;
    // See if we need to reject this sample.
    if ((sample - box_min).minCoeff() > 0.0f &&
      (box_max - sample).minCoeff() > 0.0) {
      samples.push_back(sample);
    }
  }
}

const double CylindricalSurface::DistToSurface(const Eigen::Vector3d& point)
  const {
  // For cylinders it is the same as Evaluate.
  return Evaluate(point);
}

void CylindricalSurface::ReadFromString(const std::string& str) {
  std::istringstream ss(str);
  std::string type;
  ss >> type;
  if (type != type_name()) {
    std::cerr << common::RedHead()
      << "primitive::CylindricalSurface::ReadFromString: wrong type name: "
      << str << common::RedTail() << std::endl;
    exit(-1);
  }
  // Proceed.
  for (int i = 0; i < 3; ++i) ss >> parameters_(i);
  Eigen::Vector3d dir;
  for (int i = 0; i < 3; ++i) ss >> dir(i);
  dir.normalize();
  parameters_.segment(3, 2) = common::DirToThetaPhi(dir);
  ss >> parameters_(5);
  Normalize();
}

const std::string CylindricalSurface::WriteToString() const {
  std::stringstream ss;
  ss << SurfacePrimitive::type_name();
  const Eigen::Vector3d center = Center();
  for (int i = 0; i < 3; ++i) ss << " " << center(i);
  const Eigen::Vector3d dir = common::QuantizeEigenMatrix(Direction());
  for (int i = 0; i < 3; ++i) ss << " " << dir(i);
  ss << " " << Radius();
  return ss.str();
}

const bool CylindricalSurface::IntersectRoi(const Eigen::Vector3d& pmin,
  const Eigen::Vector3d& pmax) const {
  // Keep in mind that false positives are acceptable. So here we check the
  // bounding sphere of (pmin, pmax) intersects the cylinder.
  const Eigen::Vector3d c = (pmin + pmax) * 0.5;
  const double r = (pmax - c).norm();
  // <center + dir * t - c, dir> = 0.
  // <center - c, dir> + t = 0.
  // t = <c - center, dir>.
  const Eigen::Vector3d center = Center();
  const Eigen::Vector3d dir = Direction();
  const double radius = Radius();
  const double dist = ((c - center).dot(dir) * dir + center - c).norm();
  return r > dist - radius;
}

const Eigen::Vector3d CylindricalSurface::Center() const {
  return parameters_.head(3);
}

const Eigen::Vector3d CylindricalSurface::Direction() const {
  return common::ThetaPhiToDir(parameters_.segment(3, 2));
}

const double CylindricalSurface::Radius() const {
  return parameters_(5);
}

void CylindricalSurface::Normalize() {
  // Angles.
  Eigen::Vector3d dir = common::ThetaPhiToDir(parameters_.segment(3, 2));
  if (dir.sum() < 0.0) dir = -dir;
  parameters_.segment(3, 2) = common::DirToThetaPhi(dir);
  // <p + t * dir, dir> = 0.
  // <p, dir> + t = 0.
  // t = -<p, dir>.
  // p = p - <p, dir> * dir.
  Eigen::Vector3d point = parameters_.head(3);
  point -= point.dot(dir) * dir;
  parameters_.head(3) = point;
  parameters_ = common::QuantizeEigenMatrix(parameters_);
}

void TestCylindricalSurfaceFit() {
  Eigen::Vector3d center = Eigen::Vector3d::Random();
  Eigen::Vector3d dir = Eigen::Vector3d::Random().normalized();
  const double radius = Eigen::VectorXd::Random(1).cwiseAbs()(0);
  CylindricalSurface cylinder(center, dir, radius);
  std::cout << "Ground truth: " << cylinder.parameters().transpose()
    << std::endl;
  // Generate point.
  const Eigen::Vector3d x = dir.cross(Eigen::Vector3d::UnitX()).normalized();
  const Eigen::Vector3d y = x.cross(dir).normalized();
  // h = [0, 0.1r].
  // theta = [0, 1].
  const int number = 50;
  Eigen::VectorXd height_rand = Eigen::VectorXd::Random(number);
  Eigen::VectorXd angle_rand = Eigen::VectorXd::Random(number);
  Eigen::Matrix3Xd points(3, number), normals(3, number);
  for (int i = 0; i < number; ++i) {
    const double h = (height_rand(i) + 1.0) / 2.0 * 0.1 * radius;
    const double theta = (angle_rand(i) + 1.0) / 2.0;
    normals.col(i) = x * std::cos(theta) + y * std::sin(theta);
    points.col(i) = center + dir * h + radius * normals.col(i);
  }
  const double residual = cylinder.Fit(points, normals);
  std::cout << "Residual: " << residual << std::endl;
  std::cout << "Result: " << cylinder.parameters().transpose() << std::endl;
}

}
