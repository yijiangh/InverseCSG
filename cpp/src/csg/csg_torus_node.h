#ifndef _CSG_CSG_TORUS_NODE_H_
#define _CSG_CSG_TORUS_NODE_H_

#include "csg/csg_node.h"

namespace csg {

class CsgTorusNode : public CsgNode {
public:
  CsgTorusNode(const Eigen::Matrix4d& transform, const double major_radius,
    const double minor_radius, const int rotate_resolution = 12,
    const int circle_resolution = 12);

  const double major_radius() const;
  const double minor_radius() const;
  const int rotate_resolution() const;
  const int circle_resolution() const;

private:
  const bool IsInsideUntransformedShape(const Eigen::Vector3d& point) const;
  void WriteUntransformedShapeToFormattedString(
    std::vector<std::string>& lines) const;

  double major_radius_;
  double minor_radius_;
  int rotate_resolution_;
  int circle_resolution_;
};

}

#endif
