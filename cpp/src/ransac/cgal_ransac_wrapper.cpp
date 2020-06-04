#include "ransac/cgal_ransac_wrapper.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <tuple>
#include <set>
#include "CGAL/Exact_predicates_inexact_constructions_kernel.h"
#include "CGAL/IO/read_xyz_points.h"
#include "CGAL/Point_with_normal_3.h"
#include "CGAL/property_map.h"
#include "CGAL/Timer.h"
#include "CGAL/number_utils.h"
#include "CGAL/Shape_detection_3.h"
#include "common/file_helper.h"
#include "primitive/plane_surface.h"
#include "primitive/cylindrical_surface.h"
#include "primitive/spherical_surface.h"
#include "primitive/toric_surface.h"
#include "primitive/conical_surface.h"
#include "common/file_helper.h"

namespace ransac {

// Type declarations used in CGAL.
typedef CGAL::Exact_predicates_inexact_constructions_kernel  Kernel;
typedef std::tuple<Kernel::Point_3, Kernel::Vector_3, int>   PointWithNormal;
typedef std::vector<PointWithNormal>                         PwnVector;
typedef CGAL::Nth_of_tuple_property_map<0, PointWithNormal>  PointMap;
typedef CGAL::Nth_of_tuple_property_map<1, PointWithNormal>  NormalMap;
// In Shape_detection_traits the basic types, i.e., Point and Vector types
// as well as iterator type and property maps, are defined.
typedef CGAL::Shape_detection_3::Shape_detection_traits<Kernel,
    PwnVector, PointMap, NormalMap>            Traits;
typedef CGAL::Shape_detection_3::Efficient_RANSAC<Traits>    EfficientRansac;
typedef CGAL::Shape_detection_3::Plane<Traits>               Plane;
typedef CGAL::Shape_detection_3::Sphere<Traits>              Sphere;
typedef CGAL::Shape_detection_3::Cylinder<Traits>            Cylinder;
typedef CGAL::Shape_detection_3::Cone<Traits>                Cone;
typedef CGAL::Shape_detection_3::Torus<Traits>               Torus;

CgalRansacWrapper::CgalRansacWrapper(const mesh::TriMesh& shape)
  : shape_(shape), points_(3, 0), normals_(3, 0), point_to_face_(0),
  face_to_points_(0) {}

void CgalRansacWrapper::BuildPointSamples(const double density) {
  shape_.Sample(density, false, points_, normals_, point_to_face_);
  // Construct face_to_points_.
  const int face_num = shape_.NumOfFaces();
  face_to_points_ = std::vector<std::vector<int>>(face_num);
  const int sample_num = static_cast<int>(points_.cols());
  for (int i = 0; i < sample_num; ++i) {
    face_to_points_[point_to_face_(i)].push_back(i);
  }
}

const bool CgalRansacWrapper::CoverAllFaces() const {
  for (const auto& list : face_to_points_) {
    if (list.empty()) return false;
  }
  return true;
}

const int CgalRansacWrapper::NumOfSamples() const {
  return static_cast<int>(points_.cols());
}

const Eigen::Vector3d CgalRansacWrapper::point(const int point_id) const {
  if (point_id < 0 || point_id >= NumOfSamples()) {
    common::PrintError("ransac::CgalRansacWrapper::point: invalid "
      "point id.");
  }
  return points_.col(point_id);
}

const std::vector<int>& CgalRansacWrapper::face_to_points(const int face_id)
  const {
  if (face_id < 0 || face_id >= shape_.NumOfFaces()) {
    common::PrintError("ransac::CgalRansacWrapper::face_to_points: invalid "
      "face id.");
  }
  return face_to_points_[face_id];
}

const mesh::TriMesh& CgalRansacWrapper::shape() const {
  return shape_;
}

void CgalRansacWrapper::RunRansac(const double probability,
  const int min_points, const double epsilon, const double cluster_epsilon,
  const double normal_threshold,
  std::vector<std::shared_ptr<primitive::SurfacePrimitive>>& primitives,
  std::vector<std::vector<int>>& face_to_primitive) {
  // Prepare the input samples.
  const int sample_num = NumOfSamples();
  // Compute the bounding box of all points.
  const Eigen::Vector3d pmax = points_.rowwise().maxCoeff();
  const Eigen::Vector3d pmin = points_.rowwise().minCoeff();
  const double max_radius = (pmax - pmin).maxCoeff();
  // Points with normals.
  PwnVector points(0); points.reserve(sample_num);
  for (int i = 0; i < sample_num; ++i) {
    const Kernel::Point_3 p(points_(0, i), points_(1, i), points_(2, i));
    const Kernel::Vector_3 n(normals_(0, i), normals_(1, i), normals_(2, i));
    points.push_back(std::make_tuple(p, n, i));
  }
  // Instantiates shape detection engine.
  EfficientRansac ransac;
  // Provides the input data.
  ransac.set_input(points);
  // Registers detection of planes
  ransac.add_shape_factory<Plane>();
  ransac.add_shape_factory<Sphere>();
  ransac.add_shape_factory<Cylinder>();
  ransac.add_shape_factory<Torus>();
  //ransac.add_shape_factory<Cone>();
  // Detects shapes.
  EfficientRansac::Parameters parameters;
  parameters.probability = probability;
  parameters.min_points = min_points;
  parameters.epsilon = epsilon;
  parameters.cluster_epsilon = cluster_epsilon;
  parameters.normal_threshold = normal_threshold;
  ransac.detect(parameters);
  const EfficientRansac::Shape_range shapes = ransac.shapes();

  // Prepare the output.
  const int face_num = shape_.NumOfFaces();
  std::vector<std::set<int>> face_to_primitive_set(face_num);
  primitives.clear();
  for (const auto& primitive : shapes) {
    // Get specific parameters depending on detected shape.
    if (Plane* plane = dynamic_cast<Plane*>(primitive.get())) {
      // Build a plane.
      const Kernel::Vector_3 normal = plane->plane_normal();
      auto plane_primitive = std::make_shared<primitive::PlaneSurface>(
        Eigen::Vector3d(normal.x(), normal.y(), normal.z()), plane->d());
      primitives.push_back(plane_primitive);
    } else if (Cylinder* cyl = dynamic_cast<Cylinder*>(primitive.get())) {
      // Build a cylinder.
      Kernel::Line_3 axis = cyl->axis();
      const double radius = static_cast<double>(cyl->radius());
      // Skip if radius is too big.
      if (radius > max_radius) continue;
      const Eigen::Vector3d dir(axis.direction().dx(),
        axis.direction().dy(), axis.direction().dz());
      const Eigen::Vector3d point(axis.point().x(), axis.point().y(),
        axis.point().z());
      auto cyl_primitive = std::make_shared<primitive::CylindricalSurface>(
        point, dir, radius);
      primitives.push_back(cyl_primitive);
    } else if (Sphere* sph = dynamic_cast<Sphere*>(primitive.get())) {
      // Build a sphere.
      const Eigen::Vector3d center(sph->center().x(), sph->center().y(),
        sph->center().z());
      const double radius = static_cast<double>(sph->radius());
      if (radius > max_radius) continue;
      auto sph_primitive = std::make_shared<primitive::SphericalSurface>(center,
        radius);
      primitives.push_back(sph_primitive);
    } else if (Torus* tor = dynamic_cast<Torus*>(primitive.get())) {
      // Build a torus.
      const Eigen::Vector3d axis(tor->axis().x(), tor->axis().y(),
        tor->axis().z());
      const Eigen::Vector3d center(tor->center().x(), tor->center().y(),
        tor->center().z());
      const double major_radii = static_cast<double>(tor->major_radius());
      const double minor_radii = static_cast<double>(tor->minor_radius());
      if (major_radii > max_radius || minor_radii > max_radius
        || minor_radii >= major_radii) continue;
      auto tor_primitive = std::make_shared<primitive::ToricSurface>(center,
        axis, major_radii, minor_radii);
      primitives.push_back(tor_primitive);
    } else if (Cone* cone = dynamic_cast<Cone*>(primitive.get())) {
      // Build a cone.
      const Eigen::Vector3d apex(cone->apex().x(), cone->apex().y(),
        cone->apex().z());
      const Eigen::Vector3d axis(cone->axis().x(), cone->axis().y(),
        cone->axis().z());
      const double angle = static_cast<double>(cone->angle());
      auto cone_primitive = std::make_shared<primitive::ConicalSurface>(apex,
        axis, angle);
      primitives.push_back(cone_primitive);
    } else {
      common::PrintError("ransac::CgalRansacWrapper::RunRansac: unknown "
        "primitive type.");
    }
    for (const std::size_t idx : primitive->indices_of_assigned_points()) {
      const int old_idx = std::get<2>(points[idx]);
      const int fid = point_to_face_(old_idx);
      face_to_primitive_set[fid].insert(
        static_cast<int>(primitives.size()) - 1);
    }
  }
  // Make sure the returned face_to_primitive[i] are sorted and unique.
  face_to_primitive.clear();
  face_to_primitive.reserve(face_num);
  for (const auto& pid : face_to_primitive_set) {
    face_to_primitive.push_back({});
    for (const int idx : pid) {
      face_to_primitive.back().push_back(idx);
    }
  }
}

}
