#include "csg/csg_torus_node.h"
#include <iostream>
#include <sstream>
#include "common/file_helper.h"
#include "common/math_helper.h"

namespace csg {

CsgTorusNode::CsgTorusNode(const Eigen::Matrix4d& transform,
  const double major_radius, const double minor_radius,
  const int rotate_resolution, const int circle_resolution)
  : CsgNode("torus", csg_node_list(0), transform),
  major_radius_(major_radius), minor_radius_(minor_radius),
  rotate_resolution_(rotate_resolution), circle_resolution_(circle_resolution) {
  if (major_radius < common::Epsilon()) {
    std::cerr << common::RedHead()
      << "csg::CsgTorusNode::CsgTorusNode: invalid major radius: "
      << major_radius << common::RedTail() << std::endl;
    exit(-1);
  }
  if (minor_radius < common::Epsilon()) {
    std::cerr << common::RedHead()
      << "csg::CsgTorusNode::CsgTorusNode: invalid minor radius: "
      << minor_radius << common::RedTail() << std::endl;
    exit(-1);
  }
  if (rotate_resolution < 3) {
    std::cerr << common::RedHead()
      << "csg::CsgTorusNode::CsgTorusNode: invalid rotate resolution: "
      << rotate_resolution << common::RedTail() << std::endl;
    exit(-1);
  }
  if (circle_resolution < 3) {
    std::cerr << common::RedHead()
      << "csg::CsgTorusNode::CsgTorusNode: invalid circle resolution: "
      << circle_resolution << common::RedTail() << std::endl;
    exit(-1);
  }
}

const double CsgTorusNode::major_radius() const {
  return major_radius_;
}

const double CsgTorusNode::minor_radius() const {
  return minor_radius_;
}

const int CsgTorusNode::rotate_resolution() const {
  return rotate_resolution_;
}

const int CsgTorusNode::circle_resolution() const {
  return circle_resolution_;
}

const bool CsgTorusNode::IsInsideUntransformedShape(
  const Eigen::Vector3d& point) const {
  const Eigen::Vector3d z = Eigen::Vector3d::UnitZ();
  Eigen::Vector3d y = z.cross(point);
  const double y_len = y.norm();
  if (y_len < common::Epsilon()) {
    y = Eigen::Vector3d::UnitY();
  } else {
    y /= y_len;
  }
  const Eigen::Vector3d x = y.cross(z).normalized();
  const double px = x.dot(point);
  const double pz = z.dot(point);
  const Eigen::Vector2d p0(px, pz);
  const Eigen::Vector2d c0(major_radius_, 0);
  return (p0 - c0).norm() < minor_radius_;
}

void CsgTorusNode::WriteUntransformedShapeToFormattedString(
  std::vector<std::string>& lines) const {
  lines.clear();
  const std::string rot_fn = std::to_string(rotate_resolution_);
  const std::string cir_fn = std::to_string(circle_resolution_);
  const std::string R = std::to_string(major_radius_);
  const std::string r = std::to_string(minor_radius_);
  lines.push_back("rotate_extrude($fn = " + rot_fn + ")");
  lines.push_back("translate([" + R + ", 0, 0])");
  lines.push_back("circle(r = " + r + ", $fn = " + cir_fn + ");");
}

}
