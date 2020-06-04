#include "primitive/toric_surface.h"
#include <iostream>
#include <sstream>
#include <cmath>
#include "common/file_helper.h"
#include "common/math_helper.h"

namespace primitive {

void ToricSurface::Register() {
  std::shared_ptr<ToricSurface> surface
    = std::make_shared<ToricSurface>();
  SurfacePrimitive::primitive_instances.push_back(surface);
}

ToricSurface::ToricSurface()
  : SurfacePrimitive("torus", Eigen::VectorXd::Zero(8)) {
  // Make sure we build a valid torus.
  parameters_(5) = 1.0;
  parameters_(6) = 1.0;
  parameters_(7) = 0.5;
  Normalize();
}

ToricSurface::ToricSurface(const Eigen::Vector3d& center,
  const Eigen::Vector3d& axis, const double major_radii,
  const double minor_radii)
  : SurfacePrimitive("torus", Eigen::VectorXd::Zero(8)) {
  parameters_.head(3) = center;
  parameters_.segment(3, 3) = axis;
  parameters_(6) = major_radii;
  parameters_(7) = minor_radii;
  Normalize();
}

std::shared_ptr<SurfacePrimitive> ToricSurface::Duplicate() const {
  std::shared_ptr<ToricSurface> copy =
    std::make_shared<ToricSurface>();
  *copy = *this;
  return copy;
}

const double ToricSurface::Evaluate(const Eigen::Vector3d& point) const {
  // Distance to the torus. Positive means it is inside.
  const Eigen::Vector3d center = Center();
  const Eigen::Vector3d axis = Axis();
  const double major_radii = MajorRadii();
  const double minor_radii = MinorRadii();
  // Transform the space so that the torus is centered and axis = z.
  const Eigen::Vector3d z = Eigen::Vector3d::UnitZ();
  const auto quat =
    Eigen::Quaterniond::FromTwoVectors(axis, z);
  const Eigen::Vector3d p = quat.matrix() * (point - center);
  Eigen::Vector3d y = z.cross(p);
  const double y_len = y.norm();
  if (y_len < common::Epsilon()) {
    y = Eigen::Vector3d::UnitY();
  } else {
    y /= y_len;
  }
  const Eigen::Vector3d x = y.cross(z).normalized();
  const double px = p.dot(x), pz = p.dot(z);
  // Compute the distance from (px, pz) to a circle centered at (major_radii, 0)
  // of radius = minor_radii.
  const Eigen::Vector2d dist(px - major_radii, pz);
  return minor_radii - dist.norm();
}

const Eigen::VectorXd ToricSurface::Gradient(const Eigen::Vector3d& point)
  const {
  // TODO: Gradient is not used for now. Reimplement it in the future.
  auto grad = parameters_;
  grad.setZero();
  return grad;
}

const Eigen::VectorXd ToricSurface::InitialGuess(
  const Eigen::Matrix3Xd& points, const Eigen::Matrix3Xd& normals) const {
  // TODO: InitialGuess is not used for now. Reimplement it in the future.
  auto initial_guess = parameters_;
  initial_guess.setZero();
  initial_guess(5) = initial_guess(6) = 1.0;
  initial_guess(7) = 0.5;
  return initial_guess;
}

const Eigen::Vector3d ToricSurface::SurfaceNormal(
  const Eigen::Vector3d& point_on_surface) const {
  const Eigen::Vector3d y = Axis();
  const Eigen::Vector3d o = Center();
  const Eigen::Vector3d z = y.cross(point_on_surface - o);
  const Eigen::Vector3d x = z.cross(y).normalized();
  const double major_radii = MajorRadii();
  return (point_on_surface - (o + major_radii * x)).normalized();
}

void ToricSurface::Sample(const double min_dist, const double max_dist,
  const Eigen::Vector3d& box_min, const Eigen::Vector3d& box_max,
  const double density, std::vector<Eigen::Vector3d>& samples) const {
  const Eigen::Vector3d center = Center();
  const Eigen::Vector3d axis = Axis();
  const double major_radii = MajorRadii();
  const double minor_radii = MinorRadii();
  // Compute the number of samples.
  const double R4 = minor_radii + max_dist, R3 = minor_radii + min_dist;
  double R2 = minor_radii - min_dist, R1 = minor_radii - max_dist;
  R2 = (R2 < 0) ? 0 : R2;
  R1 = (R1 < 0) ? 0 : R1;
  const double pi = common::Pi();
  const double vol = pi * (R2 * R2 - R1 * R1 + R4 * R4 - R3 * R3)
    * 2.0 * pi * major_radii;
  const int sample_num = static_cast<int>(vol * density);

  // Generate samples.
  samples.clear();
  samples.reserve(sample_num);
  const Eigen::Matrix3Xd random_seed = Eigen::Matrix3Xd::Random(3, sample_num);
  // Constants.
  const double r4 = 1.0;
  const double r3 = R3 / R4;
  const double r2 = R2 / R4;
  const double r1 = R1 / R4;
  const double u1 = r1 * r1, u2 = r2 * r2, u3 = r3 * r3, u4 = r4 * r4;
  const double du21 = u2 - u1, du43 = u4 - u3, u_all = du21 + du43;
  const double du21_ratio = du21 / u_all;
  for (int i = 0; i < sample_num; ++i) {
    const double theta = random_seed(0, i) * pi;
    const double phi = random_seed(1, i) * pi;
    double u = (random_seed(2, i) + 1.0) / 2.0;
    if (u < du21_ratio) u = u_all * u + u1;
    else u = u_all * u - du21 + u3;
    const double r = std::sqrt(u) * R4;
    Eigen::Vector3d p = Eigen::Vector3d(major_radii +
      r * std::cos(phi), 0, r * std::sin(phi));
    // Rotate p along z by theta.
    const Eigen::Vector3d z = Eigen::Vector3d::UnitZ();
    p = Eigen::AngleAxisd(theta, z).matrix() * p;
    p = Eigen::Quaterniond::FromTwoVectors(z, axis).matrix() * p;
    // Shift by center.
    p += center;
    // Accept this sample only if it is inside the box.
    if ((p - box_min).minCoeff() > 0.0 &&
      (box_max - p).minCoeff() > 0.0) {
      samples.push_back(p);
    }
  }
}

const double ToricSurface::DistToSurface(const Eigen::Vector3d& point)
  const {
  // For torus it is the same as evaluate.
  return Evaluate(point);
}

void ToricSurface::ReadFromString(const std::string& str) {
  std::istringstream ss(str);
  std::string type;
  ss >> type;
  if (type != type_name()) {
    common::PrintError("primitive::ToricSurface::ReadFromString: wrong type "
      "name: " + str);
  }
  // Proceed.
  for (int i = 0; i < 8; ++i) ss >> parameters_(i);
  Normalize();
}

const std::string ToricSurface::WriteToString() const {
  std::stringstream ss;
  ss << SurfacePrimitive::type_name();
  for (int i = 0; i < 8; ++i) ss << " " << parameters_(i);
  return ss.str();
}

const bool ToricSurface::IntersectRoi(const Eigen::Vector3d& pmin,
  const Eigen::Vector3d& pmax) const {
  // First, compute the bounding box of a torus.
  const Eigen::Vector3d center = Center();
  const Eigen::Vector3d axis = Axis();
  const double major_radii = MajorRadii();
  const double minor_radii = MinorRadii();
  const double xy_max = major_radii + minor_radii;
  const double z_max = minor_radii;
  Eigen::Matrix3Xd corners = Eigen::Matrix3Xd::Zero(3, 8);
  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 2; ++j)
      for (int k = 0; k < 2; ++k) {
        const int cid = 4 * i + 2 * j + k;
        corners(0, cid) = i ? xy_max : -xy_max;
        corners(1, cid) = j ? xy_max : -xy_max;
        corners(2, cid) = k ? z_max : -z_max;
      } 
  // Step zero: rotate by quad.
  const Eigen::Vector3d z = Eigen::Vector3d::UnitZ();
  const auto quat = Eigen::Quaterniond::FromTwoVectors(z, axis);
  corners = quat.matrix() * corners;
  // Step one: translate by center.
  corners.colwise() += center;
  // Step two: compute bmin and bmax.
  const Eigen::Vector3d bmin = corners.rowwise().minCoeff();
  const Eigen::Vector3d bmax = corners.rowwise().maxCoeff();

