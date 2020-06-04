#include "command/command.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include "common/file_helper.h"
#include "common/math_helper.h"
#include "csg/csg_node.h"
#include "csg/csg_internal_node.h"

namespace command {

static void CheckTraverseTreeCommandFileName(const std::string& scad_file) {
  if (!common::HasExtension(scad_file, ".scad")) {
    std::ostringstream ss;
    ss << "command::CheckTraverseTreeCommandFileName: wrong scad file"
      << scad_file;
    common::PrintError(ss.str());
  }
}

static void TraverseCsgTree(const std::shared_ptr<csg::CsgNode> csg,
  const std::string& folder, std::string& command_so_far,
  int& idx, std::vector<Eigen::Matrix4d>& transform_stack) {
  // Get the current transform.
  Eigen::Matrix4d current_transform = Eigen::Matrix4d::Identity();
  for (const auto& T : transform_stack) {
    current_transform *= T;
  }
  // Convert it to rpy and translation.
  Eigen::Vector3d rpy, t;
  common::TransformToRotationAndTranslation(current_transform, rpy, t);
  std::ostringstream ss;
  const double roll = common::RadianToDegree(rpy.x());
  const double pitch = common::RadianToDegree(rpy.y());
  const double yaw = common::RadianToDegree(rpy.z());
  ss << "translate([" << t.x() << ", " << t.y() << ", " << t.z() << "])"
    << std::endl
    << "rotate([" << roll << ", " << pitch << ", " << yaw << "])" << std::endl
    << csg->WriteToString() << std::endl;
  if (csg->IsLeaf()) {
    command_so_far = "union() {\n" + command_so_far + ss.str() + "}\n";
  } else {
    // Internal node.
    const auto internal = std::dynamic_pointer_cast<csg::CsgInternalNode>(csg);
    // First, we visit all children.
    const std::string old_command = command_so_far;
    transform_stack.push_back(internal->transform());
    const int old_stack_size = static_cast<int>(transform_stack.size());
    csg::csg_node_list kids = internal->children();
    // Reorder if it is an intersection.
    if (internal->internal_operator() ==
      csg::CsgInternalNodeOperator::kIntersection) {
      csg::csg_node_list subtrees, leaves;
      for (const auto& kid : kids) {
        if (kid->IsLeaf()) leaves.push_back(kid);
        else subtrees.push_back(kid);
      }
      kids = subtrees;
      kids.insert(kids.end(), leaves.begin(), leaves.end());
    }
    for (const auto& kid : kids) {
      TraverseCsgTree(kid, folder, command_so_far, idx, transform_stack);
    }
    // Remove the last element in the stack.
    const int new_stack_size = static_cast<int>(transform_stack.size());
    if (new_stack_size != old_stack_size) {
      common::PrintError("command::TraverseCsgTree: imbalance stack.");
    }
    transform_stack.pop_back();
    // Now we render itself.
    command_so_far = "union() {\n" + old_command + ss.str() + "}\n";
  }
  const std::string idx_str = std::to_string(idx);
  const int len = static_cast<int>(idx_str.size());
  // Assume we have no more than 9999 nodes.
  const std::string file_name = common::AppendFileToPath(folder,
    std::string(4 - len, '0') + idx_str + ".scad");
  ++idx;
  std::ofstream fout(file_name);
  fout << command_so_far;
}

void TraverseTreeCommand(const bool help, const std::string& scad_file,
  const std::string& output_folder, const bool verbose) {
  // Print help information.
  if (help) {
    std::cout
      << "traverse-tree       Post-order traversal in a SCAD file." << std::endl
      << "  -h                Print help information." << std::endl
      << "  -i <SCAD file>    Input scad file." << std::endl
      << "  -o <Folder>       An output folder to hold all results." << std::endl
      << "  -v                Verbose mode." << std::endl << std::endl
      << "Given a scad file, traverse in post order and print scad files."
      << std::endl << std::endl;
    return;
  }

  // Sanity check.
  CheckTraverseTreeCommandFileName(scad_file);
  // Read shape.
  std::shared_ptr<csg::CsgNode> root(nullptr);
  common::ReadScadFile(scad_file, root);

  int idx = 0;
  std::string command = "";
  std::vector<Eigen::Matrix4d> transform_stack(0);
  TraverseCsgTree(root, output_folder, command, idx, transform_stack);
}

}
