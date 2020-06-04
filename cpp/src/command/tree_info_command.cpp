#include "command/command.h"
#include <iostream>
#include <memory>
#include "common/file_helper.h"
#include "common/math_helper.h"
#include "csg/csg_node.h"
#include "csg/scad_file_parser.h"

namespace command {

static void CheckTreeInfoCommandFileName(const std::string& scad_file) {
  if (!common::HasExtension(scad_file, ".scad")) {
    std::cerr << common::RedHead() << "command::CheckTreeInfoCommandFileName: "
      << "wrong scad file: " << scad_file << common::RedTail() << std::endl;
    exit(-1);
  }
}

void TreeInfoCommand(const bool help, const std::string& scad_file) {
  // Print help information.
  if (help) {
    std::cout
      << "tree-info           Print tree depth and number of nodes." << std::endl
      << "  -h                Print help information." << std::endl
      << "  -i <SCAD file>    Input scad file." << std::endl << std::endl
      << "Given a scad file, print its depth and number of nodes."
      << std::endl << std::endl;
    return;
  }

  // Sanity check.
  CheckTreeInfoCommandFileName(scad_file);
  // Read shape.
  std::shared_ptr<csg::CsgNode> root(nullptr);
  common::ReadScadFile(scad_file, root);
  // Print info.
  std::cout << root->GetDepth() << " " << root->GetSubtreeSize() << std::endl;
}

}
