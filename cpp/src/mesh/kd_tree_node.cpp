#include "kd_tree_node.h"
#include <iostream>
#include "common/file_helper.h"

namespace mesh {

KdTreeNode::KdTreeNode()
  : left_(nullptr), right_(nullptr), triangles_(0), pmin_(0, 0, 0),
  pmax_(0, 0, 0), split_(0) {}

void KdTreeNode::InitializeLeaf(const std::vector<int>& triangles,
  const Eigen::Vector3d& pmin, const Eigen::Vector3d& pmax) {
  triangles_ = triangles;
  if ((pmax - pmin).minCoeff() <= 0.0) {
    std::cerr << common::RedHead()
      << "mesh::KdTreeNode::InitializeLeaf: incorrect pmin and pmax: "
      << "pmin = (" << pmin.transpose() << "), pmax = (" << pmax.transpose()
      << ")." << common::RedTail() << std::endl;
    exit(-1);
  }
  pmin_ = pmin;
  pmax_ = pmax;
}

void KdTreeNode::InitializeInternalNode(const std::shared_ptr<KdTreeNode> left,
  const std::shared_ptr<KdTreeNode> right, const Eigen::Vector3d& pmin,
  const Eigen::Vector3d& pmax) {
  left_ = left;
  right_ = right;
  split_ = ComputeSplit(pmin, pmax);
  pmin_ = pmin;
  pmax_ = pmax;
}

const std::shared_ptr<KdTreeNode> KdTreeNode::left() const {
  return left_;
}

const std::shared_ptr<KdTreeNode> KdTreeNode::right() const {
  return right_;
}

const std::vector<int>& KdTreeNode::triangle() const {
  return triangles_;
}

const Eigen::Vector3d KdTreeNode::pmin() const {
  return pmin_;
}

const Eigen::Vector3d KdTreeNode::pmax() const {
  return pmax_;
}

const int KdTreeNode::split() const {
  return split_;
}

const bool KdTreeNode::IsLeaf() const {
  return !left_;
}

const int KdTreeNode::ComputeSplit(const Eigen::Vector3d& pmin,
  const Eigen::Vector3d& pmax) {
  if ((pmax - pmin).minCoeff() <= 0.0) {
    std::cerr << common::RedHead()
      << "mesh::KdTreeNode::InitializeLeaf: incorrect pmin and pmax: "
      << "pmin = (" << pmin.transpose() << "), pmax = (" << pmax.transpose()
      << ")." << common::RedTail() << std::endl;
    exit(-1);
  }
  // Compute split.
  int axis = 0, dummy = 0;
  (pmax - pmin).maxCoeff(&axis, &dummy);
  return axis;
}

}
