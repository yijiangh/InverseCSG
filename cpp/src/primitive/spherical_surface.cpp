#include "primitive/spherical_surface.h"
#include <iostream>
#include <sstream>
#include <cmath>
#include "common/file_helper.h"
#include "common/math_helper.h"

namespace primitive {

void SphericalSurface::Register() {
  std::shared_ptr<SphericalSurface> surface
    = std::make_shared<SphericalSurface>();
  SurfacePrimitive::primitive_instances.push_back(surface);
}

SphericalSurface::SphericalSurface()
  : SurfacePrimitive("sphere", Eigen::Vector4d(0.0, 0.0, 0.0, 1.0)) {}

SphericalSurface::SphericalSurface(const Eigen::Vector3d& center,
  const double radius)
  : SurfacePrimitive("sphere", Eigen::Vector4d(center.x(), center.y(),
    center.z(), radius)) {
  Normalize();
}

std::shared_ptr<SurfacePrimitive> SphericalSurface::Duplicate() const {
  std::shared_ptr<SphericalSurface> copy =
    std::make_shared<SphericalSurface>();
  *copy = *this;
  return copy;
}

const double SphericalSurface::Evaluate(const Eigen::Vector3d& point) const {
  const Eigen::Vector3d center = parameters_.head(3);
  const double radius = parameters_.w();
  // r - |center - point|.
  return radius - (center - point).norm();
}

const Eigen::VectorXd SphericalSurface::Gradient(const Eigen::Vector3d& point) const {
  const Eigen::Vector3d center = parameters_.head(3);
  Eigen::Vector4d gradient;
  gradient.head(3) = -(center - point).normalized();
  gradient.w() = 1.0;
  return gradient;
}

const Eigen::VectorXd SphericalSurface::InitialGuess(
  const Eigen::Matrix3Xd& points, const Eigen::Matrix3Xd& normals) const {
  // Given a line p + t * n and a point q:
  // <p + t * n - q, n> = 0 => t = <q - p, n>.
  // So dist(p + t * n, q) = |p + <q - p, n>n - q|.
  // Let's minimize \sum_q |p_i + <q - p_i, n_i>n_i - q|.
  // = \sum_q |(n_i * n_iT - I)q - (<p_i, n_i>n_i - p_i)|.
  const int number = static_cast<int>(points.cols());
  assert(points.cols() == normals.cols());
  Eigen::MatrixXd A(3 * number, 3);
  Eigen::VectorXd b(3 * number);
  for (int i = 0; i < number; ++i) {
    const Eigen::Vector3d ni = normals.col(i).normalized();
    const Eigen::Matrix3d Ai = ni * ni.transpose() - Eigen::Matrix3d::Identity();
    A.middleRows(3 * i, 3) = Ai;
    b.segment(3 * i, 3) = Ai * points.col(i);
  }
  const Eigen::Vector3d center =
    A.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(b);
  const double radius = (points.colwise() - center).colwise().norm().mean();
  return Eigen::Vector4d(center.x(), center.y(), center.z(), radius);
}

const Eigen::Vector3d SphericalSurface::SurfaceNormal(
  const Eigen::Vector3d& point_on_surface) const {
  return (point_on_surface - parameters_.head(3)).normalized();
}

void SphericalSurface::Sample(const double min_dist, const double max_dist,
  const Eigen::Vector3d& box_min, const Eigen::Vector3d& box_max,
  const double density, std::vector<Eigen::Vector3d>& samples) const {
  // Compute the number of samples.
  const Eigen::Vector3d center = Center();
  const double radius = Radius();
  const double volume = 4.0 / 3.0 * common::Pi() * (
    std::pow(radius + max_dist, 3.0) - std::pow(radius + min_dist, 3.0) +
    std::pow(radius - min_dist, 3.0) - std::pow(radius - max_dist, 3.0));
  const int sample_num = static_cast<int>(volume * density);

  // Generate samples.
  samples.clear();
  samples.reserve(sample_num);
  const Eigen::Matrix3Xd random_seed = Eigen::Matrix3Xd::Random(3, sample_num);
  // Constants.
  const double r3 = (radius + min_dist) / (radius + max_dist);
  double r2 = (radius - min_dist) / (radius + max_dist);
  if (r2 < 0) r2 = 0;
  double r1 = (radius - max_dist) / (radius + max_dist);
  if (r1 < 0) r1 = 0;
  const double u1 = r1 * r1 * r1, u2 = r2 * r2 * r2,
    u3 = r3 * r3 * r3, u4 = 1.0;
  const double du21 = u2 - u1, du43 = u4 - u3, u_all = du21 + du43;
  const double du21_ratio = du21 / u_all;

  // phi = random(-pi, pi).
  // cos_theta = random(-1, 1).
  // u = random(0, 1).
  // r = R * pow(u, 1.0f / 3.0).
  // x = r * sin(theta) * cos(phi).
  // y = r * sin(theta) * sin(phi).
  // z = r * cos(theta).
  // This uniformly samples a point in a solid sphere.
  for (int i = 0; i < sample_num; ++i) {
    const double phi = random_seed(0, i) * common::Pi();
    const double cos_theta = random_seed(1, i);
    double u = (random_seed(2, i) + 1.0) * 0.5;
    // Uniformly sample between (u1, u2) \/ (u3, u4).
    if (u < du21_ratio) u = u_all * u + u1;
    else u = u_all * u - du21 + u3;
    const double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);
    const double r = (radius + max_dist) * std::pow(u, 1.0 / 3.0);
    const Eigen::Vector3d sample(r * sin_theta * std::cos(phi) + center.x(),
      r * sin_theta * std::sin(phi) + center.y(), r * cos_theta + center.z());
    // See if we need to reject this sample.
    if ((sample - box_min).minCoeff() > 0.0 &&
      (box_max - sample).minCoeff() > 0.0) {
      samples.push_back(sample);
    }
  }
}

