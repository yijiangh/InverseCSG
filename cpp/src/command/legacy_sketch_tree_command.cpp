#include "command/command.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include "common/file_helper.h"
#include "common/math_helper.h"
#include "csg/csg_node.h"
#include "csg/csg_internal_node.h"
#include "csg/csg_cube_node.h"
#include "csg/csg_sphere_node.h"
#include "csg/csg_cylinder_node.h"
#include "csg/scad_file_parser.h"

namespace command {

static void CheckLegacySketchTreeCommandFileName(
  const std::string& input_scad_file, const std::string& output_txt_file) {
  if (!common::HasExtension(input_scad_file, ".scad")) {
    std::ostringstream ss;
    ss << "command::CheckLegacySketchTreeCommandFileName: wrong scad file: "
      << input_scad_file;
    common::PrintError(ss.str());
  }
  if (!common::HasExtension(output_txt_file, ".txt")) {
    std::ostringstream ss;
    ss << "command::CheckLegacySketchTreeCommandFileName: wrong txt file: "
      << output_txt_file;
    common::PrintError(ss.str());
  }
}

static const std::string WriteCsgNodeToOldSketchString(
  const std::shared_ptr<csg::CsgNode>& node) {
  if (node->IsLeaf()) {
    Eigen::Vector3d rpy, t;
    common::TransformToRotationAndTranslation(node->transform(), rpy, t);
    const Eigen::Matrix3d R = common::RollPitchYawToRotation(rpy);
    // R * x + t = R * (x + R' * t) = R * (x + t2).
    const Eigen::Vector3d t2 = R.transpose() * t;
    if (node->type_name() == "sphere") {
      const auto sphere = std::dynamic_pointer_cast<csg::CsgSphereNode>(node);
      // Sphere(Vector(x, y, z), r).
      const Eigen::Vector3d center = t; 
      const double radius = sphere->radius(); 
      std::ostringstream ss;
      ss << "Sphere(Vector(" << center.x() << ", " << center.y() << ", "
        << center.z() << "), " << radius * radius << ")";
      return ss.str();
    } else if (node->type_name() == "cylinder") {
      const auto cyl = std::dynamic_pointer_cast<csg::CsgCylinderNode>(node);
      // Cylinder(Vector(r, p, y), Vector(x, y, z), Vector(dx, dy, dz), r).
      const double height = cyl->height();
      const double radius = cyl->radius();
      const Eigen::Vector3d p = Eigen::Vector3d::UnitZ() * (-height * 0.5) + t2;
      std::ostringstream ss;
      ss << "Cylinder(Vector(" << rpy.x() << ", " << rpy.y() << ", " << rpy.z()
        << "), Vector(" << p.x() << ", " << p.y() << ", " << p.z() << "), "
        << "Vector(0, 0, " << height << "), " << radius << ")";
      return ss.str();
    } else if (node->type_name() == "cube") {
      const auto cube = std::dynamic_pointer_cast<csg::CsgCubeNode>(node);
      // Cuboid(Vector(r, p, y), Vector(x, y, z), Vector(sx, sy, sz)).
      const Eigen::Vector3d size = cube->size();
      const Eigen::Vector3d p = -size * 0.5 + t2;
      std::ostringstream ss;
      ss << "Cuboid(Vector(" << rpy.x() << ", " << rpy.y() << ", " << rpy.z()
        << "), Vector(" << p.x() << ", " << p.y() << ", " << p.z() << "), "
        << "Vector(" << size.x() << ", " << size.y() << ", " << size.z()
        << "))";
      return ss.str();
    } else {
      common::PrintError("command::WriteCsgNodeToOldSketchString: unsupported "
        "leaf node type.");
    } 
    // Dummy return.
    return "";
  }
  // Now we know it is an internal node.
  const auto internal = std::dynamic_pointer_cast<csg::CsgInternalNode>(node);
  std::string str = "";
  switch (internal->internal_operator()) {
    case csg::CsgInternalNodeOperator::kUnion: {
      str += "Union(";
      break;
    }
    case csg::CsgInternalNodeOperator::kIntersection: {
      str += "Intersection(";
      break;
    }
    case csg::CsgInternalNodeOperator::kSubtraction: {
      str += "Subtract(";
      break;
    }
    default: {
      common::PrintError("command::WriteCsgNodeToOldSketchString: unsupported "
        "internal node type.");
    }
  }
  const int num_child = internal->NumOfChildren();
  for (int i = 0; i < num_child; ++i) {
    str += WriteCsgNodeToOldSketchString(internal->children()[i]);
    if (i < num_child - 1) str += ", ";
  } 
  str += ")";
  return str;
}

void LegacySketchTreeCommand(const bool help,
  const std::string& input_scad_file, const std::string& output_txt_file,
  const bool verbose) {
  // Print help information.
  if (help) {
    std::cout
      << "legacy-sketch-tree  Generate tree in the old format used by sketch."
      << std::endl
      << "  -h                Print help information." << std::endl
      << "  -i <SCAD file>    Input scad file." << std::endl
      << "  -o <TXT file>     Output text file." << std::endl
      << "  -v                Verbose mode." << std::endl << std::endl
      << "Convert the scad result into the sketch tree results" << std::endl
      << "used before. This function will soon be deprecated."
      << std::endl << std::endl;
    return;
  }

  // Check inputs.
  CheckLegacySketchTreeCommandFileName(input_scad_file, output_txt_file);

  // Read CSG tree.
  std::shared_ptr<csg::CsgNode> root(nullptr);
  common::ReadScadFile(input_scad_file, root);

  std::ofstream fout(output_txt_file);
  fout << WriteCsgNodeToOldSketchString(root) << std::endl;
}

}
