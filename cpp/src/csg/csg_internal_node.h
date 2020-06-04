#ifndef _CSG_CSG_INTERNAL_NODE_H_
#define _CSG_CSG_INTERNAL_NODE_H_

#include "csg/csg_node.h"

namespace csg {

enum CsgInternalNodeOperator { kUnion = 0, kIntersection, kSubtraction };

class CsgInternalNode : public CsgNode {
public:
  CsgInternalNode(const csg_node_list& children,
    const Eigen::Matrix4d& transform,
    const CsgInternalNodeOperator internal_operator);

  const CsgInternalNodeOperator internal_operator() const;

private:
  const bool IsInsideUntransformedShape(const Eigen::Vector3d& point) const;
  void WriteUntransformedShapeToFormattedString(
    std::vector<std::string>& lines) const;

  CsgInternalNodeOperator internal_operator_;
};

}

#endif
