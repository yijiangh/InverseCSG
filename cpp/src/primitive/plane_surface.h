#ifndef _PRIMITIVE_PLANE_SURFACE_H_
#define _PRIMITIVE_PLANE_SURFACE_H_

#include "primitive/surface_primitive.h"

namespace primitive {

class PlaneSurface : public SurfacePrimitive {
public:
  // normal.dot(point) + offset = 0.
  PlaneSurface();
  PlaneSurface(const Eigen::Vector3d& normal, const double offset);

  std::shared_ptr<SurfacePrimitive> Duplicate() const override;

  const double Evaluate(const Eigen::Vector3d& point) const override;
  const Eigen::VectorXd Gradient(const Eigen::Vector3d& point) const override;
  const Eigen::VectorXd InitialGuess(const Eigen::Matrix3Xd& points,
    const Eigen::Matrix3Xd& normals) const override;
  const double Fit(const Eigen::Matrix3Xd& points,
    const Eigen::Matrix3Xd& normals) override;
  const Eigen::Vector3d SurfaceNormal(
    const Eigen::Vector3d& point_on_surface) const override;
  void Sample(const double min_dist, const double max_dist,
    const Eigen::Vector3d& box_min, const Eigen::Vector3d& box_max,
    const double density, std::vector<Eigen::Vector3d>& samples) const override;
  const double DistToSurface(const Eigen::Vector3d& point) const override;
  void ReadFromString(const std::string& str) override;
  const std::string WriteToString() const override;
  const bool IntersectRoi(const Eigen::Vector3d& pmin,
    const Eigen::Vector3d& pmax) const override;

  const Eigen::Vector3d Normal() const;
  const double Offset() const;

  // Add this surface type to the static member in SurfacePrimitive.
  static void Register();

private:
  void Normalize() override;
};

void TestPlaneSurfaceFit();

}

#endif
