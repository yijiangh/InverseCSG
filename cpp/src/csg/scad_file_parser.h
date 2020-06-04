#ifndef _CSG_SCAD_FILE_PARSER_H_
#define _CSG_SCAD_FILE_PARSER_H_

#include <memory>
#include <string>
#include <vector>
#include "csg/csg_node.h"
#include "csg/csg_internal_node.h"
#include "csg/csg_sphere_node.h"
#include "csg/csg_cube_node.h"
#include "csg/csg_cylinder_node.h"
#include "csg/csg_torus_node.h"
#include "csg/csg_cone_node.h"

namespace csg {

class ScadFileParser {
public:
  explicit ScadFileParser(const std::string& file_name);

  const std::shared_ptr<CsgNode> root() const;

private:
  const bool IsStopChar(const char ch) const;
  const bool IsWhiteSpace(const char ch) const;
  const std::string GetNextToken();
  const std::string PeekNextToken() const;
  const std::string GetNextTokenWithPos(int& next_pos) const;
  void AssertToken(const std::string& token, const std::string& target) const;
  void AssertToken(const std::string& token,
    const std::vector<std::string>& targets) const;
  void GetLeftRoundBracket();
  void GetRightRoundBracket();
  void GetLeftSquareBracket();
  void GetRightSquareBracket();
  void GetLeftCurlyBracket();
  void GetRightCurlyBracket();
  void GetComma();
  void GetSemiColon();
  void GetEqualitySign();
  const int GetInt();
  const double GetDouble();
  const Eigen::Vector3d GetVector3d();
  const Eigen::Vector4d GetVector4d();

  // Parsers.
  const Eigen::Matrix4d ParseTranslate();
  const Eigen::Matrix4d ParseRotate();
  const Eigen::Matrix4d ParseMultiMatrix();
  const std::shared_ptr<CsgSphereNode> ParseSphere(
    const Eigen::Matrix4d& transform);
  const std::shared_ptr<CsgCubeNode> ParseCube(
    const Eigen::Matrix4d& transform);
  const std::shared_ptr<CsgNode> ParseCylinderOrCone(
    const Eigen::Matrix4d& transform);
  const std::shared_ptr<CsgTorusNode> ParseTorus(
    const Eigen::Matrix4d& transform);
  const std::shared_ptr<CsgInternalNode> ParseUnion(
    const Eigen::Matrix4d& transform);
  const std::shared_ptr<CsgInternalNode> ParseIntersection(
    const Eigen::Matrix4d& transform);
  const std::shared_ptr<CsgInternalNode> ParseSubtraction(
    const Eigen::Matrix4d& transform);

  const std::shared_ptr<CsgNode> ParseCsgNode();

  std::shared_ptr<CsgNode> root_;
  std::string context_;
  int next_pos_;

  std::string stop_chars_, white_spaces_;
};

}

#endif
