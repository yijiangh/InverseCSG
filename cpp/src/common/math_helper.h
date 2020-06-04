#ifndef _COMMON_MATH_HELPER_H_
#define _COMMON_MATH_HELPER_H_

#include <vector>
#include "Eigen/Dense"

namespace common {

const double Infinity();
const double Epsilon();

// Angles.
const double Pi();
const double RadianToDegree(const double angle);
const double DegreeToRadian(const double angle);
// angle -> (-pi, pi].
const double NormalizeAngle(const double angle);
// theta: [0, pi].
// pi: [0, 2pi].
// (sin(theta)cos(phi), cos(theta), sin(theta)sin(phi)).
const Eigen::Vector3d ThetaPhiToDir(const Eigen::Vector2d& tp);
const Eigen::Vector2d DirToThetaPhi(const Eigen::Vector3d& xyz);
const Eigen::MatrixXd ThetaPhiToDirJacobian(const Eigen::Vector2d& tp);
const Eigen::Vector3d PointToSphericalCoordinate(const Eigen::Vector3d& xyz);
const Eigen::Vector3d SphericalCoordinateToPoint(const Eigen::Vector3d& tpr);
const Eigen::Matrix3d SphericalCoordinateToPointJacobian(
  const Eigen::Vector3d& tpr);

// Round real numbers so that values whose difference <= Epsilon are the same.
const double QuantizeRealNumber(const double value);
const Eigen::MatrixXd QuantizeEigenMatrix(const Eigen::MatrixXd& values);

// Decompose transforms into rotation and translation. No scaling is allowed in
// our case.
const bool IsValidTransform(const Eigen::Matrix4d& T);
// It is strongly recommended to always call IsValidTransform before calling
// any functions below if necessary.
const Eigen::Matrix4d InverseTransform(const Eigen::Matrix4d& T);
const Eigen::Matrix3d RollPitchYawToRotation(const Eigen::Vector3d& rpy);
const Eigen::Vector3d RotationToRollPitchYaw(const Eigen::Matrix3d& R);
void TransformToRotationAndTranslation(const Eigen::Matrix4d& T,
  Eigen::Vector3d& rpy, Eigen::Vector3d& t);
const Eigen::Matrix4d RotationAndTranslationToTransform(
  const Eigen::Vector3d& rpy, const Eigen::Vector3d& t);
const Eigen::Matrix4d RotationAndTranslationToTransform(
  const Eigen::Quaterniond& q, const Eigen::Vector3d& t);
const Eigen::Matrix4d Translation(const Eigen::Vector3d& t);
const Eigen::Matrix4d Rotation(const Eigen::Vector3d& rpy);
const Eigen::Vector3d TransformPoint(const Eigen::Matrix4d& T,
  const Eigen::Vector3d& p);
const Eigen::Matrix3Xd TransformPoints(const Eigen::Matrix4d& T,
  const Eigen::Matrix3Xd& p);
const Eigen::Vector3d TransformVector(const Eigen::Matrix4d& T,
  const Eigen::Vector3d& v);

// Point to triangle distances. This function guarantees to return (almost)
// correct results even if triangle is singular.
const double PointToTriangleDistance(const Eigen::Vector3d& point,
  const Eigen::Matrix3d& triangle);

// Randomness.
const double GenerateRandomFloat(const double lower = 0.0,
  const double upper = 1.0);
// Generate a random integer from {0, 1, ..., upper - 1}.
const int GenerateRandomInt(const int lower, const int upper);
const std::vector<int> GenerateRandomInts(const int lower, const int upper,
  const int number, const bool with_replacement = false);

// Uniform sampling.
const Eigen::Matrix3Xd UniformSampleFromTriangle(const Eigen::Vector3d& v0,
  const Eigen::Vector3d& v1, const Eigen::Vector3d& v2, const int sample_num);

}

#endif