  // Now check if two boxes intersect.
  const bool intersect_x = !(pmin.x() > bmax.x() || pmax.x() < bmin.x());
  const bool intersect_y = !(pmin.y() > bmax.y() || pmax.y() < bmin.y());
  const bool intersect_z = !(pmin.z() > bmax.z() || pmax.z() < bmin.z());
  return intersect_x && intersect_y && intersect_z;
}

const Eigen::Vector3d ToricSurface::Center() const {
  return parameters_.head(3);
}

const Eigen::Vector3d ToricSurface::Axis() const {
  return parameters_.segment(3, 3);
}

const double ToricSurface::MajorRadii() const {
  return parameters_(6);
}

const double ToricSurface::MinorRadii() const {
  return parameters_(7);
}

void ToricSurface::Normalize() {
  Eigen::Vector3d axis = parameters_.segment(3, 3);
  const double axis_len = axis.norm();
  if (axis_len < common::Epsilon()) {
    common::PrintError("primitive::ToricSurface::Normalize: invalid axis.");
  }
  if (axis.sum() < 0.0) axis = -axis;
  parameters_.segment(3, 3) = axis / axis_len;
  const double major_radii = parameters_(6);
  if (major_radii < common::Epsilon()) {
    common::PrintError("primitve::ToricSurface::Normalize: "
      "invalid major radii.");
  }
  const double minor_radii = parameters_(7);
  if (minor_radii < common::Epsilon()) {
    common::PrintError("primitive::ToricSurface::Normalize: "
      "invalid minor radii.");
  }
  parameters_ = common::QuantizeEigenMatrix(parameters_);
}

}
