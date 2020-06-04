#include "command/command.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include "common/file_helper.h"
#include "common/math_helper.h"
#include "primitive/surface_primitive.h"

namespace command {

static void CheckAddSeparatorCommandFileName(const std::string& aux_prim_file,
  const std::string& init_prim_file, const std::string& neg_data_file,
  const std::string& output_prim_file, const std::string& pos_data_file) {
  if (!common::HasExtension(aux_prim_file, ".prim")) {
    std::cerr << common::RedHead()
      << "command::CheckAddSeparatorCommandFileName: wrong prim file: "
      << aux_prim_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(init_prim_file, ".prim")) {
    std::cerr << common::RedHead()
      << "command::CheckAddSeparatorCommandFileName: wrong prim file: "
      << init_prim_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(neg_data_file, ".data")) {
    std::cerr << common::RedHead()
      << "command::CheckAddSeparatorCommandFileName: wrong data file: "
      << neg_data_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(output_prim_file, ".prim")) {
    std::cerr << common::RedHead()
      << "command::CheckAddSeparatorCommandFileName: wrong prim file: "
      << output_prim_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(pos_data_file, ".data")) {
    std::cerr << common::RedHead()
      << "command::CheckAddSeparatorCommandFileName: wrong data file: "
      << pos_data_file << common::RedTail() << std::endl;
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

void AddSeparatorCommand(const std::string& aux_prim_file,
  const double min_dist, const bool help, const std::string& init_prim_file,
  const std::string& neg_data_file, const std::string& output_prim_file,
  const std::string& pos_data_file, const bool verbose) {
  if (help) {
    std::cout
      << "add-separator       Choose minimal set of separators." << std::endl
      << "  -a <PRIM file>    Auxiliary primitive file." << std::endl
      << "  -e <double>       Minimum distance to primitives." << std::endl
      << "  -h                Print help information." << std::endl
      << "  -i <PRIM file>    Initial surface primitive file." << std::endl
      << "  -n <DATA file>    Negative equivalence classes." << std::endl
      << "  -o <PRIM file>    Output primitive file." << std::endl
      << "  -p <DATA file>    Positive equivalence classes." << std::endl
      << "  -v                Verbose mode." << std::endl << std::endl
      << "Given negative and positive equivalence classes, remove" << std::endl
      << "redundant primitives in aux_prim_file. We assume all" << std::endl
      << "negative and positive data points are unique and clean" << std::endl
      << "equivalence classes that are not close to any primitives" << std::endl
      << "(min_dist is just a sanity check)." << std::endl << std::endl; 
    return;
  }

  const int unsat_code = 1;
  CheckAddSeparatorCommandFileName(aux_prim_file, init_prim_file, neg_data_file,
    output_prim_file, pos_data_file);
  if (min_dist <= 0) {
    std::cerr << common::RedHead() << "command::AddSeparatorCommand: wrong "
      << "min_dist parameter: " << min_dist << common::RedTail() << std::endl;
    exit(-1);
  }

  // Read positive and negative equivalence classes.
  std::vector<Eigen::Vector3d> pos, neg;
  common::ReadDataFile(pos_data_file, pos);
  common::ReadDataFile(neg_data_file, neg);
  if (verbose) {
    std::cout << "command::AddSeparatorCommand: read " << pos.size()
      << " pos classes and " << neg.size() << " neg classes." << std::endl;
  }
  // Read primitives.
  std::vector<std::shared_ptr<primitive::SurfacePrimitive>>
    init_prims, aux_prims;
  common::ReadPrimFile(init_prim_file, init_prims);
  common::ReadPrimFile(aux_prim_file, aux_prims);
  if (verbose) {
    std::cout << "command::AddSeparatorCommand: read " << init_prims.size()
      << " surface primitives and " << aux_prims.size() << " auxiliary "
      << "primitives." << std::endl; 
  }

  // First, we assume all the init_prims are necessary and compute the
  // equivalence classes.
  std::unordered_map<std::string, std::vector<int>> init_pos_map, init_neg_map;
  const int pos_num = static_cast<int>(pos.size());
  const int neg_num = static_cast<int>(neg.size());
  for (int i = 0; i < pos_num; ++i) {
    init_pos_map[ComputeFlag(pos[i], min_dist, init_prims)].push_back(i);
  }
  for (int i = 0; i < neg_num; ++i) {
    init_neg_map[ComputeFlag(neg[i], min_dist, init_prims)].push_back(i);
  }
  if (verbose) {
    std::cout << "command::AddSeparatorCommand: " << init_pos_map.size()
      << " positive and " << init_neg_map.size() << " negative classes are "
      << "generated by the initial primitives." << std::endl;
  }
  // Every point not in init_pos_map /\ init_neg_map is resolved.
  std::vector<Eigen::Vector3d> new_pos, new_neg;
  for (const auto& pos_pair : init_pos_map) {
    if (init_neg_map.find(pos_pair.first) != init_neg_map.end()) {
      for (const int idx : pos_pair.second) {
        new_pos.push_back(pos[idx]);
      }
      for (const int idx : init_neg_map[pos_pair.first]) {
        new_neg.push_back(neg[idx]);
      }
    }
  }
  if (verbose) {
    std::cout << "command::AddSeparatorCommand: " << new_pos.size()
      << " positive and " << new_neg.size() << " negative classes need to be "
      << "resolved." << std::endl;
  }

  // Now use all primitives to resolve pos and neg but do not remove any in
  // init_prims.
  auto primitives = init_prims;
  primitives.insert(primitives.end(), aux_prims.begin(), aux_prims.end());
  const int init_prim_num = static_cast<int>(init_prims.size());
  const int aux_prim_num = static_cast<int>(aux_prims.size());
  std::unordered_set<std::string> pos_map, neg_map;
  for (const auto& p : new_pos) {
    const auto index = ComputeFlag(p, min_dist, primitives);
    pos_map.insert(index);
  }
  if (verbose) {
    std::cout << "command::AddSeparatorCommand: collected " << pos_map.size()
      << " positive equivalence classes." << std::endl;
  }
  for (const auto& p : new_neg) {
    const auto index = ComputeFlag(p, min_dist, primitives);
    neg_map.insert(index);
  }
  if (verbose) {
    std::cout << "command::AddSeparatorCommand: collected " << neg_map.size()
      << " negitive equivalence classes." << std::endl;
  }
  for (const auto& pos_flag : pos_map) {
    if (neg_map.find(pos_flag) != neg_map.end()) {
      std::ostringstream ss;
      ss << "command::AddSeparatorCommand: equivalence class ";
        for (int i = 0; i < init_prim_num + aux_prim_num; ++i) {
          ss << (GetBitFromString(pos_flag, i) ? "1 " : "0 ");
        }
      ss << "is both inside and outside the mesh. The problem is UNSAT.";
      common::PrintError(ss.str(), unsat_code);
    }
  }

  // active_prim_idx is the set of all necessary primitives.
  std::set<int> active_prim_idx, prim_idx_to_check;
  for (int i = 0; i < init_prim_num; ++i) active_prim_idx.insert(i);
  for (int i = 0; i < init_prim_num + aux_prim_num; ++i)
    prim_idx_to_check.insert(i);
  bool updated = true;
  while (updated) {
    updated = false;
    for (const int i : prim_idx_to_check) {
      if (active_prim_idx.find(i) != active_prim_idx.end()) continue;
      if (verbose) {
        std::cout << "command::AddSeparatorCommand: testing primitive " << i
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
          std::cout << "command::AddSeparatorCommand: primitive " << i
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
          std::cout << "command::AddSeparatorCommand: primitive "
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
    common::PrintError("command::AddSeparatorCommand: active_prim_idx and "
      "prim_idx_to_check should have the same size eventually.");
  }
  if (verbose) {
    std::cout << "command::AddSeparatorCommand: " << active_prim_idx.size()
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
        common::PrintError("command::AddSeparatorCommand: the problem is UNSAT "
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
