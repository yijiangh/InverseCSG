#include "primitive/plane_surface.h"
#include <iostream>
#include <sstream>
#include <cmath>
#include "common/file_helper.h"
#include "common/math_helper.h"

namespace primitive {

void PlaneSurface::Register() {
  std::shared_ptr<PlaneSurface> surface = std::make_shared<PlaneSurface>();
  SurfacePrimitive::primitive_instances.push_back(surface);
}

PlaneSurface::PlaneSurface()
  : SurfacePrimitive("plane", Eigen::Vector4d(1.0, 0.0, 0.0, 0.0)) {
  Normalize();
}

PlaneSurface::PlaneSurface(const Eigen::Vector3d& normal, const double offset)
  : SurfacePrimitive("plane", Eigen::Vector4d(normal.x(), normal.y(),
    normal.z(), offset)) {
  Normalize();
}

std::shared_ptr<SurfacePrimitive> PlaneSurface::Duplicate() const {
  std::shared_ptr<SurfacePrimitive> copy = std::make_shared<PlaneSurface>();
  *copy = *this;
  return copy;
}

const double PlaneSurface::Evaluate(const Eigen::Vector3d& point) const {
  return parameters_.head(3).dot(point) + parameters_.w();
}

const Eigen::VectorXd PlaneSurface::Gradient(const Eigen::Vector3d& point)
  const {
  return Eigen::Vector4d(point.x(), point.y(), point.z(), 1.0);
}

const Eigen::VectorXd PlaneSurface::InitialGuess(const Eigen::Matrix3Xd& points,
  const Eigen::Matrix3Xd& normals) const {
  // Does not matter because it is a linear least square problem.
  return Eigen::Vector4d(1.0, 0.0, 0.0, 0.0);
}

const double PlaneSurface::Fit(const Eigen::Matrix3Xd& points,
  const Eigen::Matrix3Xd& normals) {
  const int number = static_cast<int>(points.cols());
  assert(points.cols() == normals.cols());
  Eigen::MatrixX4d A(number, 4);
  for (int i = 0; i < number; ++i) {
    A.row(i) = Eigen::Vector4d(points(0, i),
      points(1, i), points(2, i), 1.0);
  }
  // min \|Ax\|^2.
  // s.t. \|x\| = 1.
  // min x'(A'A)x, s.t. \|x\| = 1.
  // A'A V = V S => A'A = VSV'.
  // Define y = V'x => min y'Sy s.t. \|y\| = 1.
  const Eigen::Matrix4d AA = A.transpose() * A;
  Eigen::SelfAdjointEigenSolver<const Eigen::Matrix4d> eig_solver(AA);
  // Eigenvalues here are sorted in increasing order.
  const Eigen::Matrix4d V = eig_solver.eigenvectors();
  // x = Vy = V.col(0).
  parameters_ = V.col(0);
  Normalize();
  if (!parameters_.allFinite()) return common::Infinity();
  return (A * parameters_).cwiseAbs().maxCoeff();
}

const Eigen::Vector3d PlaneSurface::SurfaceNormal(
  const Eigen::Vector3d& point_on_surface) const {
  return parameters_.head(3);
}

void PlaneSurface::Sample(const double min_dist, const double max_dist,
  const Eigen::Vector3d& box_min, const Eigen::Vector3d& box_max,
  const double density, std::vector<Eigen::Vector3d>& samples) const {
  const Eigen::Vector3d center = (box_min + box_max) * 0.5;
  const Eigen::Vector3d normal = Normal();
  const double offset = Offset();
  // normal.dot(point) + offset = 0.
  // normal.dot(center + t * normal) + offset = 0.
  // normal.dot(center) + t + offset = 0.
  const double dist_to_plane = -offset - normal.dot(center);
  const Eigen::Vector3d projected_center = center + dist_to_plane * normal;
  const double radius_sq = (center - box_min).squaredNorm()
    - dist_to_plane * dist_to_plane;
  samples.clear();
  if (radius_sq <= 0.0) {
    // Empty sample set.
    return;
  }
  const double radius = std::sqrt(radius_sq);
  // Compute the two tangential directions.
  int min_idx = 0;
  normal.cwiseAbs().minCoeff(&min_idx);
  const Eigen::Vector3d x_vec = normal.cross(
    Eigen::Vector3d::Unit(min_idx)).normalized();
  const Eigen::Vector3d y_vec = normal.cross(x_vec).normalized();
  // Compute the number of samples.
  const double volume = common::Pi() * radius * radius
    * 2.0f * (max_dist - min_dist);
  const int sample_num = static_cast<int>(volume * density);
  samples.reserve(sample_num);

  // Sample points.
  const Eigen::Matrix3Xd random_seed = Eigen::Matrix3Xd::Random(3, sample_num);
  for (int i = 0; i < sample_num; ++i) {
    // u\in(0, 1). \theta\in(-pi, pi).
    // x = sqrt(u)cos(theta). y = sqrt(u)sin(theta).
    const double u = (random_seed(0, i) + 1.0) / 2.0;
    const double theta = random_seed(1, i) * common::Pi();
    const double r = radius * std::sqrt(u);
    const double x = r * std::cos(theta), y = r * std::sin(theta);
    // h \in [-d1, -d2] \/ [d2, d1]
    double h = random_seed(2, i) * (max_dist - min_dist);
    h = (h > 0) ? (h + min_dist) : (h - min_dist);
    const Eigen::Vector3d sample = projected_center + x_vec * x + y_vec * y
      + h * normal;
    // See if we need to reject this sample.
    if ((sample - box_min).minCoeff() > 0.0 &&
      (box_max - sample).minCoeff() > 0.0) {
      samples.push_back(sample);
    }
  }
}

const double PlaneSurface::DistToSurface(const Eigen::Vector3d& point) const {
  return parameters_.head(3).dot(point) + parameters_.w();
}

void PlaneSurface::ReadFromString(const std::string& str) {
  std::istringstream ss(str);
  std::string type;
  ss >> type;
  if (type != type_name()) {
    std::cerr << common::RedHead()
      << "primitive::PlaneSurface::ReadFromString: wrong type name: "
      << str << common::RedTail() << std::endl;
    exit(-1);
  }
  // Proceed.
  for (int i = 0; i < 4; ++i) ss >> parameters_(i);
  Normalize();
}

const std::string PlaneSurface::WriteToString() const {
  std::stringstream ss;
  ss << SurfacePrimitive::type_name();
  for (int i = 0; i < 4; ++i) ss << " " << parameters_(i);
  return ss.str();
}

const bool PlaneSurface::IntersectRoi(const Eigen::Vector3d& pmin,
  const Eigen::Vector3d& pmax) const {
  // A plane does not intersect a cuboid iff its eight corners are on the same
  // side of the plane.
  bool pos_sign = false, neg_sign = false;
  for (int i = 0; i < 8; ++i) {
    const int x = i % 2, y = (i / 2) % 2, z = i / 4;
    Eigen::Vector3d corner = pmin;
    corner(0) = x ? pmax(0) : pmin(0);
    corner(1) = y ? pmax(1) : pmin(1);
    corner(2) = z ? pmax(2) : pmin(2);
    const double dist = DistToSurface(corner);
    if (std::fabs(dist) <= common::Epsilon()) continue;
    if (dist > 0) pos_sign = true;
    else neg_sign = true;
  }
  return pos_sign == true && neg_sign == true;
}

const Eigen::Vector3d PlaneSurface::Normal() const {
  return parameters_.head(3);
}

const double PlaneSurface::Offset() const {
  return parameters_(3);
}

void PlaneSurface::Normalize() {
  assert(parameters_.size() == 4u);
  parameters_ /= parameters_.head(3).norm();
  // Flip the sign to make sure each plane has a unique representation.
  if (parameters_.head(3).sum() < 0.0) parameters_ = -parameters_;
  parameters_ = common::QuantizeEigenMatrix(parameters_);
}

void TestPlaneSurfaceFit() {
  const Eigen::Vector4d random_plane = Eigen::Vector4d::Random();
  PlaneSurface plane(random_plane.head(3), random_plane.w());
  const Eigen::Vector4d true_para = plane.parameters();
  std::cout << "Ground truth: " << true_para.transpose() << std::endl;
  const int point_number = 50;
  Eigen::Matrix3Xd random_points = Eigen::Matrix3Xd::Random(3, point_number);
  // <p + t * n, n> + w = 0.
  // <p, n> + t + w = 0.
  // t = -<p, n> - w.
  // p = p -(<p, n> + w)n.
  Eigen::RowVectorXd t = true_para.head(3).transpose() * random_points;
  t = t.array() + true_para.w();
  random_points += true_para.head(3) * (-t);
  const double residual = plane.Fit(random_points,
    true_para.head(3) * Eigen::RowVectorXd::Ones(point_number));
  std::cout << "Residual: " << residual << std::endl;
  std::cout << "Result: " << plane.parameters().transpose() << std::endl;
}

}
