#include "csg/csg_sphere_node.h"
#include <iostream>
#include <sstream>
#include "common/file_helper.h"
#include "common/math_helper.h"

namespace csg {

CsgSphereNode::CsgSphereNode(const Eigen::Matrix4d& transform,
  const double radius, const int resolution)
  : CsgNode("sphere", csg_node_list(0), transform),
  radius_(radius), resolution_(resolution) {
  if (radius < common::Epsilon()) {
    std::cerr << common::RedHead()
      << "csg::CsgSphereNode::CsgSphereNode: invalid radius: "
      << radius << common::RedTail() << std::endl;
    exit(-1);
  }
  if (resolution < 3) {
    std::cerr << common::RedHead()
      << "csg::CsgSphereNode::CsgSphereNode: invalid resolution: "
      << resolution << common::RedTail() << std::endl;
    exit(-1);
  }
}

const double CsgSphereNode::radius() const {
  return radius_;
}

const int CsgSphereNode::resolution() const {
  return resolution_;
}

const bool CsgSphereNode::IsInsideUntransformedShape(
  const Eigen::Vector3d& point) const {
  return point.squaredNorm() < radius_ * radius_;
}

void CsgSphereNode::WriteUntransformedShapeToFormattedString(
  std::vector<std::string>& lines) const {
  lines.clear();
  std::ostringstream ss;
  ss << "sphere(r = " << radius_ << ", $fn = " << resolution_ << ");";
  lines.push_back(ss.str());
}

}
