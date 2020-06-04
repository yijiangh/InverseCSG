#include "common/math_helper.h"
#include <cmath>
#include <limits>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

namespace common {

const double Infinity() {
  return std::numeric_limits<double>::max();
}

const double Epsilon() {
  return 1e-5;
}

const double Pi() {
  return 3.14159265358979323846264335;
}

const double RadianToDegree(const double angle) {
  return angle / Pi() * 180.0;
}

const double DegreeToRadian(const double angle) {
  return angle / 180.0 * Pi();
}

const double NormalizeAngle(const double angle) {
  const double pi = Pi();
  const double two_pi = 2.0 * pi;
  if (angle <= pi && angle > -pi) return angle;
  // angle - n * two_pi >= 0.
  const int n = (int)(angle / two_pi) + ((angle > 0) ? 0 : -1);
  double new_angle = angle - n * two_pi;
  // new_angle \in [0, two_pi).
  if (new_angle > pi) new_angle -= two_pi;
  // Clamp once more.
  if (new_angle > pi || new_angle <= -pi) new_angle = pi;
  return new_angle;
}

const Eigen::Vector3d ThetaPhiToDir(const Eigen::Vector2d& tp) {
  const double theta = tp.x(), phi = tp.y();
  const double sin_theta = sin(theta), cos_theta = std::cos(theta),
    sin_phi = sin(phi), cos_phi = std::cos(phi);
  return Eigen::Vector3d(sin_theta * cos_phi, cos_theta,
    sin_theta * sin_phi);
}

const Eigen::Vector2d DirToThetaPhi(const Eigen::Vector3d& xyz) {
  const double x = xyz.x(), y = xyz.y(), z = xyz.z();
  const double cos_theta = y;
  const double pi = Pi();
  if (std::fabs(1.0 - cos_theta) < Epsilon()) {
    return Eigen::Vector2d(0, 0);
  } else if (std::fabs(-1.0 - cos_theta) < Epsilon()) {
    return Eigen::Vector2d(pi, 0);
  } else {
    // Now we know sin_theta != 0.
    const double phi = NormalizeAngle(std::atan2(z, x));
    const double sin_phi = sin(phi), cos_phi = std::cos(phi);
    double sin_theta = 0.0;
    // x = sin_theta * cos_phi, y = cos_theta, z = sin_theta * sin_phi.
    if (std::fabs(sin_phi) > std::fabs(cos_phi)) sin_theta = z / sin_phi;
    else sin_theta = x / cos_phi;
    const double theta = NormalizeAngle(std::atan2(sin_theta, y));
    return Eigen::Vector2d(theta, phi);
  }
}

const Eigen::MatrixXd ThetaPhiToDirJacobian(const Eigen::Vector2d& tp) {
  Eigen::MatrixXd J = Eigen::MatrixXd::Zero(3, 2);
  const double theta = tp.x(), phi = tp.y();
  const double sin_theta = sin(theta), cos_theta = std::cos(theta),
    sin_phi = sin(phi), cos_phi = std::cos(phi);
  J(0, 0) = cos_theta * cos_phi; J(0, 1) = -sin_theta * sin_phi;
  J(1, 0) = -sin_theta; J(1, 1) = 0;
  J(2, 0) = cos_theta * sin_phi; J(2, 1) = sin_theta * cos_phi;
  return J;
}

const Eigen::Vector3d PointToSphericalCoordinate(const Eigen::Vector3d& xyz) {
  const double rho = xyz.norm();
  if (rho < Epsilon()) return Eigen::Vector3d(0.0, 0.0, 0.0);
  return (Eigen::Vector3d() << DirToThetaPhi(xyz / rho), rho).finished();
}

const Eigen::Vector3d SphericalCoordinateToPoint(const Eigen::Vector3d& tpr) {
  return ThetaPhiToDir(tpr.head(2)) * tpr(2);
}

const Eigen::Matrix3d SphericalCoordinateToPointJacobian(
  const Eigen::Vector3d& tpr) {
  Eigen::Matrix3d gradient;
  gradient.leftCols(2) = tpr(2) * ThetaPhiToDirJacobian(tpr.head(2));
  gradient.col(2) = ThetaPhiToDir(tpr.head(2));
  return gradient;
}

const double QuantizeRealNumber(const double value) {
  const double step = Epsilon();
  return static_cast<int>(value / step + (value >= 0 ? 0.5 : -0.5)) * step;
}

const Eigen::MatrixXd QuantizeEigenMatrix(const Eigen::MatrixXd& values) {
  return values.unaryExpr([](const double value) {
    return QuantizeRealNumber(value);
  });
}

const bool IsValidTransform(const Eigen::Matrix4d& T) {
  if (T(3, 0) != 0.0 || T(3, 1) != 0.0 || T(3, 2) != 0.0 || T(3, 3) != 1.0)
    return false;
  // No scaling is allowed in our case.
  const Eigen::Matrix3d R = T.topLeftCorner(3, 3);
  return (R * R.transpose() - Eigen::Matrix3d::Identity()).norm() < Epsilon();
}

const Eigen::Matrix4d InverseTransform(const Eigen::Matrix4d& T) {
  const Eigen::Matrix3d R = T.topLeftCorner(3, 3);
  const Eigen::Vector3d t = T.topRightCorner(3, 1);
  // y = R * x + t => x = R' * (y - t) = R' * y - R' * t.
  const Eigen::Matrix3d Rt = R.transpose();
  Eigen::Matrix4d inv_T = Eigen::Matrix4d::Identity();
  inv_T.topLeftCorner(3, 3) = Rt;
  inv_T.topRightCorner(3, 1) = -Rt * t;
  return inv_T;
}

const Eigen::Matrix3d RollPitchYawToRotation(const Eigen::Vector3d& rpy) {
  const double roll = rpy(0), pitch = rpy(1), yaw = rpy(2);
  return Eigen::AngleAxisd(yaw, Eigen::Vector3d::UnitZ())
    * Eigen::AngleAxisd(pitch, Eigen::Vector3d::UnitY())
    * Eigen::AngleAxisd(roll, Eigen::Vector3d::UnitX()).matrix();
}

const Eigen::Vector3d RotationToRollPitchYaw(const Eigen::Matrix3d& R) {
  // The three angles are computed based on the slides here:
  // http://www.princeton.edu/~stengel/MAE331Lecture9.pd, page 3.
  double roll, pitch, yaw;
  const Eigen::Vector3d XI = Eigen::Vector3d::UnitX();
  const Eigen::Vector3d ZI = Eigen::Vector3d::UnitZ();
  const Eigen::Vector3d XB = R.col(0), YB = R.col(1), ZB = R.col(2);
  // Let's first rotate along XB to compute Y2.
  const Eigen::Vector3d Y2 = ZI.cross(XB).normalized();
  double cos_roll = Y2.dot(YB);
  // Clamp cosRoll (if necessary).
  if (cos_roll > 1.0) cos_roll = 1.0;
  if (cos_roll < -1.0) cos_roll = -1.0;
  roll = std::acos(cos_roll);
  // Check to see whether we need to swap the sign of roll.
  if (Y2.dot(ZB) > 0) roll = -roll;

  // Next let's rotate along Y2 so that X1 falls into XOY plane.
  const Eigen::Vector3d X1 = Y2.cross(ZI).normalized();
  double cos_pitch = X1.dot(XB);
  // Clamp cosPitch.
  if (cos_pitch > 1.0) cos_pitch = 1.0;
  if (cos_pitch < -1.0) cos_pitch = -1.0;
  pitch = std::acos(cos_pitch);
  // Check to see whether we need to swap the sign of pitch.
  if (XB(2) > 0) pitch = -pitch;

  // We finally need to rotate along ZI to compute yaw.
  double cos_yaw = X1.dot(XI);
  // Clamp cosYaw.
  if (cos_yaw > 1.0) cos_yaw = 1.0;
  if (cos_yaw < -1.0) cos_yaw = -1.0;
  yaw = std::acos(cos_yaw);
  if (X1(1) < 0) yaw = -yaw;
  return Eigen::Vector3d(roll, pitch, yaw);
  // Sanity check:
  // const Matrix3 R1 = AngleAxis(yaw, Vector3::UnitZ())
  //  * AngleAxis(pitch, Vector3::UnitY())
  //  * AngleAxis(roll, Vector3::UnitX()).matrix();
  // const Matrix3 R2 = AngleAxis(roll, XB)
  //   * AngleAxis(pitch, Y2)
  //   * AngleAxis(yaw, ZI).matrix();
  // std::cout << "Diff between R and R1 = " << (R - R1).norm() << std::endl;
  // std::cout << "Diff between R and R2 = " << (R - R2).norm() << std::endl;
}

void TransformToRotationAndTranslation(const Eigen::Matrix4d& T,
  Eigen::Vector3d& rpy, Eigen::Vector3d& t) {
  rpy = RotationToRollPitchYaw(T.topLeftCorner(3, 3));
  t = T.topRightCorner(3, 1);
}

const Eigen::Matrix4d RotationAndTranslationToTransform(
  const Eigen::Vector3d& rpy, const Eigen::Vector3d& t) {
  Eigen::Matrix4d T = Eigen::Matrix4d::Identity();
  T.topLeftCorner(3, 3) = RollPitchYawToRotation(rpy);
  T.topRightCorner(3, 1) = t;
  return T;
}

const Eigen::Matrix4d RotationAndTranslationToTransform(
  const Eigen::Quaterniond& q, const Eigen::Vector3d& t) {
  Eigen::Matrix4d T = Eigen::Matrix4d::Identity();
  T.topLeftCorner(3, 3) = q.toRotationMatrix();
  T.topRightCorner(3, 1) = t;
  return T;
}

const Eigen::Matrix4d Translation(const Eigen::Vector3d& t) {
  Eigen::Matrix4d T = Eigen::Matrix4d::Identity();
  T.topRightCorner(3, 1) = t;
  return T;
}

const Eigen::Matrix4d Rotation(const Eigen::Vector3d& rpy) {
  Eigen::Matrix4d T = Eigen::Matrix4d::Identity();
  T.topLeftCorner(3, 3) = RollPitchYawToRotation(rpy);
  return T;
}

const Eigen::Vector3d TransformPoint(const Eigen::Matrix4d& T,
  const Eigen::Vector3d& p) {
  return T.topLeftCorner(3, 3) * p + T.topRightCorner(3, 1);
}

const Eigen::Matrix3Xd TransformPoints(const Eigen::Matrix4d& T,
  const Eigen::Matrix3Xd& p) {
  const Eigen::Vector3d t = T.topRightCorner(3, 1);
  return (T.topLeftCorner(3, 3) * p).colwise() + t;
}

const Eigen::Vector3d TransformVector(const Eigen::Matrix4d& T,
  const Eigen::Vector3d& v) {
  return T.topLeftCorner(3, 3) * v;
}

const double PointToTriangleDistance(const Eigen::Vector3d& point,
  const Eigen::Matrix3d& triangle) {
  // Min dist to corners.
  double dist = (triangle.col(0) - point).norm();
  for (int i = 1; i < 3; ++i) {
    const double new_dist = (triangle.col(i) - point).norm();
    if (new_dist < dist) dist = new_dist;
  }

  // Min dist to edges.
  const double eps = Epsilon();
  bool is_singular = false;
  for (int i = 0; i < 3; ++i) {
    const int j = (i + 1) % 3;
    const Eigen::Vector3d vi = triangle.col(i), vj = triangle.col(j);
    // <vi + t * (vj - vi) - p, vj - vi> = 0.
    // <vi - p, vj - vi> + t * <vj - vi, vj - vi> = 0.
    const double vij_sq_dist = (vj - vi).squaredNorm();
    if (vij_sq_dist < eps * eps) {
      is_singular = true;
      continue;
    }
    const double t = (point - vi).dot(vj - vi) / vij_sq_dist;
    if (t < 0.0 || t > 1.0) continue;
    const double new_dist = (vi + t * (vj - vi) - point).norm();
    if (new_dist < dist) dist = new_dist;
  }
  if (is_singular) return dist;

  // Finally, dist to the plane.
  const Eigen::Vector3d v0 = triangle.col(0), v1 = triangle.col(1),
    v2 = triangle.col(2);
  Eigen::Vector3d normal = (v1 - v0).cross(v2 - v1);
  const double double_area = normal.norm();
  if (double_area <= 2.0 * eps) return dist;
  normal /= double_area;
  const double t = (v1 - point).dot(normal);
  const Eigen::Vector3d project_p = t * normal + point;
  // Check if project_p is inside the triangle.
  // v0 + alpha * (v1 - v0) + beta * (v2 - v0) = project_p.
  Eigen::MatrixXd A(3, 2); A.col(0) = v1 - v0; A.col(1) = v2 - v0;
  const Eigen::Vector3d b = project_p - v0;
  const Eigen::Vector2d param = (A.transpose() * A).inverse()
    * A.transpose() * b;
  const double alpha = param.x(), beta = param.y();
  if (!param.allFinite() || alpha < 0.0 || alpha > 1.0
    || beta < 0.0 || beta > 1.0 || alpha + beta > 1.0) return dist;
  return std::fabs(t);
}

const double GenerateRandomFloat(const double lower, const double upper) {
  if (lower == upper) return lower;
  const Eigen::VectorXd seed = Eigen::VectorXd::Random(1);
  double val = seed(0) * (upper - lower) * 0.5 + (upper + lower) * 0.5;
  if (val < lower) val = lower;
  if (val > upper) val = upper;
  return val;
}

// Generate a random integer from {lower, 1, ..., upper - 1}.
const int GenerateRandomInt(const int lower,
  const int upper) {
  int idx = static_cast<int>(GenerateRandomFloat(0.0, (upper - lower) * 1.0))
    + lower;
  if (idx < lower) idx = lower;
  if (idx >= upper) idx = upper - 1;
  return idx;
}

const std::vector<int> GenerateRandomInts(const int lower, const int upper,
  const int number, const bool with_replacement) {
  std::vector<int> samples(0);
  samples.reserve(number);
  if (with_replacement) {
    for (int i = 0; i < number; ++i)
      samples.push_back(GenerateRandomInt(lower, upper));
  } else {
    int n = number;
    if (number > upper - lower) n = upper - lower;
    std::unordered_map<int, int> swap;
    // Imagine you have a big array a[i] = i, i = lower, lower + 1, ...,
    // upper - 1. At each iteration i, swap stores all the indices such that
    // a[idx] != idx, lower + i <= idx < upper.
    for (int i = 0; i < n; ++i) {
      int idx = GenerateRandomInt(lower + i, upper);
      // Swap [lower + i] and [idx].
      if (swap.find(idx) == swap.end()) {
        samples.push_back(idx);
      } else {
        samples.push_back(swap[idx]);
      }
      if (idx != lower + i) swap[idx] = (swap.find(lower + i) == swap.end())
        ? (lower + i) : swap[lower + i];
    }
  }
  return samples;
}

const Eigen::Matrix3Xd UniformSampleFromTriangle(const Eigen::Vector3d& v0,
  const Eigen::Vector3d& v1, const Eigen::Vector3d& v2, const int sample_num) {
  Eigen::Matrix2Xd barycentric_seed = Eigen::Matrix2Xd::Random(2, sample_num);
  Eigen::Matrix3Xd points(3, sample_num);
  for (int j = 0; j < sample_num; ++j) {
    double bary_alpha = barycentric_seed(0, j) * 0.5 + 0.5;
    double bary_beta = barycentric_seed(1, j) * 0.5 + 0.5;
    if (bary_alpha + bary_beta > 1.0) {
      const double x = bary_alpha, y = bary_beta;
      bary_alpha = 1.0 - y;
      bary_beta = 1.0 - x;
    }
    const Eigen::Vector3d point = v0 + bary_alpha * (v1 - v0)
      + bary_beta * (v2 - v0);
    points.col(j) = point;
  }
  return points;
}

}
