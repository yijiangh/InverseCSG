#ifndef _CSG_CSG_CYLINDER_NODE_H_
#define _CSG_CSG_CYLINDER_NODE_H_

#include "csg/csg_node.h"

namespace csg {

class CsgCylinderNode : public CsgNode {
public:
  CsgCylinderNode(const Eigen::Matrix4d& transform, const double height,
    const double radius, const int resolution = 360);

  const double height() const;
  const double radius() const;
  const int resolution() const;

private:
  const bool IsInsideUntransformedShape(const Eigen::Vector3d& point) const;
  void WriteUntransformedShapeToFormattedString(
    std::vector<std::string>& lines) const;

  double height_;
  double radius_;
  int resolution_;
};

}

#endif
