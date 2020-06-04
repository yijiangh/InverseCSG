#include "csg/csg_cube_node.h"
#include <iostream>
#include <sstream>
#include "common/file_helper.h"
#include "common/math_helper.h"

namespace csg {

CsgCubeNode::CsgCubeNode(const Eigen::Matrix4d& transform,
  const Eigen::Vector3d& size)
  : CsgNode("cube", csg_node_list(0), transform), size_(size) {
  if (size.minCoeff() < common::Epsilon()) {
    std::cerr << common::RedHead()
      << "csg::CsgCubeNode::CsgCubeNode: invalid size: "
      << size.transpose() << common::RedTail() << std::endl;
    exit(-1);
  }
}

const Eigen::Vector3d CsgCubeNode::size() const {
  return size_;
}

const bool CsgCubeNode::IsInsideUntransformedShape(
  const Eigen::Vector3d& point) const {
  return (size_ * 0.5 - point).minCoeff() > 0.0 &&
    (point + size_ * 0.5).minCoeff() > 0.0;
}

void CsgCubeNode::WriteUntransformedShapeToFormattedString(
  std::vector<std::string>& lines) const {
  lines.clear();
  std::ostringstream ss;
  ss << "cube(size = [" << size_.x() << ", " << size_.y() << ", " << size_.z()
    << "], center = true);";
  lines.push_back(ss.str());
}

}
