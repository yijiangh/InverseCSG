#ifndef _MESH_KD_TREE_NODE_H_
#define _MESH_KD_TREE_NODE_H_

#include <vector>
#include <memory>
#include "Eigen/Dense"

namespace mesh {

struct KdTreeNode {
public:
  KdTreeNode();

  void InitializeLeaf(const std::vector<int>& triangles,
    const Eigen::Vector3d& pmin, const Eigen::Vector3d& pmax);
  void InitializeInternalNode(const std::shared_ptr<KdTreeNode> left,
    const std::shared_ptr<KdTreeNode> right, const Eigen::Vector3d& pmin,
    const Eigen::Vector3d& pmax);

  const std::shared_ptr<KdTreeNode> left() const;
  const std::shared_ptr<KdTreeNode> right() const;
  const std::vector<int>& triangle() const;
  const Eigen::Vector3d pmin() const;
  const Eigen::Vector3d pmax() const;
  const int split() const;

  const bool IsLeaf() const;

  static const int ComputeSplit(const Eigen::Vector3d& pmin,
    const Eigen::Vector3d& pmax);

private:
  // Internal node: left_ != nullptr, right_ != nullptr, triangles_ is empty.
  // Leaf node: left_ = right_ = nullptr, triangles_ is nonempty.
  std::shared_ptr<KdTreeNode> left_, right_;
  std::vector<int> triangles_;
  // The bounding box of this node.
  Eigen::Vector3d pmin_, pmax_;
  // Split axis: 0 (x), 1 (y), 2 (z). Undefined for the leaf.
  int split_;
};

}

#endif