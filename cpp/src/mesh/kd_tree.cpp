#include "kd_tree.h"
#include <iostream>
#include "mesh/tri_mesh.h"
#include "common/math_helper.h"

namespace mesh {

static const bool Overlap(const Eigen::Vector3d& a_min,
  const Eigen::Vector3d& a_max, const Eigen::Vector3d& b_min,
  const Eigen::Vector3d& b_max) {
  for (int i = 0; i < 3; ++i)
    if (a_max(i) < b_min(i) || b_max(i) < a_min(i)) return false;
  return true;
}

static const bool IntersectBox(const Eigen::Vector3d& origin,
  const Eigen::Vector3d& dir, const Eigen::Vector3d& pmin,
  const Eigen::Vector3d& pmax, const double tmin, const double tmax) {
  double border_tmin = tmin, border_tmax = tmax;
  // Return false as soon as border_tmin > border_tmax.
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
      if (border_tmin < t0) border_tmin = t0;
      if (border_tmax > t1) border_tmax = t1;
      if (border_tmin > border_tmax) return false;
    }
  }
  return true;
}

KdTree::KdTree(const TriMesh& shape)
  : shape_(shape), root_(nullptr) {}

void KdTree::BuildKdTree(const int max_depth, const int max_triangle_num) {
  const double eps = common::Epsilon();
  const Eigen::Vector3d pmin = shape_.box_min().array() - eps;
  const Eigen::Vector3d pmax = shape_.box_max().array() + eps;
  const int triangle_num = shape_.NumOfFaces();
  std::vector<int> triangles(triangle_num, 0);
  for (int i = 0; i < triangle_num; ++i) triangles[i] = i;
  root_ = BuildKdTreeNode(pmin, pmax, triangles, 0, max_depth,
    max_triangle_num);
}

void KdTree::Intersect(const Eigen::Vector3d& origin,
  const Eigen::Vector3d& dir, const double tmin, const double tmax,
  Intersection& inter) const {
  IntersectKdTreeNode(root_, origin, dir, tmin, tmax, inter);
}

const std::shared_ptr<KdTreeNode> KdTree::BuildKdTreeNode(
  const Eigen::Vector3d& pmin, const Eigen::Vector3d& pmax,
  const std::vector<int>& triangles, const int depth,
  const int max_depth, const int max_triangle_num) const {
  const int triangle_num = static_cast<int>(triangles.size());
  std::shared_ptr<KdTreeNode> node = std::make_shared<KdTreeNode>();
  if (depth >= max_depth || triangle_num <= max_triangle_num) {
    // Leaf node.
    node->InitializeLeaf(triangles, pmin, pmax);
    return node;
  }
  // Split.
  const int axis = KdTreeNode::ComputeSplit(pmin, pmax);
  const double mid = (pmin + pmax)(axis) * 0.5;
  Eigen::Vector3d left_pmax = pmax; left_pmax(axis) = mid;
  Eigen::Vector3d right_pmin = pmin; right_pmin(axis) = mid;
  // Find overlapping triangles.
  std::vector<int> left_triangles(0), right_triangles(0);
  for (const int idx : triangles) {
    const Eigen::Matrix3d triangle = shape_.Triangle(idx);
    const Eigen::Vector3d face_pmin = triangle.rowwise().minCoeff(),
      face_pmax = triangle.rowwise().maxCoeff();
    // Check if [face_pmin, face_max] overlaps with [pmin, left_pmax].
    if (Overlap(face_pmin, face_pmax, pmin, left_pmax))
      left_triangles.push_back(idx);
    // Check if [face_pmin, face_max] overlaps with [right_pmin, pmax].
    if (Overlap(face_pmin, face_pmax, right_pmin, pmax))
      right_triangles.push_back(idx);
  }
  const std::shared_ptr<KdTreeNode> left = BuildKdTreeNode(pmin, left_pmax,
    left_triangles, depth + 1, max_depth, max_triangle_num);
  const std::shared_ptr<KdTreeNode> right = BuildKdTreeNode(right_pmin, pmax,
    right_triangles, depth + 1, max_depth, max_triangle_num);
  node->InitializeInternalNode(left, right, pmin, pmax);
  return node;
}

void KdTree::IntersectKdTreeNode(const std::shared_ptr<KdTreeNode> node,
  const Eigen::Vector3d& origin, const Eigen::Vector3d& dir,
  const double tmin, const double tmax, Intersection& inter) const {
  inter = Intersection::NoIntersection();
  if (node->IsLeaf()) {
    // Loop over all triangles.
    double new_tmax = tmax;
    for (const int idx : node->triangle()) {
      Intersection triangle_inter;
      shape_.IntersectTriangle(idx, origin, dir, tmin, new_tmax,
        triangle_inter);
      if (triangle_inter.uncertain()) {
        // Give up.
        inter = Intersection::UncertainIntersection();
        return;
      }
      if (triangle_inter.hit()) {
        inter = triangle_inter;
        new_tmax = triangle_inter.t();
      }
    }
    return;
  }
  // Internal node.
  Intersection left_inter = Intersection::NoIntersection(),
    right_inter = Intersection::NoIntersection();
  // Check left node.
  if (IntersectBox(origin, dir, node->left()->pmin(), node->left()->pmax(),
    tmin, tmax)) {
    IntersectKdTreeNode(node->left(), origin, dir, tmin, tmax, left_inter);
    if (left_inter.uncertain()) {
      // Give up.
      inter = Intersection::UncertainIntersection();
      return;
    }
  }
  // Now left_inter is either a clear miss, or a clear hit.
  // Check right node.
  const double new_tmax = (!left_inter.uncertain() && left_inter.hit())
    ? left_inter.t() : tmax;
  if (IntersectBox(origin, dir, node->right()->pmin(), node->right()->pmax(),
    tmin, new_tmax)) {
    IntersectKdTreeNode(node->right(), origin, dir, tmin,
      new_tmax, right_inter);
    if (right_inter.uncertain()) {
      // Give up.
      inter = Intersection::UncertainIntersection();
      return;
    }
  }
  inter = right_inter.hit() ? right_inter : left_inter;
}

}
