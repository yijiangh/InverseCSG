#include "command/command.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <map>
#include "common/file_helper.h"
#include "common/math_helper.h"

namespace command {

static void CheckEquivClassCommandFileName(const std::string& input_data_file,
  const std::string& prim_file, const std::string& output_data_file) {
  if (!common::HasExtension(input_data_file, ".data")) {
    std::cerr << common::RedHead()
       << "command::CheckEquivClassCommandFileName: wrong data file: "
      << input_data_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(prim_file, ".prim")) {
    std::cerr << common::RedHead()
      << "command::CheckEquivClassCommandFileName: wrong prim file: "
      << prim_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(output_data_file, ".data")) {
    std::cerr << common::RedHead()
      << "command::CheckEquivClassCommandFileName: wrong data file: "
      << output_data_file << common::RedTail() << std::endl;
    exit(-1);
  }
}

void EquivClassCommand(const double min_dist, const bool help,
  const std::string& input_data_file, const std::string& prim_file,
  const std::string& output_data_file, const bool verbose) {
  if (help) {
    std::cout
      << "equiv-class         Merge points into equivalent classes." << std::endl
      << "  -e <double>       Minimum distance to the primitives." << std::endl
      << "  -h                Print help information." << std::endl
      << "  -i <DATA file>    Input data file." << std::endl
      << "  -p <PRIM file>    Input primitive file." << std::endl
      << "  -o <DATA file>    Output data file." << std::endl
      << "  -v                Verbose mode." << std::endl << std::endl
      << "Given points and primitives, merge points based on the" << std::endl
      << "equivalent classes defined by the primitives. This" << std::endl
      << "command skips any points that are too close to the" << std::endl
      << "primitive surfaces, determined by checking if there" << std::endl
      << "exists one primitive s such that dist(p, s) <=" << std::endl
      << "min_dist." << std::endl << std::endl;
    return;
  }

  CheckEquivClassCommandFileName(input_data_file, prim_file, output_data_file);
  // Read data.
  std::vector<Eigen::Vector3d> points(0);
  common::ReadDataFile(input_data_file, points);
  std::vector<std::shared_ptr<primitive::SurfacePrimitive>> primitives(0);
  common::ReadPrimFile(prim_file, primitives);

  // Thanks to C++11 we can use decltype to wrap CompareEigenVectorXi. In this
  // way there is no need to introduce a separate struct.
  auto less = [](const Eigen::VectorXi& a, const Eigen::VectorXi& b) {
    assert(a.size() == b.size());
    for (auto i = 0; i < a.size(); ++i) {
      if (a(i) < b(i)) return true;
      if (a(i) > b(i)) return false;
    }
    return false;
  };
  std::map<Eigen::VectorXi, std::pair<Eigen::Vector3d, double>, decltype(less)>
    unique_points_map(less);
  const int prim_num = static_cast<int>(primitives.size());
  for (const auto& p : points) {
    // Compute its representative.
    Eigen::VectorXi index = Eigen::VectorXi::Zero(prim_num);
    bool too_close = false;
    double min_point_dist = common::Infinity();
    for (int i = 0; i < prim_num; ++i) {
      const auto& surface = primitives[i];
      const double f_val = surface->DistToSurface(p);
      const double f_val_abs = std::fabs(f_val);
      if (f_val_abs <= min_dist) {
        too_close = true;
        if (verbose) {
          std::cout << "command::EquivClassCommand: points too close to the "
            << "surface: " << f_val << ". point = " << p.transpose()
            << ", surface = " << surface->WriteToString() << std::endl;
        }
        break;
      }
      if (f_val_abs < min_point_dist) min_point_dist = f_val_abs;
      if (f_val > 0) index(i) = 1;
    }
    // Skip if it is too close.
    if (too_close) continue;
    if (unique_points_map.find(index) == unique_points_map.end() ||
      min_point_dist > unique_points_map[index].second) {
      unique_points_map[index] = std::make_pair(p, min_point_dist);
    }
  }

  // Write points back to the file.
  std::vector<Eigen::Vector3d> new_points(0);
  new_points.reserve(unique_points_map.size());
  for (const auto& pair : unique_points_map) {
    new_points.push_back(pair.second.first);
  }
  common::WriteDataFile(new_points, output_data_file);
}

}
