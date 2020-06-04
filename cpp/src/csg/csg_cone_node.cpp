#include "csg/csg_cone_node.h"
#include <iostream>
#include <sstream>
#include "common/file_helper.h"
#include "common/math_helper.h"

namespace csg {

CsgConeNode::CsgConeNode(const Eigen::Matrix4d& transform, const double height,
    const double top_radius, const double bottom_radius,
    const int resolution)
  : CsgNode("cone", csg_node_list(0), transform),
  height_(height), top_radius_(top_radius), bottom_radius_(bottom_radius),
  resolution_(resolution) {
  if (height < common::Epsilon()) {
    std::cerr << common::RedHead()
      << "csg::CsgConeNode::CsgConeNode: invalid height: "
      << height << common::RedTail() << std::endl;
    exit(-1);
  }
  if (top_radius < common::Epsilon()) {
    std::cerr << common::RedHead()
      << "csg::CsgConeNode::CsgConeNode: invalid top radius: "
      << top_radius << common::RedTail() << std::endl;
    exit(-1);
  }
  if (bottom_radius < common::Epsilon()) {
    std::cerr << common::RedHead()
      << "csg::CsgConeNode::CsgConeNode: invalid bottom radius: "
      << bottom_radius << common::RedTail() << std::endl;
    exit(-1);
  }
  if (resolution < 3) {
    std::cerr << common::RedHead()
      << "csg::CsgConeNode::CsgConeNode: invalid resolution: "
      << resolution << common::RedTail() << std::endl;
    exit(-1);
  }
}

const double CsgConeNode::height() const {
  return height_;
}

const double CsgConeNode::top_radius() const {
  return top_radius_;
}

const double CsgConeNode::bottom_radius() const {
  return bottom_radius_;
}

const int CsgConeNode::resolution() const {
  return resolution_;
}

const bool CsgConeNode::IsInsideUntransformedShape(
  const Eigen::Vector3d& point) const {
  const double z = point.z();
  const double zmin = -height_ * 0.5;
  const double zmax = height_ * 0.5;
  // z = zmin -> bottom_radius
  // z = zmax -> top_radius
  const double r = (z - zmin) / (zmax - zmin) * (top_radius_ - bottom_radius_)
    + bottom_radius_;
  return point.head(2).squaredNorm() < r * r && z < zmax && z > zmin;
}

void CsgConeNode::WriteUntransformedShapeToFormattedString(
  std::vector<std::string>& lines) const {
  lines.clear();
  std::ostringstream ss;
  ss << "cylinder(h = " << height_ << ", r1 = " << bottom_radius_
    << ", r2 = " << top_radius_ << ", center = true, $fn = "
    << resolution_ << ");";
  lines.push_back(ss.str());
}

}
