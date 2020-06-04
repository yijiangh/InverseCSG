#include "command/command.h"
#include <iostream>
#include <memory>
#include "common/file_helper.h"
#include "common/math_helper.h"
#include "csg/csg_node.h"
#include "csg/scad_file_parser.h"

namespace command {

static void CheckCsgFlagCommandFileName(const std::string& input_data_file,
  const std::string& scad_file,
  const std::string& output_negative_data_file,
  const std::string& output_positive_data_file) {
  if (!common::HasExtension(input_data_file, ".data")) {
    std::cerr << common::RedHead() << "command::CheckCsgFlagCommandFileName: "
      << "wrong data file: " << input_data_file << common::RedTail()
      << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(scad_file, ".scad")) {
    std::cerr << common::RedHead() << "command::CheckCsgFlagCommandFileName: "
      << "wrong scad file: " << scad_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(output_negative_data_file, ".data")) {
    std::cerr << common::RedHead() << "command::CheckCsgFlagCommandFileName: "
      << "wrong negative data file: " << output_negative_data_file
      << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(output_positive_data_file, ".data")) {
    std::cerr << common::RedHead() << "command::CheckCsgFlagCommandFileName: "
      << "wrong positive data file: " << output_positive_data_file
      << common::RedTail() << std::endl;
    exit(-1);
  }
}

void CsgFlagCommand(const std::string& input_data_file, const double min_dist,
  const bool help, const std::string& scad_file,
  const std::string& output_negative_data_file,
  const std::string& output_positive_data_file,
  const bool verbose) {
  // Print help information.
  if (help) {
    std::cout
      << "csg-flag            Check if points are inside CSG or not." << std::endl
      << "  -d <DATA file>    Input data file." << std::endl
      << "  -e <double>       Minimum distance to the csg shape." << std::endl
      << "  -h                Print help information." << std::endl
      << "  -i <SCAD file>    Input OpenSCAD file." << std::endl
      << "  -n <DATA file>    Output data file with negative points." << std::endl
      << "  -p <DATA file>    Output data file with positive points." << std::endl
      << "  -v                Verbose mode." << std::endl << std::endl
      << "Given a csg shape, find all the positive and negative" << std::endl
      << "points in the provided point sets. Points are positive" << std::endl
      << "if and only if it is inside the csg." << std::endl << std::endl
      << "If a point is too close to the csg, this command skips" << std::endl
      << "that point. To check if p is too close to the csg, we" << std::endl
      << "check 27 points (p+/-min_dist in 3 dimensions) and see" << std::endl
      << "if they have different signs." << std::endl << std::endl;
    return;
  }

  // Sanity check.
  CheckCsgFlagCommandFileName(input_data_file, scad_file,
    output_negative_data_file, output_positive_data_file);
  if (min_dist < 0.0) {
    std::cerr << common::RedHead() << "command::CsgFlagCommand: wrong "
      << "min_dist: " << min_dist << common::RedTail() << std::endl;
    exit(-1);
  }

  // Read shape.
  csg::ScadFileParser scad_parser(scad_file);
  std::shared_ptr<csg::CsgNode> root = scad_parser.root();

  // Read points.
  std::vector<Eigen::Vector3d> points(0);
  common::ReadDataFile(input_data_file, points);

  // Filter out points.
  std::vector<Eigen::Vector3d> inside_points(0), outside_points(0);
  inside_points.reserve(points.size());
  outside_points.reserve(points.size());
  for (const auto& p : points) {
    const bool inside = root->IsInside(p);
    // Check if p is too close.
    bool too_close = false;
    for (int i = 0; i < 27; ++i) {
      const int ii = i / 9 - 1, jj = (i / 3) % 3 - 1, kk = i % 3 - 1;
      const Eigen::Vector3d p_neighbor = p
        + Eigen::Vector3d(ii * 1.0, jj * 1.0, kk * 1.0) * min_dist;
      if (root->IsInside(p_neighbor) != inside) {
        too_close = true;
        if (verbose) {
          std::cout << "command::CsgFlagCommand: points too close to the "
            << "bound: " << p.transpose() << std::endl;
        }
        break;
      }
    }
    if (too_close) continue;
    if (inside) inside_points.push_back(p);
    else outside_points.push_back(p);
  }

  // Write back results.
  common::WriteDataFile(outside_points, output_negative_data_file);
  common::WriteDataFile(inside_points, output_positive_data_file);
}

}
