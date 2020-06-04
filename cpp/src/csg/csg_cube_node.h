#ifndef _CSG_CSG_CUBE_NODE_H_
#define _CSG_CSG_CUBE_NODE_H_

#include "csg/csg_node.h"

namespace csg {

class CsgCubeNode : public CsgNode {
public:
  CsgCubeNode(const Eigen::Matrix4d& transform, const Eigen::Vector3d& size);

  const Eigen::Vector3d size() const;

private:
  const bool IsInsideUntransformedShape(const Eigen::Vector3d& point) const;
  void WriteUntransformedShapeToFormattedString(
    std::vector<std::string>& lines) const;

  Eigen::Vector3d size_;
};

}

#endif
