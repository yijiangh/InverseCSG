#include "csg/scad_file_parser.h"
#include <iostream>
#include <fstream>
#include "common/file_helper.h"
#include "common/math_helper.h"

namespace csg {

ScadFileParser::ScadFileParser(const std::string& file_name)
  : root_(nullptr), context_(""), next_pos_(0),
  stop_chars_("{}(),;[]="), white_spaces_(" \t\r\n") {
  if (!common::HasExtension(file_name, ".scad")) {
    std::cerr << common::RedHead()
      << "csg::ScadFileParser::ScadFileParser: wrong file extension: "
      << file_name << common::RedTail() << std::endl;
    exit(-1);
  }
  // Read the whole file into a string.
  std::ifstream scad_file(file_name);
  context_ = std::string{ std::istreambuf_iterator<char>(scad_file),
    std::istreambuf_iterator<char>() };
  // Parse.
  root_ = ParseCsgNode();
}

const std::shared_ptr<CsgNode> ScadFileParser::root() const {
  return root_;
}

const bool ScadFileParser::IsStopChar(const char ch) const {
  return stop_chars_.find(ch) != std::string::npos;
}

const bool ScadFileParser::IsWhiteSpace(const char ch) const {
  return white_spaces_.find(ch) != std::string::npos;
}

const std::string ScadFileParser::GetNextToken() {
  return GetNextTokenWithPos(next_pos_);
}

const std::string ScadFileParser::PeekNextToken() const {
  int dummy_pos = next_pos_;
  return GetNextTokenWithPos(dummy_pos);
}

const std::string ScadFileParser::GetNextTokenWithPos(int& next_pos) const {
  const int len = static_cast<int>(context_.size());
  std::string token = "";
  // Get the next token.
  while (next_pos < len) {
    const char next_ch = context_[next_pos];
    if (IsStopChar(next_ch)) {
      if (token.empty()) {
        token = std::string(1, next_ch);
        ++next_pos;
      }
      break;
    } else if (IsWhiteSpace(next_ch)) {
      if (!token.empty()) break;
    } else {
      token += std::string(1, next_ch);
      // Skip comments.
      if (token.size() >= 2u && token.substr(0, 2) == "//") {
        token = "";
        // Keep going until we reach the end of line or file.
        while (next_pos < len && context_[next_pos] != '\r'
          && context_[next_pos] != '\n') ++next_pos;
        --next_pos;
      }
    }
    ++next_pos;
  }
  return token;
}

void ScadFileParser::AssertToken(const std::string& token,
  const std::string& target) const {
  if (token != target) {
    std::cerr << common::RedHead()
      << "csg::ScadFileParser::AssertToken: " << token << " != "
      << target << common::RedTail() << std::endl;
    exit(-1);
  }
}

void ScadFileParser::AssertToken(const std::string& token,
  const std::vector<std::string>& targets) const {
  for (const auto& target : targets) {
    if (token == target) return;
  }
  std::cerr << common::RedHead()
    << "csg::ScadFileParser::AssertToken: " << token << " not in { ";
  for (const auto& target : targets) std::cerr << target << " ";
  std::cerr << "}" << common::RedTail() << std::endl;
  exit(-1);
}

void ScadFileParser::GetLeftRoundBracket() {
  AssertToken(GetNextToken(), "(");
}

void ScadFileParser::GetRightRoundBracket() {
  AssertToken(GetNextToken(), ")");
}

void ScadFileParser::GetLeftSquareBracket() {
  AssertToken(GetNextToken(), "[");
}

void ScadFileParser::GetRightSquareBracket() {
  AssertToken(GetNextToken(), "]");
}

void ScadFileParser::GetLeftCurlyBracket() {
  AssertToken(GetNextToken(), "{");
}

void ScadFileParser::GetRightCurlyBracket() {
  AssertToken(GetNextToken(), "}");
}

void ScadFileParser::GetComma() {
  AssertToken(GetNextToken(), ",");
}

void ScadFileParser::GetSemiColon() {
  AssertToken(GetNextToken(), ";");
}

void ScadFileParser::GetEqualitySign() {
  AssertToken(GetNextToken(), "=");
}

const int ScadFileParser::GetInt() {
  std::size_t idx = 0;
  const std::string token = GetNextToken();
  const int number = std::stoi(token, &idx);
  if (idx != token.size()) {
    std::cerr << common::RedHead()
      << "csg::ScadFileParser::GetInt: " << token << common::RedTail()
      << std::endl;
    exit(-1);
  }
  return number;
}

const double ScadFileParser::GetDouble() {
  std::size_t idx = 0;
  const std::string token = GetNextToken();
  const double number = std::stod(token, &idx);
  if (idx != token.size()) {
    std::cerr << common::RedHead()
      << "csg::ScadFileParser::GetDouble: " << token << common::RedTail()
      << std::endl;
    exit(-1);
  }
  return number;
}

const Eigen::Vector3d ScadFileParser::GetVector3d() {
  // [1, 2, 3]
  GetLeftSquareBracket();
  Eigen::Vector3d v;
  v.x() = GetDouble();
  GetComma();
  v.y() = GetDouble();
  GetComma();
  v.z() = GetDouble();
  GetRightSquareBracket();
  return v;
}

const Eigen::Vector4d ScadFileParser::GetVector4d() {
  // [1, 2, 3, 4]
  GetLeftSquareBracket();
  Eigen::Vector4d v;
  v.x() = GetDouble();
  GetComma();
  v.y() = GetDouble();
  GetComma();
  v.z() = GetDouble();
  GetComma();
  v.w() = GetDouble();
  GetRightSquareBracket();
  return v;
}

const Eigen::Matrix4d ScadFileParser::ParseTranslate() {
  // translate([1, 2, 3])
  AssertToken(GetNextToken(), "translate");
  GetLeftRoundBracket();
  Eigen::Vector3d v = GetVector3d();
  GetRightRoundBracket();
  return common::Translation(v);
}

const Eigen::Matrix4d ScadFileParser::ParseRotate() {
  // rotate([1, 2, 3])
  AssertToken(GetNextToken(), "rotate");
  GetLeftRoundBracket();
  Eigen::Vector3d v = GetVector3d();
  GetRightRoundBracket();
  const double roll = common::DegreeToRadian(v.x()),
    pitch = common::DegreeToRadian(v.y()),
    yaw = common::DegreeToRadian(v.z());
  return common::Rotation(Eigen::Vector3d(roll, pitch, yaw));
}

const Eigen::Matrix4d ScadFileParser::ParseMultiMatrix() {
  // multmatrix(m = [[1, -0, 0, 0],
  //                 [0, 0, 1, -0.025],
  //                 [-0, -1, 0, 0],
  //                 [0, 0, 0, 1]])
  AssertToken(GetNextToken(), "multmatrix");
  GetLeftRoundBracket();
  AssertToken(GetNextToken(), "m");
  GetEqualitySign();
  GetLeftSquareBracket();
  Eigen::Matrix4d m;
  for (int i = 0; i < 4; ++i) {
    m.row(i) = GetVector4d();
    if (i == 3) GetRightSquareBracket();
    else GetComma();
  }
  GetRightRoundBracket();
  return m;
}

const std::shared_ptr<CsgSphereNode> ScadFileParser::ParseSphere(
  const Eigen::Matrix4d& transform) {
  // sphere(r = 1, $fn = 20);
  AssertToken(GetNextToken(), "sphere");
  GetLeftRoundBracket();
  AssertToken(GetNextToken(), "r");
  GetEqualitySign();
  const double radius = GetDouble();
  GetComma();
  AssertToken(GetNextToken(), "$fn");
  GetEqualitySign();
  const int resolution = GetInt();
  GetRightRoundBracket();
  GetSemiColon();
  return std::make_shared<CsgSphereNode>(transform, radius, resolution);
}

const std::shared_ptr<CsgCubeNode> ScadFileParser::ParseCube(
  const Eigen::Matrix4d& transform) {
  // cube(size = [0.9, 1.2, 0.8], center = false);
  AssertToken(GetNextToken(), "cube");
  GetLeftRoundBracket();
  AssertToken(GetNextToken(), "size");
  GetEqualitySign();
  const Eigen::Vector3d size = GetVector3d();
  GetComma();
  AssertToken(GetNextToken(), "center");
  GetEqualitySign();
  const std::string is_center = GetNextToken();
  AssertToken(is_center, std::vector<std::string>{ "true", "false" });
  const Eigen::Matrix4d final_transform = transform * (
    is_center == "true" ? Eigen::Matrix4d::Identity() :
    common::Translation(size * 0.5));
  GetRightRoundBracket();
  GetSemiColon();
  return std::make_shared<CsgCubeNode>(final_transform, size);
}

const std::shared_ptr<CsgNode> ScadFileParser::ParseCylinderOrCone(
  const Eigen::Matrix4d& transform) {
  // cylinder(h = 0.4, r1 = a, r2 = b, center = true|false, $fn = 40);
  AssertToken(GetNextToken(), "cylinder");
  GetLeftRoundBracket();
  // Height.
  AssertToken(GetNextToken(), "h");
  GetEqualitySign();
  const double height = GetDouble();
  GetComma();
  // Radius.
  AssertToken(GetNextToken(), "r1");
  GetEqualitySign();
  const double r1 = GetDouble();
  GetComma();
  AssertToken(GetNextToken(), "r2");
  GetEqualitySign();
  const double r2 = GetDouble();
  GetComma();
  // Center.
  AssertToken(GetNextToken(), "center");
  GetEqualitySign();
  const std::string is_center = GetNextToken();
  AssertToken(is_center, std::vector<std::string>{ "true", "false" });
  GetComma();
  const Eigen::Matrix4d final_transform = transform * (
    is_center == "true" ? Eigen::Matrix4d::Identity() :
    common::Translation(Eigen::Vector3d::UnitZ() * height * 0.5));
  // Resolution.
  AssertToken(GetNextToken(), "$fn");
  GetEqualitySign();
  const int resolution = GetInt();
  GetRightRoundBracket();
  GetSemiColon();
  if (r1 == r2) {
    // Cylinder.
    return std::make_shared<CsgCylinderNode>(final_transform, height, r1,
      resolution);
  } else {
    // Cone.
    return std::make_shared<CsgConeNode>(final_transform, height, r2, r1,
      resolution);
  }
}

const std::shared_ptr<CsgTorusNode> ScadFileParser::ParseTorus(
  const Eigen::Matrix4d& transform) {
  // rotate_extrude($fn = 20)
  // translate([10, 0, 0])
  // circle(r = 3, $fn = 20);
  AssertToken(GetNextToken(), "rotate_extrude");
  GetLeftRoundBracket();
  // Rotate resolution.
  AssertToken(GetNextToken(), "$fn");
  GetEqualitySign();
  const int rotate_resolution = GetInt();
  GetRightRoundBracket();
  // Major radius.
  AssertToken(GetNextToken(), "translate");
  GetLeftRoundBracket();
  const Eigen::Vector3d t = GetVector3d();
  const double major_radius = t.x();
  if (t.y() != 0 || t.z() != 0) {
    common::PrintError("csg::ScadFileParser::ParseTorus: invalid major radii.");
  }
  GetRightRoundBracket();
  // Minor radius.
  AssertToken(GetNextToken(), "circle");
  GetLeftRoundBracket();
  AssertToken(GetNextToken(), "r");
  GetEqualitySign();
  const double minor_radius = GetDouble();
  GetComma();
  AssertToken(GetNextToken(), "$fn");
  GetEqualitySign();
  const int circle_resolution = GetInt();
  GetRightRoundBracket();
  GetSemiColon();
  // Torus.
  return std::make_shared<CsgTorusNode>(transform, major_radius,
    minor_radius, rotate_resolution, circle_resolution);
}

const std::shared_ptr<CsgInternalNode> ScadFileParser::ParseUnion(
  const Eigen::Matrix4d& transform) {
  // union() { ... }
  AssertToken(GetNextToken(), "union");
  GetLeftRoundBracket();
  GetRightRoundBracket();
  GetLeftCurlyBracket();
  std::vector<std::shared_ptr<CsgNode>> children(0);
  while (PeekNextToken() != "}") {
    children.push_back(ParseCsgNode());
  }
  GetRightCurlyBracket();
  return std::make_shared<CsgInternalNode>(children, transform,
    CsgInternalNodeOperator::kUnion);
}

const std::shared_ptr<CsgInternalNode> ScadFileParser::ParseIntersection(
  const Eigen::Matrix4d& transform) {
  // intersection() { ... }
  AssertToken(GetNextToken(), "intersection");
  GetLeftRoundBracket();
  GetRightRoundBracket();
  GetLeftCurlyBracket();
  std::vector<std::shared_ptr<CsgNode>> children(0);
  while (PeekNextToken() != "}") {
    children.push_back(ParseCsgNode());
  }
  GetRightCurlyBracket();
  return std::make_shared<CsgInternalNode>(children, transform,
    CsgInternalNodeOperator::kIntersection);
}

const std::shared_ptr<CsgInternalNode> ScadFileParser::ParseSubtraction(
  const Eigen::Matrix4d& transform) {
  // difference() { ... }
  AssertToken(GetNextToken(), "difference");
  GetLeftRoundBracket();
  GetRightRoundBracket();
  GetLeftCurlyBracket();
  std::vector<std::shared_ptr<CsgNode>> children(0);
  while (PeekNextToken() != "}") {
    children.push_back(ParseCsgNode());
  }
  GetRightCurlyBracket();
  return std::make_shared<CsgInternalNode>(children, transform,
    CsgInternalNodeOperator::kSubtraction);
}

const std::shared_ptr<CsgNode> ScadFileParser::ParseCsgNode() {
  std::string token = PeekNextToken();
  Eigen::Matrix4d transform = Eigen::Matrix4d::Identity();
  // Prerequisites: transform.
  while (true) {
    if (token == "rotate") transform = transform * ParseRotate();
    else if (token == "translate") transform = transform * ParseTranslate();
    else if (token == "multmatrix") transform = transform * ParseMultiMatrix();
    else break;
    token = PeekNextToken();
  }
  // Case 1: pure leaf node.
  if (token == "sphere") return ParseSphere(transform);
  else if (token == "cube") return ParseCube(transform);
  else if (token == "cylinder") return ParseCylinderOrCone(transform);
  else if (token == "rotate_extrude") return ParseTorus(transform);
  // Case 2 : internal nodes.
  else if (token == "union") return ParseUnion(transform);
  else if (token == "intersection") return ParseIntersection(transform);
  else if (token == "difference") return ParseSubtraction(transform);
  // Unhandled cases.
  else {
    std::cerr << common::RedHead()
      << "csg::ScadFileParser::ParseCsgNode: unhandled node: " << token
      << common::RedTail() << std::endl;
    exit(-1);
  }
}

}
