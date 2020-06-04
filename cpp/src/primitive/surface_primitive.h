#ifndef _PRIMITIVE_SURFACE_PRIMITIVE_H_
#define _PRIMITIVE_SURFACE_PRIMITIVE_H_

#include <memory>
#include <vector>
#include "Eigen/Dense"

namespace primitive {

class SurfacePrimitive {
public:
  SurfacePrimitive(const std::string& type_name,
    const Eigen::VectorXd& parameters);
  virtual ~SurfacePrimitive();

  // Copy. This allows us to copy a derived class from a base class.
  virtual std::shared_ptr<SurfacePrimitive> Duplicate() const = 0;

  // Getter.
  const std::string type_name() const;
  const Eigen::VectorXd parameters() const;

  // Compute f(point).
  virtual const double Evaluate(const Eigen::Vector3d& point) const = 0;
  // Compute df(point)/dparameter.
  virtual const Eigen::VectorXd Gradient(const Eigen::Vector3d& point)
    const = 0;
  // Choose to return a reasonable initial guess.
  virtual const Eigen::VectorXd InitialGuess(const Eigen::Matrix3Xd& points,
    const Eigen::Matrix3Xd& normals) const = 0;
  // Attempt to find the best parameters to fit points and normals. parameters
  // will be updated and the residual will be returned. If it fails the return
  // residual will be in, and parameters_ will be meaningless values.
  virtual const double Fit(const Eigen::Matrix3Xd& points,
    const Eigen::Matrix3Xd& normals);

  virtual const Eigen::Vector3d SurfaceNormal(
    const Eigen::Vector3d& point_on_surface) const = 0;
  // A point is on the surface if and long if |Evaluate(point)| < point_eps and
  // |normal.cross(SurfaceNormal(point)).norm| < normal_eps.
  const bool IsOnSurface(const Eigen::Vector3d& point,
    const Eigen::Vector3d& normal, const double point_eps,
    const double normal_eps) const;

  // Sampling.
  // Generate samples within the distance range (min_dist, max_dist) to the
  // surface and inside the bounding box (box_min, box_max). The number of
  // samples is controlled by density = #samples per unit volume.
  virtual void Sample(const double min_dist, const double max_dist,
    const Eigen::Vector3d& box_min, const Eigen::Vector3d& box_max,
    const double density, std::vector<Eigen::Vector3d>& samples) const = 0;
  // Point distance to the surface with signs. This is different from Evaluate.
  // Positive sign means the point is inside.
  virtual const double DistToSurface(const Eigen::Vector3d& point) const = 0;

  // Print a descriptive string.
  virtual void ReadFromString(const std::string& str) = 0;
  virtual const std::string WriteToString() const = 0;

  // Intersects a region of interest. Note that false positives are acceptable
  // as we can always filter redundant primitives later using remove-prim.
  virtual const bool IntersectRoi(const Eigen::Vector3d& pmin,
    const Eigen::Vector3d& pmax) const = 0;

  // Hold an instance to each surface primitive type.
  static std::vector<std::shared_ptr<SurfacePrimitive>> primitive_instances;

protected:
  // Convert parameters to a canonical form.
  virtual void Normalize();

  Eigen::VectorXd parameters_;

private:
  std::string type_name_;
};

}

#endif
