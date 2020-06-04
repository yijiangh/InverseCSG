#ifndef _CSG_CSG_SPHERE_NODE_H_
#define _CSG_CSG_SPHERE_NODE_H_

#include "csg/csg_node.h"

namespace csg {

class CsgSphereNode : public CsgNode {
public:
  CsgSphereNode(const Eigen::Matrix4d& transform, const double radius,
    const int resolution = 360);

  const double radius() const;
  const int resolution() const;

private:
  const bool IsInsideUntransformedShape(const Eigen::Vector3d& point) const;
  void WriteUntransformedShapeToFormattedString(
    std::vector<std::string>& lines) const;

  double radius_;
  int resolution_;
};

}

#endif
