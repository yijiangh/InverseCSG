#include "primitive/conical_surface.h"
#include <iostream>
#include <sstream>
#include <cmath>
#include "common/file_helper.h"
#include "common/math_helper.h"

namespace primitive {

void ConicalSurface::Register() {
  std::shared_ptr<ConicalSurface> surface
    = std::make_shared<ConicalSurface>();
  SurfacePrimitive::primitive_instances.push_back(surface);
}

ConicalSurface::ConicalSurface()
  : SurfacePrimitive("cone", Eigen::VectorXd::Zero(7)) {
  // Make sure we build a valid cone.
  parameters_(5) = 1.0;
  parameters_(6) = common::Pi() / 4.0;
  Normalize();
}

ConicalSurface::ConicalSurface(const Eigen::Vector3d& apex,
  const Eigen::Vector3d& axis, const double angle)
  : SurfacePrimitive("cone", Eigen::VectorXd::Zero(7)) {
  parameters_.head(3) = apex;
  parameters_.segment(3, 3) = axis;
  parameters_(6) = angle;
  Normalize();
}

std::shared_ptr<SurfacePrimitive> ConicalSurface::Duplicate() const {
  std::shared_ptr<ConicalSurface> copy =
    std::make_shared<ConicalSurface>();
  *copy = *this;
  return copy;
}

const double ConicalSurface::Evaluate(const Eigen::Vector3d& point) const {
  // Distance to the cone. Positive means it is inside.
  const Eigen::Vector3d apex = Apex();
  const Eigen::Vector3d axis = Axis();
  const Eigen::Vector3d z = Eigen::Vector3d::UnitZ();
  const Eigen::Matrix3d R =
    Eigen::Quaterniond::FromTwoVectors(axis, z).matrix();
  const Eigen::Vector3d p = R * (point - apex);
  // Now apex is the origin, axis is z, point is p.
  Eigen::Vector3d y = z.cross(p);
  const double y_len = y.norm();
  if (y_len < common::Epsilon()) {
    y = Eigen::Vector3d::UnitY();
  } else {
    y /= y_len;
  }
  const Eigen::Vector3d x = y.cross(z);
  double px = x.dot(p), pz = z.dot(p);
  // This happens only because of numerical errors.
  if (px < 0) px = -px;
  const double k = 1.0 / std::tan(Angle());
  if (pz >= k * px) {
    // Inside the cone.
    const double dist = (pz - k * px) / std::sqrt(1 + k * k);
    return dist;
  } else {
    // Outside the cone.
    const double dist_to_line = (k * px - pz) / std::sqrt(1 + k * k);
    const double dist_to_apex = std::sqrt(px * px + pz * pz);
    // <t * (1, k) - (px, pz), (1, k)> = 0.
    // t - px + k * (tk - pz) = 0.
    // (1 + k^2)t = px + k * pz.
    // t = (px + k * pz) / (1 + k^2)
    const double t = (px + k * pz) / (1 + k * k);
    if (t < 0) return -dist_to_apex;
    else return -dist_to_line;
  }
}

const Eigen::VectorXd ConicalSurface::Gradient(const Eigen::Vector3d& point)
  const {
  // TODO: Gradient is not used for now. Reimplement it in the future.
  auto grad = parameters_;
  grad.setZero();
  return grad;
}

const Eigen::VectorXd ConicalSurface::InitialGuess(
  const Eigen::Matrix3Xd& points, const Eigen::Matrix3Xd& normals) const {
  // TODO: InitialGuess is not used for now. Reimplement it in the future.
  auto initial_guess = parameters_;
  initial_guess.setZero();
  initial_guess(5) = 1.0;
  initial_guess(6) = common::Pi() / 4.0;
  return initial_guess;
}

const Eigen::Vector3d ConicalSurface::SurfaceNormal(
  const Eigen::Vector3d& point_on_surface) const {
  const Eigen::Vector3d apex = Apex();
  const Eigen::Vector3d axis = Axis();
  const Eigen::Vector3d p = point_on_surface - apex;
  if (p.norm() < common::Epsilon())
    return -axis;
  const Eigen::Vector3d y = axis.cross(p).normalized();
  return y.cross(p).normalized();
}

static const bool IntersectBox(const Eigen::Vector3d& origin,
  const Eigen::Vector3d& dir, const Eigen::Vector3d& pmin,
  const Eigen::Vector3d& pmax, double& tmin, double& tmax) {
  tmin = 0.0;
  tmax = common::Infinity();
  for (int i = 0; i < 3; ++i) {
    if (dir[i] == 0) {
      if (origin[i] < pmin[i] || origin[i] > pmax[i]) {
        return false;
      }
    } else {
      double t0 = (pmin[i] - origin[i]) / dir[i];
      double t1 = (pmax[i] - origin[i]) / dir[i];
      if (t0 > t1) {
        const double tmp = t0; t0 = t1; t1 = tmp;
      }
      if (tmin < t0) tmin = t0;
      if (tmax > t1) tmax = t1;
      if (tmin >= tmax) return false;
    }
  }
  return true;
}

void ConicalSurface::Sample(const double min_dist, const double max_dist,
  const Eigen::Vector3d& box_min, const Eigen::Vector3d& box_max,
  const double density, std::vector<Eigen::Vector3d>& samples) const {
  // TODO: this function turns out to be a lot trickier than we have thought.
  // I believe there should be an analytical way of sampling points here, but
  // I could not find it. So I ended up coding this nasty version below.
  samples.clear();
  const auto apex = Apex();
  const auto axis = Axis();
  const double angle = Angle();

  // Generate a unit vector that is orthogonal to axis.
  int idx = -1;
  axis.cwiseAbs().minCoeff(&idx);
  if (idx < 0 || idx > 2) {
    std::ostringstream ss;
    ss << "primitive::ConicalSurface::Sample: invalid axis: "
      << axis.transpose();
    common::PrintError(ss.str());
  }
  const auto aux = axis.cross(Eigen::Vector3d::Unit(idx)).normalized();
  const auto s0 = Eigen::AngleAxisd(angle, aux).matrix() * axis;

  // To randomly sample a ray, we rotate s0 along axis by a random angle.
  const double pi = common::Pi();
  // TODO: compute the area of the conical surface that is enclosed in the
  // bounding box. I don't have a good way to do it now.
  const double area = 10.0;
  const int sample_num = density * (max_dist - min_dist) * 2.0 * area;
  // If we cannot finish within this number of trials, we give up.
  const int max_iter = 10000;
  int iter = 0;
  while (iter < max_iter && static_cast<int>(samples.size()) < sample_num) {
    ++iter;
    const auto seeds = Eigen::Vector3d::Random();
    const double ray_angle = seeds(0) * pi;
    const Eigen::Vector3d ray_dir = Eigen::AngleAxisd(ray_angle, axis).matrix()
      * s0;

    // Now compute the intersection.
    double tmin = 0.0, tmax = common::Infinity();
    if (!IntersectBox(apex, ray_dir, box_min, box_max, tmin, tmax)) continue;

    // Now we have a nonempty intersection.
    const double t0 = seeds(1) * (tmax - tmin) / 2.0 + (tmax + tmin) / 2.0;
    const Eigen::Vector3d p0 = apex + t0 * ray_dir;

    // Offset by a random distance.
    const double h0 = seeds(2) * (max_dist - min_dist) +
      (seeds(2) > 0 ? 1.0 : -1.0) * min_dist;
    const auto n = SurfaceNormal(p0);
    const auto sample_point = p0 + n * h0;

    // Check if this point is inside the bounding box.
    if ((sample_point - box_min).minCoeff() < 0.0 ||
      (box_max - sample_point).minCoeff() < 0.0) continue;

    // Finally, this is a valid sample point.
    samples.push_back(sample_point);
  }
}

const double ConicalSurface::DistToSurface(const Eigen::Vector3d& point)
  const {
  // For cone it is the same as evaluate.
  return Evaluate(point);
}

void ConicalSurface::ReadFromString(const std::string& str) {
  std::istringstream ss(str);
  std::string type;
  ss >> type;
  if (type != type_name()) {
    common::PrintError("primitive::ConicalSurface::ReadFromString: wrong type "
      "name: " + str);
  }
  // Proceed.
  for (int i = 0; i < 7; ++i) ss >> parameters_(i);
  Normalize();
}

const std::string ConicalSurface::WriteToString() const {
  std::stringstream ss;
  ss << SurfacePrimitive::type_name();
  for (int i = 0; i < 7; ++i) ss << " " << parameters_(i);
  return ss.str();
}

const bool ConicalSurface::IntersectRoi(const Eigen::Vector3d& pmin,
  const Eigen::Vector3d& pmax) const {
  // TODO: implement this function in the right way. Recall that it is OK to
  // have false positives so always returning true won't affect the correctness
  // of the other parts.
  return true;
}

const Eigen::Vector3d ConicalSurface::Apex() const {
  return parameters_.head(3);
}

const Eigen::Vector3d ConicalSurface::Axis() const {
  return parameters_.segment(3, 3);
}

const double ConicalSurface::Angle() const {
  return parameters_(6);
}

void ConicalSurface::Normalize() {
  Eigen::Vector3d axis = parameters_.segment(3, 3);
  const double axis_len = axis.norm();
  if (axis_len < common::Epsilon()) {
    common::PrintError("primitive::ConicalSurface::Normalize: invalid axis.");
  }
  parameters_.segment(3, 3) = axis / axis_len;
  const double angle = parameters_(6);
  if (angle < common::Epsilon() || angle >= common::Pi() / 2.0) {
    common::PrintError("primitve::ConicalSurface::Normalize: "
      "invalid angle.");
  }
  parameters_ = common::QuantizeEigenMatrix(parameters_);
}

}
