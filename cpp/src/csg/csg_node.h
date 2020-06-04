#ifndef _CSG_CSG_NODE_H_
#define _CSG_CSG_NODE_H_

#include <memory>
#include <string>
#include <vector>
#include "Eigen/Dense"

namespace csg {

class CsgNode;
typedef std::vector<std::shared_ptr<CsgNode>> csg_node_list;

class CsgNode {
public:
  CsgNode(const std::string& type_name,
    const csg_node_list& children, const Eigen::Matrix4d& transform);
  virtual ~CsgNode();

  const bool IsLeaf() const;
  const int NumOfChildren() const;
  const std::string type_name() const;
  const csg_node_list& children() const;
  void set_children(const int idx, const std::shared_ptr<csg::CsgNode>& node);
  const Eigen::Matrix4d transform() const;
  const Eigen::Matrix4d inv_transform() const;

  const bool IsInside(const Eigen::Vector3d& point) const;
  const std::string WriteToString() const;
  void WriteToFormattedString(std::vector<std::string>& lines) const;

  // Leaf node has depth = 1.
  const int GetDepth() const;
  // Get the number of nodes in the subtree rooted at itself.
  const int GetSubtreeSize() const;

protected:
  virtual const bool IsInsideUntransformedShape(const Eigen::Vector3d& point)
    const = 0;
  virtual void WriteUntransformedShapeToFormattedString(
    std::vector<std::string>& lines) const = 0;

private:
  std::string type_name_;
  csg_node_list children_;
  // transform_ is applied to the shape in this way: let P be the set of all
  // points inside the shape without transform, then the new shape is defined
  // as {transform_ * p|p\in P}.
  // To check if a point p is inside, consider p' = inv_transform_ * p, then
  // check if p' is inside the original shape.
  Eigen::Matrix4d transform_, inv_transform_;
};

}

#endif
