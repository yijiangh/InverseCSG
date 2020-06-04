#include "csg/csg_node.h"
#include <iostream>
#include <sstream>
#include "common/file_helper.h"
#include "common/math_helper.h"

namespace csg {

CsgNode::CsgNode(const std::string& type_name, const csg_node_list& children,
  const Eigen::Matrix4d& transform)
  : type_name_(type_name), children_(children) {
  // Check transform.
  if (!common::IsValidTransform(transform)) {
    std::cerr << common::RedHead()
      << "csg::CsgNode::CsgNode: invalid transform."
      << common::RedTail() << std::endl;
    exit(-1);
  }
  transform_ = transform;
  inv_transform_ = common::InverseTransform(transform);
}

CsgNode::~CsgNode() {}

const bool CsgNode::IsLeaf() const {
  return children_.empty();
}

const int CsgNode::NumOfChildren() const {
  return static_cast<int>(children_.size());
}

const std::string CsgNode::type_name() const {
  return type_name_;
}

const csg_node_list& CsgNode::children() const {
  return children_;
}

void CsgNode::set_children(const int idx,
  const std::shared_ptr<csg::CsgNode>& node) {
  if (idx < 0 || idx >= NumOfChildren()) {
    common::PrintError("csg::CsgNode::set_children: index out of bound.");
  }
  children_.at(idx) = node;
}

const Eigen::Matrix4d CsgNode::transform() const {
  return transform_;
}

const Eigen::Matrix4d CsgNode::inv_transform() const {
  return inv_transform_;
}

const bool CsgNode::IsInside(const Eigen::Vector3d& point) const {
  return IsInsideUntransformedShape(
    common::TransformPoint(inv_transform_, point));
}

const std::string CsgNode::WriteToString() const {
  std::vector<std::string> lines(0);
  WriteToFormattedString(lines);
  std::ostringstream ss;
  for (const auto& line : lines) {
    ss << line << std::endl;
  }
  return ss.str();
}

void CsgNode::WriteToFormattedString(std::vector<std::string>& lines) const {
  lines.clear();
  Eigen::Vector3d rpy, t;
  common::TransformToRotationAndTranslation(transform_, rpy, t);
  const double roll = common::RadianToDegree(rpy.x()),
    pitch = common::RadianToDegree(rpy.y()),
    yaw = common::RadianToDegree(rpy.z());

  if (t.cwiseAbs().maxCoeff() > 0.0) {
    std::ostringstream translate_str;
    translate_str << "translate([" << t.x() << ", " << t.y()
      << ", " << t.z() << "])";
    lines.push_back(translate_str.str());
  }
  if (roll != 0.0 || pitch != 0.0 || yaw != 0.0) {
    std::ostringstream rotate_str;
    rotate_str << "rotate([" << roll << ", " << pitch << ", " << yaw << "])";
    lines.push_back(rotate_str.str());
  }

  std::vector<std::string> untransformed_lines(0);
  WriteUntransformedShapeToFormattedString(untransformed_lines);
  lines.insert(lines.end(), untransformed_lines.begin(),
    untransformed_lines.end());
}

const int CsgNode::GetDepth() const {
  if (IsLeaf()) return 1;
  int max_depth = -1;
  for (const auto& kid : children_) {
    const int depth = kid->GetDepth();
    if (depth > max_depth) max_depth = depth;
  }
  return max_depth + 1;
}

const int CsgNode::GetSubtreeSize() const {
  if (IsLeaf()) return 1;
  int node_num = 1; 
  for (const auto& kid : children_) {
    node_num += kid->GetSubtreeSize();
  }
  return node_num;
}

}
