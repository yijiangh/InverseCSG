#ifndef _MESH_TRI_MESH_H_
#define _MESH_TRI_MESH_H_

#include <string>
#include "Eigen/Dense"
#include "mesh/kd_tree.h"
#include "mesh/intersection.h"

namespace mesh {

class TriMesh {
public:
  TriMesh();

  // The triangles will be reordered in the constructors below so do not expect
  // the resulting faces are in the same order as they are in the file or input
  // matrices.
  void Initialize(const std::string& file_name);
  void Initialize(const Eigen::Matrix3Xd& vertices,
    const Eigen::Matrix3Xi& faces);

  // Getter.
  const Eigen::Matrix3Xd vertices() const;
  const Eigen::Vector3d vertex(const int vertex_id) const;
  const Eigen::Matrix3Xi faces() const;
  const Eigen::Vector3i face(const int face_id) const;
  const Eigen::VectorXd areas() const;
  const Eigen::Matrix3Xd vertex_normals() const;
  const Eigen::Matrix3Xd face_normals() const;
  const double area(const int face_id) const;
  const Eigen::Vector3d vertex_normal(const int vertex_id) const;
  const Eigen::Vector3d face_normal(const int face_id) const;
  const int NumOfVertices() const;
  const int NumOfFaces() const;
  const int NumOfEdges() const;
  const Eigen::Matrix3d Triangle(const int face_id) const;
  const Eigen::Vector3d box_min() const;
  const Eigen::Vector3d box_max() const;
  const std::vector<int> face_neighbor(const int face_id) const;
  const Eigen::Vector3i face_edge(const int face_id) const;
  const std::vector<int> edge_neighbor(const int edge_id) const;

  void WriteToFile(const std::string& file_name) const;

  // density = number / area.
  // point_to_face[i] is the face that point i is sampled from.
  // We provide two sampling methods: if fully_random is true, then we will
  // first randomly pick a triangle with the prob being proportional to the
  // area), then uniformly sample a point inside the triangle. This way is
  // more "uniform" but we might miss samples from some triangles. If we set
  // fully_random = false, we will first assign the number of samples to each
  // triangle with prob being proportional to the area, then sample that many
  // points on that face. In this way we guarantee at least one point is seen
  // on each (non-singular) face. In both case, we skip faces with singular
  // normals.
  void Sample(const double density, const bool fully_random,
    Eigen::Matrix3Xd& points, Eigen::Matrix3Xd& normals,
    Eigen::VectorXi& point_to_face) const;


  // Kd-tree.
  const KdTree& kd_tree() const;
  const bool IsInside(const Eigen::Vector3d& point) const;

  // Intersect the triangle of index idx in (tmin, tmax).
  const void IntersectTriangle(const int idx, const Eigen::Vector3d& origin,
    const Eigen::Vector3d& dir, const double tmin, const double tmax,
    Intersection& inter) const;

private:
  void InitializeAfterVerticesAndFaces();
  void SampleWithoutFullRandomness(const double density,
    Eigen::Matrix3Xd& points, Eigen::Matrix3Xd& normals,
    Eigen::VectorXi& point_to_face) const;
  void SampleWithFullRandomness(const double density, Eigen::Matrix3Xd& points,
    Eigen::Matrix3Xd& normals, Eigen::VectorXi& point_to_face) const;

  Eigen::Matrix3Xd vertices_;
  Eigen::Matrix3Xi faces_;
  Eigen::VectorXd areas_;
  // This is only used by IsInside.
  Eigen::VectorXi sorted_face_id_;
  // Vertex normals is the weighted average of adjacent face normals.
  Eigen::Matrix3Xd vertex_normals_;
  Eigen::Matrix3Xd face_normals_;

  KdTree kd_tree_;

  // Bounding boxes.
  Eigen::Vector3d box_min_, box_max_;

  // Topology.
  // For each face, we store the indices of its adjacent faces. There are at
  // most three of them and they are not stored in any particular order.
  std::vector<std::vector<int>> face_neighbors_;
  // For each face, store the indices of its three edges. They are not in any
  // particular order.
  std::vector<Eigen::Vector3i> face_edges_;
  // For each edge, store its adjacent faces. Ideally each edge should have
  // exactly 2 faces, but we allow for various face numbers for flexibility.
  std::vector<std::vector<int>> edge_neighbors_;
};

}

#endif
