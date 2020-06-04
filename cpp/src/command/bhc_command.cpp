#include "command/command.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <stack>
#include <sstream>
#include "common/file_helper.h"
#include "common/math_helper.h"
#include "csg/csg_node.h"
#include "csg/csg_internal_node.h"
#include "csg/csg_sphere_node.h"
#include "csg/csg_cube_node.h"
#include "csg/csg_cylinder_node.h"
#include "csg/csg_torus_node.h"
#include "primitive/surface_primitive.h"
#include "primitive/spherical_surface.h"
#include "primitive/plane_surface.h"
#include "primitive/cylindrical_surface.h"
#include "primitive/toric_surface.h"

namespace command {

static void CheckBhcCommandFileName(const std::string& input_prim_file,
  const std::string& neg_data_file, const std::string& output_scad_file,
  const std::string& pos_data_file) {
  if (!common::HasExtension(input_prim_file, ".prim")) {
    std::cerr << common::RedHead()
      << "command::CheckBhcCommandFileName: wrong prim file: "
      << input_prim_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(neg_data_file, ".data")) {
    std::cerr << common::RedHead()
      << "command::CheckBhcCommandFileName: wrong data file: "
      << neg_data_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(output_scad_file, ".scad")) {
    std::cerr << common::RedHead()
      << "command::CheckBhcCommandFileName: wrong scad file: "
      << output_scad_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(pos_data_file, ".data")) {
    std::cerr << common::RedHead()
      << "command::CheckBhcCommandFileName: wrong data file: "
      << pos_data_file << common::RedTail() << std::endl;
    exit(-1);
  }
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

static const std::shared_ptr<csg::CsgNode> SolidifySurfacePrimitive(
  const std::shared_ptr<primitive::SurfacePrimitive>& prim,
  const bool use_positive, const double max_offset) {
  std::shared_ptr<csg::CsgNode> node = nullptr;
  if (prim->type_name() == "sphere") {
    const std::shared_ptr<primitive::SphericalSurface> sphere =
      std::dynamic_pointer_cast<primitive::SphericalSurface>(prim);
    const Eigen::Vector3d center = sphere->Center();
    const double radius = sphere->Radius();
    node = std::make_shared<csg::CsgSphereNode>(
      common::Translation(center), radius, 12);
  } else if (prim->type_name() == "plane") {
    const std::shared_ptr<primitive::PlaneSurface> plane =
      std::dynamic_pointer_cast<primitive::PlaneSurface>(prim);
    const Eigen::Vector3d n = plane->Normal();
    const double d = plane->Offset();
    const double t = -d;
    const Eigen::Vector3d center = t * n;
    // Create a giant cuboid.
    const Eigen::Vector3d cube_size(max_offset * 2,
      max_offset * 2, max_offset * 2);
    const Eigen::Quaterniond q = Eigen::Quaterniond::FromTwoVectors(
      Eigen::Vector3d::UnitZ(), n);
    const Eigen::Matrix4d transform = common::RotationAndTranslationToTransform(
      q, center + (use_positive ? 1.0 : -1.0) * n * cube_size.z() * 0.5);
    node = std::make_shared<csg::CsgCubeNode>(transform, cube_size);
    return node;
  } else if (prim->type_name() == "cylinder") {
    const std::shared_ptr<primitive::CylindricalSurface> cylinder =
      std::dynamic_pointer_cast<primitive::CylindricalSurface>(prim);
    const Eigen::Vector3d center = cylinder->Center();
    const Eigen::Vector3d axis = cylinder->Direction();
    const double radius = cylinder->Radius();
    const Eigen::Quaterniond q = Eigen::Quaterniond::FromTwoVectors(
      Eigen::Vector3d::UnitZ(), axis);
    const Eigen::Matrix4d transform =
      common::RotationAndTranslationToTransform(q, center);
    node = std::make_shared<csg::CsgCylinderNode>(transform,
      max_offset * 2, radius, 12);
  } else if (prim->type_name() == "torus") {
    const std::shared_ptr<primitive::ToricSurface> torus =
      std::dynamic_pointer_cast<primitive::ToricSurface>(prim);
    const Eigen::Vector3d center = torus->Center();
    const Eigen::Vector3d axis = torus->Axis();
    const double major_radius = torus->MajorRadii();
    const double minor_radius = torus->MinorRadii();
    const Eigen::Quaterniond q = Eigen::Quaterniond::FromTwoVectors(
      Eigen::Vector3d::UnitZ(), axis);
    const Eigen::Matrix4d transform =
      common::RotationAndTranslationToTransform(q, center);
    node = std::make_shared<csg::CsgTorusNode>(transform, major_radius,
      minor_radius, 12);
  } else {
    std::ostringstream ss;
    ss << "command::SolidifySurfacePrimitive: unsupported primitive type: "
      << prim->type_name();
    common::PrintError(ss.str());
  }
  if (use_positive) return node;
  // Need to add negation.
  const auto all = std::make_shared<csg::CsgCubeNode>(
    Eigen::Matrix4d::Identity(), Eigen::Vector3d::Constant(2 * max_offset));
  csg::csg_node_list children(2, nullptr);
  children[0] = all; children[1] = node;
  return std::make_shared<csg::CsgInternalNode>(children,
    Eigen::Matrix4d::Identity(), csg::CsgInternalNodeOperator::kSubtraction);
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

static void RemovePrimitives(std::unordered_set<std::string>& pos_sets,
  std::unordered_set<std::string>& neg_sets,
  std::unordered_set<int>& active_prim_idx) {
  for (const auto& pos_flag : pos_sets) {
    if (neg_sets.find(pos_flag) != neg_sets.end()) {
      std::ostringstream ss;
      ss << "command::RemovePrimitives: equivalence class is both inside and "
        << "outside the mesh.";
      common::PrintError(ss.str());
    }
  }

  // active_prim_idx is the set of all necessary primitives.
  auto prim_idx_to_check = active_prim_idx;
  active_prim_idx.clear();
  bool updated = true;
  while (updated) {
    updated = false;
    for (const int i : prim_idx_to_check) {
      if (active_prim_idx.find(i) != active_prim_idx.end()) continue;
      bool necessary = false;
      for (const auto& pos_index : pos_sets) {
        for (const auto& neg_index : neg_sets) {
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
      } else {
        updated = true;
        prim_idx_to_check.erase(i);
        std::unordered_set<std::string> new_pos_sets, new_neg_sets;
        for (std::string str : pos_sets) {
          SetBitInString(i, str);
          new_pos_sets.insert(str);
        }
        for (std::string str : neg_sets) {
          SetBitInString(i, str);
          new_neg_sets.insert(str);
        }
        new_pos_sets.swap(pos_sets);
        new_neg_sets.swap(neg_sets);
        break;
      } 
    }
  }
  // Now check if the problem is unsat. The problem is unsat if there exists one
  // pos region and one neg region that have the same index.
  for (const auto& pos_flag : pos_sets)
    for (const auto& neg_flag : neg_sets) {
      bool conflict = true;
      for (const int i : active_prim_idx) {
        if (GetBitFromString(pos_flag, i) != GetBitFromString(neg_flag, i)) {
          conflict = false;
          break;
        }
      }
      if (conflict) {
        common::PrintError("command::RemovePrimitives: the problem is UNSAT "
          "after removing primitives. This should never happen.");
      }
    }
}

static const std::shared_ptr<csg::CsgNode> GenerateEquivClassNode(
  const std::vector<std::shared_ptr<primitive::SurfacePrimitive>>& primitives,
  const std::string& flag, const double max_offset,
  const std::unordered_set<int>& active_prim_idx) {
  csg::csg_node_list children;
  for (const int i : active_prim_idx) {
    children.push_back(SolidifySurfacePrimitive(primitives[i],
      GetBitFromString(flag, i), max_offset));
  }
  return std::make_shared<csg::CsgInternalNode>(children,
    Eigen::Matrix4d::Identity(), csg::CsgInternalNodeOperator::kIntersection);
}

// Call this function with inside == true when you are absolutely sure either
// prim >= 0 or prim <= 0 does not contain any negative points. This means we
// can rewrite the solution as (prim_idx >= 0 or prim_idx <= 0) \/ Positive
// equiv classes.
// Call this function with inside == false when you are absolutely sure either
// prim >= 0 or prim <= 0 does not contain any positive points. In this case,
// we rewrite the solution as (prim < 0 or prim > 0) /\ Positive equiv classes.
static void FactorOutPrimitive(const int prim_idx, const bool inside,
  std::unordered_set<std::string>& pos_sets,
  std::unordered_set<std::string>& neg_sets,
  std::unordered_set<int>& active_prim_idx) {
  std::unordered_set<std::string> pos_sets_copy = pos_sets,
    neg_sets_copy = neg_sets;
  pos_sets.clear(); neg_sets.clear();
  for (std::string new_flag : pos_sets_copy) {
    SetBitInString(prim_idx, new_flag);
    pos_sets.insert(new_flag);
  }
  for (std::string new_flag : neg_sets_copy) {
    SetBitInString(prim_idx, new_flag);
    neg_sets.insert(new_flag);
  }
  // Resolve conflicts.
  pos_sets_copy = pos_sets;
  neg_sets_copy = neg_sets;
  for (const auto& flag : pos_sets_copy) {
    if (neg_sets_copy.find(flag) != neg_sets_copy.end()) {
      if (inside)
        pos_sets.erase(flag);
      else
        neg_sets.erase(flag);
    }
  }
  active_prim_idx.erase(prim_idx);
}

static void CheckEquivClassSide(const int prim_idx,
  const std::unordered_set<std::string>& equiv_classes,
  bool& inside, bool& outside) {
  inside = false; outside = false;
  for (const auto& flag : equiv_classes) {
    const bool equiv_class_inside_prim = GetBitFromString(flag, prim_idx);
    inside = inside || equiv_class_inside_prim;
    outside = outside || !equiv_class_inside_prim;
  }
}

// Given pos and neg equiv classes, figure out if we can factor out a primitive.
// If nothing is found, prim_idx = -1.
static const bool CheckPrimitiveToFactorOut(
  const std::unordered_set<std::string>& pos_sets,
  const std::unordered_set<std::string>& neg_sets,
  const std::unordered_set<int>& active_prim_idx,
  int& prim_idx, bool& inside, bool& use_positive) {
  prim_idx = -1;
  inside = false;
  use_positive = false;
  for (const int idx : active_prim_idx) {
    // Check primitive idx.
    bool see_pos_inside, see_pos_outside;
    CheckEquivClassSide(idx, pos_sets, see_pos_inside, see_pos_outside);
    if (see_pos_inside != see_pos_outside) {
      // We can factor it out.
      prim_idx = idx;
      // If see_pos_inside = true, then all positive equiv classes are inside
      // this primitive, which implies prim < 0 \in neg equiv classes.
      // If see_pos_inside = false, then all positive equiv classes are outside
      // this primitive, which implies prim >= 0 \in neg equiv classes.
      inside = false;
      use_positive = see_pos_inside;
      return true;
    }
    bool see_neg_inside, see_neg_outside;
    CheckEquivClassSide(idx, neg_sets, see_neg_inside, see_neg_outside);
    if (see_neg_inside != see_neg_outside) {
      // We can factor it out too.
      prim_idx = idx;
      // If see_neg_inside = true, then all negative equiv classes are inside
      // this primitive, which implies prim <= 0 \in pos equiv classes.
      // If see_neg_inside = false, then all negative equiv classes are outside
      // this primitive, which implies prim >= 0 \in pos equiv classes.
      inside = true;
      use_positive = see_neg_outside;
      return true;
    }
  }
  return false;
}

static const int ChoosePartitionPrimitive(
  const std::unordered_set<std::string>& pos_sets,
  const std::unordered_set<int>& active_prim_idx) {
  // In their paper they choose the one that splits the minimal number of
  // planes. Here we will do it in a quick and dirty way by choosing the one
  // that has the minimal difference between numbers of pos equiv classes that
  // are on both sides of the primitive.
  int prim_idx = -1;
  int min_diff_num = 0;
  for (const int idx : active_prim_idx) {
    int pos_num = 0, neg_num = 0;
    for (const auto& flag : pos_sets) {
      const bool inside = GetBitFromString(flag, idx);
      if (inside) ++pos_num;
      else ++neg_num;
    }
    int diff = std::abs(pos_num - neg_num);
    if (prim_idx == -1 || diff < min_diff_num) {
      prim_idx = idx;
      min_diff_num = diff;
    }
  }
  return prim_idx;
}

// Using active primitives to build a tree that includes all positive points and
// excludes all negative points.
static const std::shared_ptr<csg::CsgNode> SolvePointSets(
  const std::vector<std::shared_ptr<primitive::SurfacePrimitive>>& primitives,
  const std::unordered_set<std::string>& input_pos_sets,
  const std::unordered_set<std::string>& input_neg_sets,
  const std::unordered_set<int>& input_active_prim_idx,
  const double max_offset, const bool verbose) {
  // Check both sets are nonempty.
  if (input_pos_sets.empty()) {
    common::PrintError("command::SolvePointSets: pos_sets is empty.");
  }
  if (input_neg_sets.empty()) {
    common::PrintError("command::SolvePointSets: neg_sets is empty.");
  }
  std::unordered_set<std::string> pos_sets = input_pos_sets;
  std::unordered_set<std::string> neg_sets = input_neg_sets;
  std::unordered_set<int> active_prim_idx = input_active_prim_idx;
  // Filter out input points.
  RemovePrimitives(pos_sets, neg_sets, active_prim_idx);
  // Check if we can factor out any primitives.
  int prim_idx = -1;
  bool inside = false, use_positive = false;
  std::stack<std::pair<std::shared_ptr<csg::CsgNode>,
    csg::CsgInternalNodeOperator>> history;
  while (CheckPrimitiveToFactorOut(pos_sets, neg_sets, active_prim_idx,
    prim_idx, inside, use_positive)) {
    if (verbose) {
      std::cout << "command::SolvePointSets: factoring out primitive "
        << prim_idx << " " << primitives[prim_idx]->WriteToString()
        << (inside ? std::string(" because no negative points are inside ")
          + (use_positive ? "" : "the negation of ") + "this primitive"
         : std::string(" because no positive points are inside ")
          + (use_positive ? "the negation of " : "") + "this primitive")
        << std::endl;
      std::cout << "command::SolvePointSets: before factoring out: "
        << active_prim_idx.size() << " primitives. " << pos_sets.size()
        << " unique positive equivalence classes. " << neg_sets.size()
        << " unique negative equivalence classes." << std::endl;
    }
    FactorOutPrimitive(prim_idx, inside, pos_sets, neg_sets, active_prim_idx);
    if (verbose) {
      std::cout << "command::SolvePointSets: after factoring out: "
        << active_prim_idx.size() << " primitives. " << pos_sets.size()
        << " unique positive equivalence classes. " << neg_sets.size()
        << " unique negative equivalence classes." << std::endl;
    }
    const auto op = inside ? csg::CsgInternalNodeOperator::kUnion
      : csg::CsgInternalNodeOperator::kIntersection;
    history.push(std::make_pair(SolidifySurfacePrimitive(primitives[prim_idx],
      use_positive, max_offset), op));
  }
  // Corner cases: either pos_sets or neg_sets is empty.
  const auto all = std::make_shared<csg::CsgCubeNode>(
    Eigen::Matrix4d::Identity(), Eigen::Vector3d::Constant(2 * max_offset));
  std::shared_ptr<csg::CsgNode> node(nullptr);
  const auto union_op = csg::CsgInternalNodeOperator::kUnion;
  const auto intersect_op = csg::CsgInternalNodeOperator::kIntersection;
  if (pos_sets.empty()) node = nullptr;
  else if (neg_sets.empty()) node = all;
  else {
    // Choose a primitive to split.
    const int split_idx = ChoosePartitionPrimitive(pos_sets, active_prim_idx);
    if (split_idx == -1) {
      common::PrintError("command::SolvePointSets: cannot find a "
        "partitioning primitive. Should never happen.");
    }
    std::unordered_set<std::string> inside_pos_sets, outside_pos_sets;
    for (const auto& flag : pos_sets) {
      const bool inside = GetBitFromString(flag, split_idx);
      if (inside) inside_pos_sets.insert(flag);
      else outside_pos_sets.insert(flag);
    }
    // Recursively solve <inside_pos_sets, neg_sets> and
    // <outside_pos_sets, neg_sets>.
    std::shared_ptr<csg::CsgNode> inside_child(nullptr), outside_child(nullptr);
    if (!inside_pos_sets.empty()) {
      inside_child = SolvePointSets(primitives, inside_pos_sets, neg_sets,
        active_prim_idx, max_offset, verbose);
    }
    if (!outside_pos_sets.empty()) {
      outside_child = SolvePointSets(primitives, outside_pos_sets, neg_sets,
        active_prim_idx, max_offset, verbose);
    }
    if (!inside_child) node = outside_child;
    else if (!outside_child) node = inside_child;
    else {
      // Taking the union of the two.
      csg::csg_node_list children(2, nullptr);
      children[0] = inside_child; children[1] = outside_child;
      node = std::make_shared<csg::CsgInternalNode>(children,
        Eigen::Matrix4d::Identity(), union_op);
    }
  }
  // Now pop factored results from the stack.
  while (!history.empty()) {
    const auto top_history = history.top();
    history.pop();
    const auto left = top_history.first;
    const auto op = top_history.second;
    // Check if op is valid.
    if (op != union_op && op != intersect_op) {
      common::PrintError("command::SolvePointSets: unsupported operator.");
    }
    // Check if node is nullptr.
    if (node) {
      csg::csg_node_list children(2, nullptr);
      children[0] = left; children[1] = node;
      node = std::make_shared<csg::CsgInternalNode>(children,
        Eigen::Matrix4d::Identity(), op);
    } else {
      switch (op) {
        case union_op: {
          // left \/ nullptr = left.
          node = left;
          break;
        }
        case intersect_op: {
          // left /\ nullptr = nullptr.
          node = nullptr;
          break;
        }
        default: {
          common::PrintError("command::SolvePointSets: unsupported operator. "
            "Should never happen.");
        }
      }
    }
  }
  return node;
}

void BhcCommand(const bool help, const std::string& input_prim_file,
  const std::string& neg_data_file, const std::string& output_scad_file,
  const std::string& pos_data_file, const bool verbose) {
  if (help) {
    std::cout
      << "bhc                 Implement the BHC algorithm." << std::endl
      << "  -h                Print help information." << std::endl
      << "  -i <PRIM file>    All necessary primitives." << std::endl
      << "  -n <DATA file>    All negative equivalence classes." << std::endl
      << "  -o <SCAD file>    Output scad file." << std::endl
      << "  -p <DATA file>    All positive equivalence classes." << std::endl
      << "  -v                Verbose mode." << std::endl << std::endl
      << "Given negative and positive equivalence classes and all" << std::endl
      << "necessary primitives, return the scad file using the" << std::endl
      << "BHC algorithm. The points should not be close to the" << std::endl
      << "primitives and each occupies a unique equivalence class." << std::endl
      << "If these requirements are not met, the program will" << std::endl
      << "terminate with an error message." << std::endl << std::endl;
    return;
  }

  CheckBhcCommandFileName(input_prim_file, neg_data_file, output_scad_file,
    pos_data_file);
  // Read positive and negative equivalence classes.
  std::vector<Eigen::Vector3d> pos, neg;
  common::ReadDataFile(pos_data_file, pos);
  common::ReadDataFile(neg_data_file, neg);
  if (verbose) {
    std::cout << "command::BhcCommand: read " << pos.size()
      << " pos classes and " << neg.size() << " neg classes." << std::endl;
  }
  // Read primitives.
  std::vector<std::shared_ptr<primitive::SurfacePrimitive>> primitives;
  common::ReadPrimFile(input_prim_file, primitives);
  const int prim_num = static_cast<int>(primitives.size());
  if (verbose) {
    std::cout << "command::BhcCommand: read " << prim_num
      << " surface primitives." << std::endl;
  }

  // Check if each point is in a unique equivalence class.
  std::unordered_set<std::string> pos_sets, neg_sets;
  const double eps = common::Epsilon();
  const double inf = common::Infinity();
  Eigen::Vector3d pmax(-inf, -inf, -inf), pmin(inf, inf, inf);
  for (const auto& p : pos) {
    pmax = p.cwiseMax(pmax);
    pmin = p.cwiseMin(pmin);
    const auto flag = ComputeFlag(p, eps, primitives);
    if (pos_sets.find(flag) != pos_sets.end()) {
      std::ostringstream ss;
      ss << "command::BhcCommand: point (" << p.transpose() << ") shares equiv "
        << "class (";
      for (int i = 0; i < prim_num; ++i) {
        ss << (GetBitFromString(flag, i) ? "1" : "0");
      }
      ss << ") with another positive point.";
      common::PrintError(ss.str());
    }
    pos_sets.insert(flag);
  }
  for (const auto& p : neg) {
    pmax = p.cwiseMax(pmax);
    pmin = p.cwiseMin(pmin);
    const auto flag = ComputeFlag(p, eps, primitives);
    if (neg_sets.find(flag) != neg_sets.end()) {
      std::ostringstream ss;
      ss << "command::BhcCommand: point (" << p.transpose() << ") shares equiv "
        << "class (";
      for (int i = 0; i < prim_num; ++i) {
        ss << (GetBitFromString(flag, i) ? "1" : "0");
      }
      ss << ") with another negative point.";
      common::PrintError(ss.str());
    }
    if (pos_sets.find(flag) != pos_sets.end()) {
      std::ostringstream ss;
      ss << "command::BhcCommand: negative point (" << p.transpose() << ") and "
        << "a positive point shares the same equiv class (";
      for (int i = 0; i < prim_num; ++i) {
        ss << (GetBitFromString(flag, i) ? "1" : "0");
      }
      ss << ")";
      common::PrintError(ss.str());
    }
    neg_sets.insert(flag);
  }

  // We use a cube at (0, 0, 0) with size = 2 * max_offset to generate negation.
  const double max_offset = std::max(pmax.cwiseAbs().maxCoeff(),
    pmin.cwiseAbs().maxCoeff()) + 1;
  std::unordered_set<int> active_prim_idx;
  for (int i = 0; i < prim_num; ++i) active_prim_idx.insert(i);
  const auto root = SolvePointSets(primitives, pos_sets, neg_sets,
    active_prim_idx, max_offset, verbose);
  // Write back the solution.
  common::WriteScadFile(root, output_scad_file);
}

}
