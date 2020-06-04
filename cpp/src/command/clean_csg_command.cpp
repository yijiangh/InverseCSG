#include "command/command.h"
#include <iostream>
#include <memory>
#include "common/file_helper.h"
#include "common/math_helper.h"
#include "csg/csg_node.h"
#include "csg/csg_internal_node.h"
#include "csg/csg_cube_node.h"
#include "csg/csg_sphere_node.h"
#include "csg/csg_cylinder_node.h"

namespace command {

static void CheckCleanCsgCommandFileName(const std::string& input_scad_file,
  const std::string& output_scad_file) {
  if (!common::HasExtension(input_scad_file, ".scad")) {
    std::cerr << common::RedHead() << "command::CheckCleanCsgCommandFileName: "
      << "wrong input scad file: " << input_scad_file << common::RedTail()
      << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(output_scad_file, ".scad")) {
    std::cerr << common::RedHead() << "command::CheckCleanCsgCommandFileName: "
      << "wrong output scad file: " << output_scad_file << common::RedTail()
      << std::endl;
    exit(-1);
  }
}

// Returns the number of epsilons needed at node. Guaranteed to be nonnegative.
static const int RunBottomUpPass(const std::shared_ptr<csg::CsgNode>& node) {
  if (node->IsLeaf()) return 0;
  // Internal node.
  const auto internal = std::dynamic_pointer_cast<csg::CsgInternalNode>(node);
  std::vector<int> children_vals;
  for (const auto& child : internal->children()) {
    children_vals.push_back(RunBottomUpPass(child));
  }
  if (children_vals.empty()) {
    common::PrintError("command::RunBottomUpPass: empty children.");
  }
  switch (internal->internal_operator()) {
    case csg::CsgInternalNodeOperator::kUnion: {
      // Pick the maximum.
      int max_num = -1;
      for (const int num : children_vals) {
        if (num > max_num) max_num = num;
      }
      return max_num;
    }
    case csg::CsgInternalNodeOperator::kIntersection: {
      // If all zero, return 1. Otherwise return the max.
      int max_num = -1;
      for (const int num : children_vals) {
        if (num > max_num) max_num = num;
      }
      return max_num ? max_num : 1;
    }
    case csg::CsgInternalNodeOperator::kSubtraction: {
      const int right = children_vals.at(1);
      int left = children_vals.at(0);
      if (left <= right) left = right + 1;
      return left;
    }
    default: {
      common::PrintError("command::RunBottomUpPass: unsupport operator.");
    }
  }
  // Dummy return.
  return 0;
}

// The second, top down pass which does the actual work.
static const std::shared_ptr<csg::CsgNode> RunTopDownPass(
  const std::shared_ptr<csg::CsgNode>& node, const double eps,
  const int num_of_eps) {
  if (node->IsLeaf()) {
    // Change the leaf node.
    if (node->type_name() == "cube") {
      const auto cube = std::dynamic_pointer_cast<csg::CsgCubeNode>(node);
      const Eigen::Vector3d new_size = cube->size().array() - eps * num_of_eps;
      return std::make_shared<csg::CsgCubeNode>(cube->transform(), new_size);
    } else if (node->type_name() == "sphere") {
      const auto sphere = std::dynamic_pointer_cast<csg::CsgSphereNode>(node);
      // TODO: remove this magic number.
      int res = sphere->resolution();
      if (sphere->radius() / res > 0.5) res = sphere->radius() / 0.5;
      return std::make_shared<csg::CsgSphereNode>(sphere->transform(),
        sphere->radius() - eps * num_of_eps, res);
    } else if (node->type_name() == "cylinder") {
      const auto cyl = std::dynamic_pointer_cast<csg::CsgCylinderNode>(node);
      // Determine the right number of resolution.
      // TODO: remove this magic number.
      int res = cyl->resolution();
      if (cyl->radius() / res > 0.5) res = cyl->radius() / 0.5;
      return std::make_shared<csg::CsgCylinderNode>(cyl->transform(),
        cyl->height() - eps * num_of_eps, cyl->radius(), res);
    } else {
      common::PrintError("command::PerturbNode: unsupported leaf node type.");
    }
  } else {
    // Internal node.
    const auto internal_node =
      std::dynamic_pointer_cast<csg::CsgInternalNode>(node);
    switch (internal_node->internal_operator()) {
      case csg::CsgInternalNodeOperator::kUnion: {
        csg::csg_node_list children;
        for (const auto& child : internal_node->children()) {
          children.push_back(RunTopDownPass(child, eps, num_of_eps));
        }
        return std::make_shared<csg::CsgInternalNode>(children,
          internal_node->transform(), internal_node->internal_operator());
      }
      case csg::CsgInternalNodeOperator::kIntersection: {
        csg::csg_node_list children;
        for (const auto& child : internal_node->children()) {
          children.push_back(RunTopDownPass(child, eps, num_of_eps));
        }
        return std::make_shared<csg::CsgInternalNode>(children,
          internal_node->transform(), internal_node->internal_operator());
      }
      case csg::CsgInternalNodeOperator::kSubtraction: {
        csg::csg_node_list children;
        children.push_back(RunTopDownPass(internal_node->children()[0], eps,
          num_of_eps));
        children.push_back(RunTopDownPass(internal_node->children()[1], eps,
          num_of_eps - 1));
        return std::make_shared<csg::CsgInternalNode>(children,
          internal_node->transform(), internal_node->internal_operator());
      }
      default: {
        common::PrintError("command::PerturbNode: unsupported operator.");
      }
    }
  }
  // Should not reach here.
  return nullptr;
}

void CleanCsgCommand(const double epsilon, const bool help,
  const std::string& input_scad_file, const std::string& output_scad_file,
  const bool verbose) {
  // Print help information.
  if (help) {
    std::cout
      << "clean-csg           Cleanup csg results by perturbing dimensions to "
      << "remove degenerated faces." << std::endl
      << "  -e <double>       Epsilon value to be added/removed." << std::endl
      << "  -h                Print help information." << std::endl
      << "  -i <SCAD file>    Input OpenSCAD file." << std::endl
      << "  -o <SCAD file>    Output OpenSCAD file." << std::endl
      << "  -v                Verbose mode." << std::endl << std::endl
      << "Perturb dimensions to avoid degenerated faces." << std::endl
      << "This is a two-pass algorithm. In the first, bottom-up" << std::endl
      << "pass, we compute how much the geometry represented by" << std::endl
      << "each node needs to shrink. In the second, top-down pass," << std::endl
      << "we propagate the epsilon value from the root to each" << std::endl
      << "leaf and actually shrink the geometry." << std::endl << std::endl;
    return;
  }

  // Sanity check.
  CheckCleanCsgCommandFileName(input_scad_file, output_scad_file);
  if (epsilon <= 0.0) {
    std::cerr << common::RedHead() << "command::CsgFlagCommand: please give a "
      << "positive epsilon (current value is " << epsilon << ")."
      << common::RedTail() << std::endl;
    exit(-1);
  }

  // Read shape.
  std::shared_ptr<csg::CsgNode> root(nullptr);
  common::ReadScadFile(input_scad_file, root);

  // Compute how much we need to shrink.
  const int num_of_eps = RunBottomUpPass(root);
  if (verbose) {
    std::cout << "command::CleanCsgCommand: shrink the whole shape by "
      << num_of_eps << " epsilons." << std::endl;
  }
  // Write solution.
  const auto new_root = RunTopDownPass(root, epsilon, num_of_eps);
  common::WriteScadFile(new_root, output_scad_file);
}

}
