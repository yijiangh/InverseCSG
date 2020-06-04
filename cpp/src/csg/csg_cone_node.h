#ifndef _CSG_CSG_CONE_NODE_H_
#define _CSG_CSG_CONE_NODE_H_

#include "csg/csg_node.h"

namespace csg {

class CsgConeNode : public CsgNode {
public:
  CsgConeNode(const Eigen::Matrix4d& transform, const double height,
    const double top_radius, const double bottom_radius,
    const int resolution = 360);

  const double height() const;
  const double top_radius() const;
  const double bottom_radius() const;
  const int resolution() const;

private:
  const bool IsInsideUntransformedShape(const Eigen::Vector3d& point) const;
  void WriteUntransformedShapeToFormattedString(
    std::vector<std::string>& lines) const;

  double height_;
  double top_radius_;
  double bottom_radius_;
  int resolution_;
};

}

#endif