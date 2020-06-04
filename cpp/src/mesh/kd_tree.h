#ifndef _MESH_KD_TREE_H_
#define _MESH_KD_TREE_H_

#include <memory>
#include <vector>
#include "Eigen/Dense"
#include "mesh/kd_tree_node.h"
#include "mesh/intersection.h"

namespace mesh {

class TriMesh;

class KdTree {
public:
  explicit KdTree(const TriMesh& shape);

  void BuildKdTree(const int max_depth = 5,
    const int max_triangle_num = 10);
  // Return the first intersection in (tmin, tmax).
  void Intersect(const Eigen::Vector3d& origin, const Eigen::Vector3d& dir,
    const double tmin, const double tmax, Intersection& inter) const;

private:
  const std::shared_ptr<KdTreeNode> BuildKdTreeNode(
    const Eigen::Vector3d& pmin, const Eigen::Vector3d& pmax,
    const std::vector<int>& triangles, const int depth,
    const int max_depth, const int max_triangle_num) const;
  void IntersectKdTreeNode(const std::shared_ptr<KdTreeNode> node,
    const Eigen::Vector3d& origin, const Eigen::Vector3d& dir,
    const double tmin, const double tmax, Intersection& inter) const;

  const TriMesh& shape_;
  std::shared_ptr<KdTreeNode> root_;
};

}

#endif
