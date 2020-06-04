#include "command/command.h"
#include <iostream>
#include <unordered_set>
#include "common/file_helper.h"
#include "common/math_helper.h"
#include "primitive/surface_primitive.h"

namespace command {

static void CheckPrimitiveLocalCommandFileName(const std::string& meta_file,
  const std::string& output_primitive_file,
  const std::string& input_primitive_file) {
  if (!common::HasExtension(meta_file, ".meta")) {
    std::cerr << common::RedHead()
      << "command::PrimitiveLocalCommand: wrong meta file: "
      << meta_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(output_primitive_file, ".prim")) {
    std::cerr << common::RedHead()
      << "command::PrimitiveLocalCommand: wrong output prim file: "
      << output_primitive_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(input_primitive_file, ".prim")) {
    std::cerr << common::RedHead()
      << "command::PrimitiveLocalCommand: wrong input prim file: "
      << input_primitive_file << common::RedTail() << std::endl;
    exit(-1);
  }
}

void PrimitiveLocalCommand(const bool help, const std::string& meta_file,
  const std::string& output_primitive_file,
  const std::string& input_primitive_file, const Eigen::Vector3d& pmin,
  const Eigen::Vector3d& pmax, const bool verbose) {
  if (help) {
    std::cout
      << "primitive-local     Detect primitives inside a region." << std::endl
      << "  -h                Print help information." << std::endl
      << "  -i <META file>    Primitive metadata file." << std::endl
      << "  -o <PRIM file>    Output primitive file." << std::endl
      << "  -p <PRIM file>    Primitive file." << std::endl
      << "  -s <Vector6f>     Region of interest: <xmin xmax ymin ymax"
      << " zmin zmax>." << std::endl
      << "  -v                Verbose mode." << std::endl << std::endl
      << "Given a region of interest, return all primitives that" << std::endl
      << "are inside this region. The meta file and the primitive" << std::endl
      << "file are from the primitive command." << std::endl << std::endl;
    return;
  }

  // Check file extensions first.
  CheckPrimitiveLocalCommandFileName(meta_file, output_primitive_file,
    input_primitive_file);
  // Check region of interest.
  if ((pmax - pmin).minCoeff() < common::Epsilon()) {
    std::cerr << common::RedHead()
      << "command::PrimitiveLocalCommand: invalid region of interest:"
      << " (" << pmin.transpose() << "), (" << pmax.transpose() << ")."
      << common::RedTail() << std::endl;
    exit(-1);
  }

  // Read all primitives.
  std::vector<std::shared_ptr<primitive::SurfacePrimitive>> primitives;
  common::ReadPrimFile(input_primitive_file, primitives);
  if (verbose) {
    std::cout << "command::PrimitiveLocalCommand: " << primitives.size()
      << " primitives at the beginning." << std::endl;
  }

  // Find the right primitives.
  std::vector<std::shared_ptr<primitive::SurfacePrimitive>> results;
  for (const auto& p : primitives) {
    if (p->IntersectRoi(pmin, pmax)) results.push_back(p);
  }
  if (verbose) {
    std::cout << "command::PrimitiveLocalCommand: " << results.size()
      << " primitives in area (" << pmin.transpose() << "), ("
      << pmax.transpose() << "). Note that false positives are "
      << "allowed." << std::endl;
  }
  common::WritePrimFile(results, output_primitive_file);
}

// This is the old version that requires meta points.
// TODO: remove this deprecated function once the code is stabilized.
/*
void PrimitiveLocalCommand(const bool help, const std::string& meta_file,
  const std::string& output_primitive_file,
  const std::string& input_primitive_file, const Eigen::Vector3d& pmin,
  const Eigen::Vector3d& pmax, const bool verbose) {
  if (help) {
    std::cout
      << "Given a region of interest, return all primitives that" << std::endl
      << "are inside this region. The meta file and the primitive" << std::endl
      << "file are from the primitive command." << std::endl << std::endl;
    return;
  }

  // Check file extensions first.
  CheckPrimitiveLocalCommandFileName(meta_file, output_primitive_file,
    input_primitive_file);
  // Check region of interest.
  if ((pmax - pmin).minCoeff() < common::Epsilon()) {
    std::cerr << common::RedHead()
      << "command::PrimitiveLocalCommand: invalid region of interest:"
      << " (" << pmin.transpose() << "), (" << pmax.transpose() << ")."
      << common::RedTail() << std::endl;
    exit(-1);
  }

  // Read all sample points.
  std::vector<std::pair<Eigen::Vector3d, int>> points(0);
  common::ReadMetaFile(meta_file, points);
  // Read all primitives.
  std::vector<std::shared_ptr<primitive::SurfacePrimitive>> primitives(0);
  common::ReadPrimFile(input_primitive_file, primitives);
  const int prim_num = static_cast<int>(primitives.size());

  std::unordered_set<int> prim_in_roi;
  for (const auto& p : points) {
    const Eigen::Vector3d& point = p.first;
    const int prim_idx = p.second;
    if ((point - pmin).minCoeff() > 0 && (pmax - point).minCoeff() > 0) {
      if (prim_idx < 0 || prim_idx >= prim_num) {
        std::cerr << common::RedHead()
          << "command::PrimitiveLocalCommand: primitive index out of "
          << "bound: " << prim_idx << ", " << prim_num << common::RedTail()
          << std::endl;
        exit(-1);
      }
      prim_in_roi.insert(prim_idx);
    }
  }

  std::vector<std::shared_ptr<primitive::SurfacePrimitive>> results(0);
  results.reserve(prim_in_roi.size());
  for (const int idx : prim_in_roi) {
    results.push_back(primitives[idx]);
  }
  common::WritePrimFile(results, output_primitive_file);
}
*/

}
