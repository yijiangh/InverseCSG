#include "command/command.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_set>
#include <sstream>
#include "common/file_helper.h"
#include "common/math_helper.h"
#include "primitive/surface_primitive.h"

namespace command {

static void CheckRemovePrimCommandFileName(const std::string& input_prim_file,
  const std::string& input_neg_data_file, const std::string& output_prim_file,
  const std::string& input_pos_data_file) {
  if (!common::HasExtension(input_prim_file, ".prim")) {
    std::cerr << common::RedHead()
      << "command::CheckRemovePrimCommandFileName: wrong prim file: "
      << input_prim_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(input_neg_data_file, ".data")) {
    std::cerr << common::RedHead()
      << "command::CheckRemovePrimCommandFileName: wrong data file: "
      << input_neg_data_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(output_prim_file, ".prim")) {
    std::cerr << common::RedHead()
      << "command::CheckRemovePrimCommandFileName: wrong prim file: "
      << output_prim_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(input_pos_data_file, ".data")) {
    std::cerr << common::RedHead()
      << "command::CheckRemovePrimCommandFileName: wrong data file: "
      << input_pos_data_file << common::RedTail() << std::endl;
    exit(-1);
  }
}

static const bool GetBitFromString(const std::string& str, const int idx) {
  const int pos = idx / 8, offset = idx % 8;
  return str[pos] & (1 << offset);
}

static void SetBitInString(const int idx, std::string& str) {
  const int pos = idx / 8, offset = idx % 8;
  str[pos] = str[pos] | (1 << offset);
}

static void UnsetBitInString(const int idx, std::string& str) {
  const int pos = idx / 8, offset = idx % 8;
  str[pos] = str[pos] & ~(1 << offset);
}

static const std::string ComputeFlag(const Eigen::Vector3d& p,
  const double min_dist,
  const std::vector<std::shared_ptr<primitive::SurfacePrimitive>>& prims) {
  const int prim_num = static_cast<int>(prims.size());
  const int char_num = (prim_num % 8) ? (prim_num / 8 + 1) : (prim_num / 8);
  std::string index(char_num, 0);
  for (int i = 0; i < prim_num; ++i) {
    const auto& surface = prims[i];
    const double f_val = surface->DistToSurface(p);
    if (std::fabs(f_val) <= min_dist) {
      std::cerr << common::RedHead() << "command::ComputeFlag: point ("
        << p.transpose() << ") is too close to the surface "
        << surface->WriteToString() << common::RedTail() << std::endl;
      exit(-1);
    }
    if (f_val > 0) {
      const int pos = i / 8, offset = i % 8;
      index[pos] = index[pos] | (1 << offset);
    }
  }
  return index;
}

void RemovePrimCommand(const double min_dist, const bool help,
  const std::string& input_prim_file, const std::string& input_neg_data_file,
  const std::string& output_prim_file, const std::string& input_pos_data_file,
  const bool verbose) {
  if (help) {
    std::cout
      << "remove-prim         Remove redundant primitive." << std::endl
      << "  -e <double>       Minimum distance to primitives." << std::endl
      << "  -h                Print help information." << std::endl
      << "  -i <PRIM file>    Input primitives." << std::endl
      << "  -n <DATA file>    Input negative equivalence classes." << std::endl
      << "  -o <PRIM file>    Output primitives." << std::endl
      << "  -p <DATA file>    Input positive equivalence classes." << std::endl
      << "  -v                Verbose mode." << std::endl << std::endl
      << "Given negative and positive equivalence classes, remove" << std::endl
      << "redundant primitives. The input data files are assumed" << std::endl
      << "to be clean, unique equivalence classes. If the problem" << std::endl
      << "is UNSAT using existing primitives, we will return a" << std::endl
      << "primitive file that has zero primitives. This command" << std::endl
      << "returns 1 if the problem is UNSAT." << std::endl << std::endl;
  }

  const int unsat_code = 1;
  CheckRemovePrimCommandFileName(input_prim_file, input_neg_data_file,
    output_prim_file, input_pos_data_file);
  if (min_dist <= 0) {
    std::cerr << common::RedHead() << "command::RemovePrimCommand: wrong "
      << "min_dist parameter: " << min_dist << common::RedTail() << std::endl;
    exit(-1);
  }
  // Read positive and negative equivalence classes.
  std::vector<Eigen::Vector3d> pos, neg;
  common::ReadDataFile(input_pos_data_file, pos);
  common::ReadDataFile(input_neg_data_file, neg);
  // Read primitives.
  std::vector<std::shared_ptr<primitive::SurfacePrimitive>> primitives;
  common::ReadPrimFile(input_prim_file, primitives);
  const int prim_num = static_cast<int>(primitives.size());
  if (verbose) {
    std::cout << "command::RemovePrimCommand: " << prim_num << " primitives"
      << " at the beginning." << std::endl;
  }

  // Use pos_flag and neg_flag to check the input is healthy.
  std::unordered_set<std::string> pos_map, neg_map;
  for (const auto& p : pos) {
    const auto index = ComputeFlag(p, min_dist, primitives);
    pos_map.insert(index);
  }
  if (verbose) {
    std::cout << "command::RemovePrimCommand: collected " << pos_map.size()
      << " positive equivalence classes. Key size = "
      << pos_map.begin()->size() << " chars." << std::endl;
  }
  for (const auto& p : neg) {
    const auto index = ComputeFlag(p, min_dist, primitives);
    neg_map.insert(index);
  }
  if (verbose) {
    std::cout << "command::RemovePrimCommand: collected " << neg_map.size()
      << " negitive equivalence classes. Key size = "
      << neg_map.begin()->size() << " chars." << std::endl;
  }
  for (const auto& pos_flag : pos_map) {
    if (neg_map.find(pos_flag) != neg_map.end()) {
      std::ostringstream ss;
      ss << "command::RemovePrimCommand: equivalence class ";
        for (int i = 0; i < prim_num; ++i) {
          ss << (GetBitFromString(pos_flag, i) ? "1 " : "0 ");
        }
      ss << "is both inside and outside the mesh. The problem is UNSAT.";
      common::PrintError(ss.str(), unsat_code);
    }
  }

  // active_prim_idx is the set of all necessary primitives.
  std::set<int> active_prim_idx, prim_idx_to_check;
  for (int i = 0; i < prim_num; ++i) prim_idx_to_check.insert(i);
  bool updated = true;
  while (updated) {
    updated = false;
    for (const int i : prim_idx_to_check) {
      if (active_prim_idx.find(i) != active_prim_idx.end()) continue;
      if (verbose) {
        std::cout << "command::RemovePrimCommand: testing primitive " << i
          << std::endl;
      }
      const auto& p = primitives[i];
      bool necessary = false;
      for (const auto& pos_index : pos_map) {
        for (const auto& neg_index : neg_map) {
          necessary = true;
          for (const int j : prim_idx_to_check) {
            if (i == j) continue;
            if (GetBitFromString(pos_index, j)
              != GetBitFromString(neg_index, j)) {
              necessary = false;
              break;
            }
          }
          if (necessary) break;
        }
        if (necessary) break;
      }
      if (necessary) {
        active_prim_idx.insert(i);
        if (verbose) {
          std::cout << "command::RemovePrimCommand: primitive " << i
            << " is necessary." << std::endl;
        }
      } else {
        updated = true;
        prim_idx_to_check.erase(i);
        std::unordered_set<std::string> new_pos_map, new_neg_map;
        for (std::string str : pos_map) {
          SetBitInString(i, str);
          new_pos_map.insert(str);
        }
        for (std::string str : neg_map) {
          SetBitInString(i, str);
          new_neg_map.insert(str);
        }
        new_pos_map.swap(pos_map);
        new_neg_map.swap(neg_map);
        if (verbose) {
          std::cout << "command::RemovePrimCommand: primitive "
            << p->WriteToString() << " is redundant. "
            << prim_idx_to_check.size() << " primitives left. "
            << pos_map.size() << " positive equivalence classes. "
            << neg_map.size() << " negative equivalence classes. " << std::endl;
        }
        break;
      } 
    }
  }
  if (active_prim_idx.size() != prim_idx_to_check.size()) {
    common::PrintError("command::RemovePrimCommand: active_prim_idx and "
      "prim_idx_to_check should have the same size eventually.");
  }
  if (verbose) {
    std::cout << "command::RemovePrimCommand: " << active_prim_idx.size()
      << " primitives after filtering." << std::endl;
  }

  // Now check if the problem is unsat. The problem is unsat if there exists one
  // pos region and one neg region that have the same index.
  for (const auto& pos_flag : pos_map)
    for (const auto& neg_flag : neg_map) {
      bool conflict = true;
      for (const int i : active_prim_idx) {
        if (GetBitFromString(pos_flag, i) != GetBitFromString(neg_flag, i)) {
          conflict = false;
          break;
        }
      }
      if (conflict) {
        common::PrintError("command::RemovePrimCommand: the problem is UNSAT "
          "after removing primitives. This indicates an error in remove-prim.",
          unsat_code);
      }
    }
  // Write back the new primitives.
  auto final_primitives = primitives;
  final_primitives.clear();
  for (const int i : active_prim_idx) final_primitives.push_back(primitives[i]);
  common::WritePrimFile(final_primitives, output_prim_file);
}

}