const double SphericalSurface::DistToSurface(const Eigen::Vector3d& point)
  const {
  // For spheres it is the same as Evaluate.
  return Evaluate(point);
}

void SphericalSurface::ReadFromString(const std::string& str) {
  std::istringstream ss(str);
  std::string type;
  ss >> type;
  if (type != type_name()) {
    std::cerr << common::RedHead()
      << "primitive::SphericalSurface::ReadFromString: wrong type name: "
      << str << common::RedTail() << std::endl;
    exit(-1);
  }
  // Proceed.
  for (int i = 0; i < 4; ++i) ss >> parameters_(i);
  Normalize();
}

const std::string SphericalSurface::WriteToString() const {
  std::stringstream ss;
  ss << SurfacePrimitive::type_name();
  for (int i = 0; i < 4; ++i) ss << " " << parameters_(i);
  return ss.str();
}

const bool SphericalSurface::IntersectRoi(const Eigen::Vector3d& pmin,
  const Eigen::Vector3d& pmax) const {
  // This is not completely correct but it guarantees to return true if the
  // sphere indeed intersects the cuboid.
  const Eigen::Vector3d center = Center();
  const double radius = Radius();
  for (int i = 0; i < 3; ++i) {
    const double s_low = center(i) - radius;
    const double s_high = center(i) + radius;
    const double t_low = pmin(i);
    const double t_high = pmax(i);
    if (t_high <= s_low || s_high <= t_low) return false;
  }
  return true;
}

const Eigen::Vector3d SphericalSurface::Center() const {
  return parameters_.head(3);
}

const double SphericalSurface::Radius() const {
  return parameters_(3);
}

void SphericalSurface::Normalize() {
  parameters_ = common::QuantizeEigenMatrix(parameters_);
}

void TestSphericalSurfaceFit() {
  const Eigen::Vector4d random_param = Eigen::Vector4d::Random();
  const Eigen::Vector3d center = random_param.head(3);
  const double r = random_param.w() > 0 ? random_param.w() : -random_param.w();
  SphericalSurface sphere(center, r);
  std::cout << "Ground truth: " << sphere.parameters().transpose()
    << std::endl;
  const int number = 50;
  const Eigen::Matrix2Xd random_angle = Eigen::Matrix2Xd::Random(2, number);
  Eigen::Matrix3Xd random_points(3, number);
  Eigen::Matrix3Xd random_normals(3, number);
  for (int i = 0; i < number; ++i) {
    const double theta = random_angle(0, i) * common::Pi() * 0.5;
    const double phi = random_angle(1, i) * common::Pi();
    random_normals.col(i) = Eigen::Vector3d(std::cos(theta) * std::cos(phi),
      std::cos(theta) * std::sin(phi), std::sin(theta));
    random_points.col(i) = center + random_normals.col(i) * r;
  }
  const double residual = sphere.Fit(random_points, random_normals);
  std::cout << "Residual: " << residual << std::endl;
  std::cout << "Result: " << sphere.parameters().transpose() << std::endl;
}

}
