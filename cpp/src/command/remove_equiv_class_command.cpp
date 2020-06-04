#include "command/command.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <set>
#include "common/file_helper.h"
#include "common/math_helper.h"

namespace command {

static void CheckRemoveEquivClassCommandFileName(
  const std::string& input_data_file, const std::string& output_data_file,
  const std::string& prim_file, const std::string& subtract_data_file) {
  if (!common::HasExtension(input_data_file, ".data")) {
    std::cerr << common::RedHead()
       << "command::CheckRemoveEquivClassCommandFileName: wrong data file: "
      << input_data_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(output_data_file, ".data")) {
    std::cerr << common::RedHead()
       << "command::CheckRemoveEquivClassCommandFileName: wrong data file: "
      << output_data_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(prim_file, ".prim")) {
    std::cerr << common::RedHead()
      << "command::CheckRemoveEquivClassCommandFileName: wrong prim file: "
      << prim_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(subtract_data_file, ".data")) {
    std::cerr << common::RedHead()
       << "command::CheckRemoveEquivClassCommandFileName: wrong data file: "
      << subtract_data_file << common::RedTail() << std::endl;
    exit(-1);
  }
}

void RemoveEquivClassCommand(const double min_dist, const bool help,
  const std::string& input_data_file, const std::string& output_data_file,
  const std::string& prim_file, const std::string& subtract_data_file,
  const bool verbose) {
  if (help) {
    std::cout
      << "remove-equiv-class  Remove equivalence points." << std::endl
      << "  -e <double>       Minimum distance to primitives." << std::endl
      << "  -h                Print help information." << std::endl
      << "  -i <DATA file>    Input data file." << std::endl
      << "  -o <DATA file>    Output data file." << std::endl
      << "  -p <PRIM file>    Input primitive file." << std::endl
      << "  -r <DATA file>    Points to remove." << std::endl
      << "  -v                Verbose mode." << std::endl << std::endl
      << "Subtract points that belong to the same equivalence" << std::endl
      << "classes in the second input data file from the first" << std::endl
      << "input file." << std::endl << std::endl;
    return;
  }

  CheckRemoveEquivClassCommandFileName(input_data_file, output_data_file,
    prim_file, subtract_data_file);
  // Read data.
  std::vector<Eigen::Vector3d> points, to_subtract;
  common::ReadDataFile(input_data_file, points);
  common::ReadDataFile(subtract_data_file, to_subtract);
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
  // We first collect all equivalence classes in to_subtract.
  std::set<Eigen::VectorXi, decltype(less)> unique_classes(less);
  const int prim_num = static_cast<int>(primitives.size());
  for (const auto& p : to_subtract) {
    // Compute its representative.
    Eigen::VectorXi index = Eigen::VectorXi::Zero(prim_num);
    bool too_close = false;
    for (int i = 0; i < prim_num; ++i) {
      const auto& surface = primitives[i];
      const double f_val = surface->DistToSurface(p);
      if (std::fabs(f_val) <= min_dist) {
        too_close = true;
        if (verbose) {
          std::cout << "command::RemoveEquivClassCommand: points too close to "
            << "the surface: " << f_val << ". point = " << p.transpose()
            << ", surface = " << surface->WriteToString() << std::endl;
        }
        break;
      }
      if (f_val > 0) index(i) = 1;
    }
    // Skip if it is too close.
    if (too_close) continue;
    unique_classes.insert(index);
  }
  // Now we can loop over all points.
  std::vector<Eigen::Vector3d> remains;
  for (const auto& p : points) {
    // Compute its representative.
    Eigen::VectorXi index = Eigen::VectorXi::Zero(prim_num);
    bool too_close = false;
    for (int i = 0; i < prim_num; ++i) {
      const auto& surface = primitives[i];
      const double f_val = surface->DistToSurface(p);
      if (std::fabs(f_val) <= min_dist) {
        too_close = true;
        if (verbose) {
          std::cout << "command::RemoveEquivClassCommand: points too close to "
            << "the surface: " << f_val << ". point = " << p.transpose()
            << ", surface = " << surface->WriteToString() << std::endl;
        }
        break;
      }
      if (f_val > 0) index(i) = 1;
    }
    // Skip if it is too close.
    if (too_close || unique_classes.find(index) != unique_classes.end())
      continue;
    remains.push_back(p); 
  }

  // Write points back to the file.
  common::WriteDataFile(remains, output_data_file);
}

}
