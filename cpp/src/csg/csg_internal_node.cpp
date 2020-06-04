#include "csg/csg_internal_node.h"
#include <iostream>
#include "common/file_helper.h"

namespace csg {

CsgInternalNode::CsgInternalNode(const csg_node_list& children,
  const Eigen::Matrix4d& transform,
  const CsgInternalNodeOperator internal_operator)
  : CsgNode("internal", children, transform),
  internal_operator_(internal_operator) {
  if (children.empty()) {
    std::cerr << common::RedHead()
      << "csg::CsgInternalNode::CsgInternalNode: empty children."
      << common::RedTail() << std::endl;
    exit(-1);
  }
  if (internal_operator == CsgInternalNodeOperator::kSubtraction &&
    children.size() != 2u) {
    std::cerr << common::RedHead()
      << "csg::CsgInternalNode::CsgInternalNode: subtraction expects "
      << "two children." << common::RedTail() << std::endl;
    exit(-1);
  }
}

const CsgInternalNodeOperator CsgInternalNode::internal_operator() const {
  return internal_operator_;
}

const bool CsgInternalNode::IsInsideUntransformedShape(
  const Eigen::Vector3d& point) const {
  switch (internal_operator_) {
    case CsgInternalNodeOperator::kUnion: {
      for (const auto& child : children()) {
        if (child->IsInside(point)) return true;
      }
      return false;
    }
    case CsgInternalNodeOperator::kIntersection: {
      for (const auto& child : children()) {
        if (!child->IsInside(point)) return false;
      }
      return true;
    }
    case CsgInternalNodeOperator::kSubtraction: {
      return children()[0]->IsInside(point) && !children()[1]->IsInside(point);
    }
    default: {
      std::cerr << common::RedHead() << "csg::CsgInternalNode::"
        "WriteUntransformedShapeToFormattedString: unsupported operator."
        << common::RedTail() << std::endl;
      exit(-1);
    }
  }
  // Dummy return.
  return false;
}

void CsgInternalNode::WriteUntransformedShapeToFormattedString(
  std::vector<std::string>& lines) const {
  lines.clear();
  switch (internal_operator_) {
    case CsgInternalNodeOperator::kUnion: {
      lines.push_back("union() {");
      break;
    }
    case CsgInternalNodeOperator::kIntersection: {
      lines.push_back("intersection() {");
      break;
    }
    case CsgInternalNodeOperator::kSubtraction: {
      lines.push_back("difference() {");
      break;
    }
    default: {
      std::cerr << common::RedHead() << "csg::CsgInternalNode::"
        "WriteUntransformedShapeToFormattedString: unsupported operator."
        << common::RedTail() << std::endl;
      exit(-1);
    }
  }
  for (const auto& child : children()) {
    std::vector<std::string> child_lines(0);
    child->WriteToFormattedString(child_lines);
    for (const auto& line : child_lines) {
      lines.push_back("  " + line);
    }
    lines.push_back("");
  }
  lines.back() = "}";
}

}
