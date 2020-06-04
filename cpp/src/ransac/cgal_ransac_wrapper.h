#ifndef _RANSAC_CGAL_RANSAC_WRAPPER_H_
#define _RANSAC_CGAL_RANSAC_WRAPPER_H_

#include <vector>
#include <memory>
#include "Eigen/Dense"
#include "mesh/tri_mesh.h"
#include "primitive/surface_primitive.h"

namespace ransac {

// To use this class, follow the steps below:
// - Construct a CgalRansacWrapper object.
// - Call BuildPointSamples with given sampling density. This will inherently
//   sample points on the surface of the mesh and save them inside the class.
// - Call RunRansac to get the primitives and which faces each primitive covers.
//   This function calls CGAL's efficient-RANSAC on the samples. Since there is
//   randomness, calling this function twice will almost surely give you
//   different set of primitives.

class CgalRansacWrapper {
public:
  CgalRansacWrapper(const mesh::TriMesh& shape);

  void BuildPointSamples(const double density);
  // This function check if samples have covered all faces. The typical usage is
  // to use it to check if density in BuildPointSamples is high enough, e.g.:
  // while (!CoverAllFaces()) {
  //   density *= 2;
  //   BuildPointSamples(deni sity);
  // }
  const bool CoverAllFaces() const;
  const int NumOfSamples() const;
  const Eigen::Vector3d point(const int point_id) const;
  const std::vector<int>& face_to_points(const int face_id) const;
  const mesh::TriMesh& shape() const;
  // The meaning of each parameter can be found in this page:
  // https://doc.cgal.org/latest/Point_set_shape_detection_3/index.html
  // This function is just a wrapper of the example code presented in CGAL.
  // Roughly speaking:
  // Larger probability <-> less reilable but faster.
  // Larger min_points <-> early termination.
  // Larger epsilon/normal_threshold <-> less reliable, fewer oversegmenation.
  // Larger cluster_epsilon <-> fewer oversegmentation.
  void RunRansac(const double probability, const int min_points,
    const double epsilon, const double cluster_epsilon,
    const double normal_threshold,
    std::vector<std::shared_ptr<primitive::SurfacePrimitive>>& primitives,
    std::vector<std::vector<int>>& face_to_primitive);

private:
  const mesh::TriMesh& shape_;

  // Sample points and their corresponding normals. Both have the same number of
  // columns.
  Eigen::Matrix3Xd points_, normals_;
  // For each point, maps it to the face it belongs to.
  Eigen::VectorXi point_to_face_;
  // For each face, stores the indices of samples on it.
  std::vector<std::vector<int>> face_to_points_;
};

}

#endif
