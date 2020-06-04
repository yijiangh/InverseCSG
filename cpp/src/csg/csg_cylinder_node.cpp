#include "csg/csg_cylinder_node.h"
#include <iostream>
#include <sstream>
#include "common/file_helper.h"
#include "common/math_helper.h"

namespace csg {

CsgCylinderNode::CsgCylinderNode(const Eigen::Matrix4d& transform,
  const double height, const double radius, const int resolution)
  : CsgNode("cylinder", csg_node_list(0), transform),
  height_(height), radius_(radius), resolution_(resolution) {
  if (height < common::Epsilon()) {
    std::cerr << common::RedHead()
      << "csg::CsgCylinderNode::CsgCylinderNode: invalid height: "
      << height << common::RedTail() << std::endl;
    exit(-1);
  }
  if (radius < common::Epsilon()) {
    std::cerr << common::RedHead()
      << "csg::CsgCylinderNode::CsgCylinderNode: invalid radius: "
      << radius << common::RedTail() << std::endl;
    exit(-1);
  }
  if (resolution < 3) {
    std::cerr << common::RedHead()
      << "csg::CsgCylinderNode::CsgCylinderNode: invalid resolution: "
      << resolution << common::RedTail() << std::endl;
    exit(-1);
  }
}

const double CsgCylinderNode::height() const {
  return height_;
}

const double CsgCylinderNode::radius() const {
  return radius_;
}

const int CsgCylinderNode::resolution() const {
  return resolution_;
}

const bool CsgCylinderNode::IsInsideUntransformedShape(
  const Eigen::Vector3d& point) const {
  return point.head(2).squaredNorm() < radius_ * radius_ &&
    point.z() < height_ * 0.5 && point.z() > -height_ * 0.5;
}

void CsgCylinderNode::WriteUntransformedShapeToFormattedString(
  std::vector<std::string>& lines) const {
  lines.clear();
  std::ostringstream ss;
  ss << "cylinder(h = " << height_ << ", r1 = " << radius_ << ", r2 = "
    << radius_ << ", center = true, $fn = " << resolution_ << ");";
  lines.push_back(ss.str());
}

}
