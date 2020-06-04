#include "command/command.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>
#include <cmath>
#include "common/math_helper.h"
#include "common/file_helper.h"
#include "csg/csg_node.h"
#include "csg/csg_internal_node.h"
#include "csg/csg_sphere_node.h"
#include "csg/csg_cube_node.h"
#include "csg/csg_cylinder_node.h"
#include "mesh/tri_mesh.h"
#include "primitive/surface_primitive.h"
#include "primitive/spherical_surface.h"
#include "primitive/plane_surface.h"
#include "primitive/cylindrical_surface.h"

namespace command {

// Configurations.
// TODO: move them into input arguments in the future.
static const double max_bound = 1000.0;
static const double density = 10000.0;
static const double subtree_prob = 0.7;
static const int max_depth = 10;
static const int population_size = 150;
static const double mutation_rate = 0.3;
static const double crossover_rate = 0.3;
static const int max_iter = 3000;
static const double alpha = common::DegreeToRadian(10.0);
static const int n = 2;
static std::vector<Eigen::VectorXd> prim_scores(0);
static std::vector<Eigen::Matrix3Xd> prim_gradients(0);
static std::unordered_map<std::shared_ptr<csg::CsgNode>, int> prim_idx(0);

static double eps_d = 0.01; // Then scaled by the bounding box.
static double lambda = 0.0; // Scaled by the number of samples.

static void CheckGeneticCommandFileName(const std::string& mesh_file,
  const std::string& prim_file, const std::string& output_scad_file) {
  if (!common::HasExtension(mesh_file, ".off")) {
    std::cerr << common::RedHead()
      << "command::CheckGeneticCommandFileName: wrong mesh file: "
      << mesh_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(prim_file, ".prim")) {
    std::cerr << common::RedHead()
      << "command::CheckGeneticCommandFileName: wrong prim file: "
      << prim_file << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(output_scad_file, ".scad")) {
    std::cerr << common::RedHead()
      << "command::CheckGeneticCommandFileName: wrong scad file: "
      << output_scad_file << common::RedTail() << std::endl;
    exit(-1);
  }
}

static void SampleFromTriangleMesh(const mesh::TriMesh& shape, const double density,
  std::vector<std::pair<Eigen::Vector3d, Eigen::Vector3d>>& samples) {
  samples.clear();
  Eigen::Matrix3Xd points, normals;
  Eigen::VectorXi dummy;
  shape.Sample(density, true, points, normals, dummy);
  samples.resize(points.cols());
  for (auto i = 0; i < points.cols(); ++i) {
    samples[i].first = points.col(i);
    samples[i].second = normals.col(i);
  }
}

// We don't want to change the CsgNode class too much so we create proxies here.
struct CsgNodeProxy {
public:
  std::shared_ptr<csg::CsgNode> node;
  std::vector<int> children;
  int index;
  int parent_index;
  int num_of_nodes;
  int depth;  // depth == 0 <=> leaf.
  int primitive_idx;  // Used by leaf nodes only.
};

static void CreateCsgNodeProxy(const std::shared_ptr<csg::CsgNode>& root,
  std::vector<CsgNodeProxy>& proxies) {
  proxies.clear();
  if (root->IsLeaf()) {
    if (prim_idx.find(root) == prim_idx.end()) {
      common::PrintError("command::CreateCsgNodeProxy: new leaf.");
    }
    const int idx = prim_idx.at(root);
    CsgNodeProxy proxy{ root, {}, 0, -1, 1, 0, idx };
    proxies.push_back(proxy);
    return;
  }
  proxies.push_back({ root, {}, 0, -1, 1, 0, -1 });
  for (const auto& child : root->children()) {
    std::vector<CsgNodeProxy> child_proxies(0);
    CreateCsgNodeProxy(child, child_proxies);
    // Update root.
    if (proxies[0].depth < child_proxies[0].depth + 1) {
      proxies[0].depth = child_proxies[0].depth + 1;
    }
    proxies[0].children.push_back(proxies[0].num_of_nodes);
    // Update children.
    for (auto& proxy : child_proxies) {
      for (int& child : proxy.children) {
        child += proxies[0].num_of_nodes;
      }
      proxy.index += proxies[0].num_of_nodes;
      if (proxy.parent_index == -1) proxy.parent_index = 0;
      else proxy.parent_index += proxies[0].num_of_nodes;
      proxies.push_back(proxy);
    }
    proxies[0].num_of_nodes += static_cast<int>(child_proxies.size());
  }
}

// The three functions below are very inefficient and only used in
// CheckCsgNodeProxy. In general you should avoid using them.
static const int ComputeCsgDepth(const std::shared_ptr<csg::CsgNode>& node) {
  if (node->IsLeaf()) return 0;
  int depth = 0;
  for (const auto child : node->children()) {
    const int child_depth = ComputeCsgDepth(child);
    if (child_depth > depth) depth = child_depth;
  }
  return depth + 1;
}

static const int ComputeCsgNodeNumber(
  const std::shared_ptr<csg::CsgNode>& node) {
  if (node->IsLeaf()) return 1;
  int count = 1;
  for (const auto child : node->children()) {
    count += ComputeCsgNodeNumber(child);
  }
  return count;
}

static const std::shared_ptr<csg::CsgNode> GetNodeAtIndex(
  const std::shared_ptr<csg::CsgNode>& root, const int idx) {
  const int num_of_nodes = ComputeCsgNodeNumber(root);
  if (idx < 0 || idx >= num_of_nodes) {
    std::cerr << common::RedHead() << "command::GetNodeAtIndex: index out of "
      << "range." << common::RedTail() << std::endl;
    exit(-1);
  }
  if (idx == 0) return root;
  int count = 1;
  for (const auto& child : root->children()) {
    int child_node_num = ComputeCsgNodeNumber(child);
    if (idx >= count && idx < count + child_node_num) {
      return GetNodeAtIndex(child, idx - count);
    }
    count += child_node_num;
  }
  common::PrintError("command::GetNodeAtIndex: index out of range.");
  return nullptr;
}

static void CheckCsgNodeProxy(const std::shared_ptr<csg::CsgNode>& root,
  const std::vector<CsgNodeProxy>& proxies) {
  const int node_num = ComputeCsgNodeNumber(root);
  if (node_num != static_cast<int>(proxies.size())) {
    std::cerr << common::RedHead() << "command::CheckCsgNodeProxy: node number "
      << "did not match: " << node_num << ", " << proxies.size()
      << common::RedTail() << std::endl;
    exit(-1);
  }
  for (int i = 0; i < node_num; ++i) {
    const std::shared_ptr<csg::CsgNode> node = GetNodeAtIndex(root, i);
    if (proxies[i].node != node) {
      common::PrintError("command::CheckCsgNodeProxy: pointers "
        "to the node did not match.");
    }
    if (proxies[i].index != i) {
      common::PrintError("command::CheckCsgNodeProxy: node "
        "index did not match.");
    }
    if (proxies[i].num_of_nodes != ComputeCsgNodeNumber(node)) {
      common::PrintError("command::CheckCsgNodeProxy: number of "
        "nodes did not match.");
    }
    if (proxies[i].depth != ComputeCsgDepth(node)) {
      common::PrintError("command::CheckCsgNodeProxy: node depth "
        "did not match.");
    }
    // Check parents.
    if (i == 0) {
      // This has to be the root.
      if (proxies[i].parent_index != -1 || node != root) {
        common::PrintError("command::CheckCsgNodeProxy: root "
          "pointers did not match.");
      }
    } else {
      if (proxies[i].parent_index == -1) {
        common::PrintError("command::CheckCsgNodeProxy: child "
          "pointers did not match.");
      }
      const auto& parent_node = proxies[proxies[i].parent_index].node;
      bool good = false;
      for (const auto& kid : parent_node->children()) {
        if (proxies[i].node == kid) {
          good = true;
          break;
        }
      }
      if (!good) {
        common::PrintError("command::CheckCsgNodeProxy: pointers "
          "to the node did not match.");
      }
    }
    // Check children.
    const int child_num = static_cast<int>(proxies[i].children.size());
    if (child_num != proxies[i].node->NumOfChildren()) {
      common::PrintError("command::CheckCsgNodeProxy: children number did not "
        "match");
    }
    for (int j = 0; j < child_num; ++j) {
      if (proxies[proxies[i].children[j]].node !=
        proxies[i].node->children()[j]) {
        common::PrintError("command::CheckCsgNodeProxy: children relation "
          "did not match");
      }
    }
  }
}

static std::shared_ptr<csg::CsgNode> GenerateRandomCsgLeaf(
  const std::vector<std::shared_ptr<primitive::SurfacePrimitive>>& primitives) {
  const int prim_num = static_cast<int>(primitives.size());
  const int idx = common::GenerateRandomInt(0, prim_num);
  const std::shared_ptr<primitive::SurfacePrimitive> prim = primitives[idx];
  // Check primitive type.
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
    const Eigen::Vector3d cube_size(max_bound,
      max_bound, max_bound);
    const Eigen::Quaterniond q = Eigen::Quaterniond::FromTwoVectors(
      Eigen::Vector3d::UnitZ(), n);
    const Eigen::Matrix4d transform = common::RotationAndTranslationToTransform(
      q, center + n * cube_size.z() * 0.5);
    node = std::make_shared<csg::CsgCubeNode>(transform, cube_size);
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
      max_bound, radius, 12);
  } else {
    std::cerr << common::RedHead()
      << "command::GenerateRandomCsgLeaf: unsupported primitive type: "
      << prim->type_name() << common::RedTail() << std::endl;
    exit(-1);
  }
  prim_idx[node] = idx;
  return node;
}

static std::shared_ptr<csg::CsgNode> GenerateRandomCsgTree(
  const std::vector<std::shared_ptr<primitive::SurfacePrimitive>>& primitives,
  const double subtree_prob, const int max_depth) {
  double prob = common::GenerateRandomFloat();
  if (prob >= subtree_prob || max_depth == 0) {
    // Generate a leaf node and we are done.
    return GenerateRandomCsgLeaf(primitives);
  }
  // Build its left and right children.
  std::shared_ptr<csg::CsgNode> left_kid = GenerateRandomCsgTree(
    primitives, subtree_prob, max_depth - 1);
  const std::shared_ptr<csg::CsgNode> right_kid = GenerateRandomCsgTree(
    primitives, subtree_prob, max_depth - 1);
  // Randomly pick a set operator.
  prob = common::GenerateRandomFloat();
  csg::CsgInternalNodeOperator choice;
  if (prob < 1.0 / 4.0)
    choice = csg::CsgInternalNodeOperator::kUnion;
  else if (prob < 2.0 / 4.0)
    choice = csg::CsgInternalNodeOperator::kIntersection;
  else if (prob < 3.0 / 4.0)
    choice = csg::CsgInternalNodeOperator::kSubtraction;
  else {
    // Complement needs some trick.
    choice = csg::CsgInternalNodeOperator::kSubtraction;
    left_kid = std::make_shared<csg::CsgSphereNode>(Eigen::Matrix4d::Identity(),
      max_bound, 12);
    prim_idx[left_kid] = static_cast<int>(primitives.size());
  }
  const csg::csg_node_list kids{ left_kid, right_kid };
  return std::make_shared<csg::CsgInternalNode>(kids,
    Eigen::Matrix4d::Identity(), choice);
}

static const int ComputeDistanceToRoot(const std::vector<CsgNodeProxy>& proxies,
  const int idx) {
  // Root -> 0.
  int node_idx = idx;
  int dist = -1;
  while (node_idx != -1) {
    node_idx = proxies[node_idx].parent_index;
    ++dist;
  }
  return dist;
}

static void ReplaceSubtree(std::shared_ptr<csg::CsgNode>& root,
  const std::shared_ptr<csg::CsgNode>& subtree,
  const int cut_idx, const std::vector<CsgNodeProxy>& proxies) {
  const int node_num = static_cast<int>(proxies.size());
  if (cut_idx < 0 || cut_idx >= node_num) {
    common::PrintError("command::ReplaceSubtree: index out of range.");
  }
  const auto mutate_node = proxies[cut_idx].node;
  std::shared_ptr<csg::CsgNode> parent = nullptr;
  if (proxies[cut_idx].parent_index != -1)
    parent = proxies[proxies[cut_idx].parent_index].node;
  if (!parent) {
    root = subtree;
    return;
  }
  const int kid_num = parent->NumOfChildren();
  for (int i = 0; i < kid_num; ++i) {
    if (parent->children()[i] == mutate_node) {
      parent->set_children(i, subtree);
      return;
    }
  }
  common::PrintError("command::ReplaceSubtree: children did not match");
}

static void CrossOverCsgTrees(std::shared_ptr<csg::CsgNode>& root1,
  const std::vector<CsgNodeProxy>& proxies1,
  std::shared_ptr<csg::CsgNode>& root2,
  const std::vector<CsgNodeProxy>& proxies2,
  const int max_depth, const double crossover_rate) {
  const double prob = common::GenerateRandomFloat();
  if (prob >= crossover_rate) return;
  const int root1_node_num = static_cast<int>(proxies1.size());
  const int root2_node_num = static_cast<int>(proxies2.size());
  const int cut1_idx = common::GenerateRandomInt(0, root1_node_num);
  const int cut2_idx = common::GenerateRandomInt(0, root2_node_num);
  const int dist_to_root1 = ComputeDistanceToRoot(proxies1, cut1_idx);
  const int dist_to_root2 = ComputeDistanceToRoot(proxies2, cut2_idx);
  // Check if we can exchange.
  if (proxies1[cut1_idx].depth + dist_to_root2 > max_depth ||
    proxies2[cut2_idx].depth + dist_to_root1 > max_depth) return;
  const auto subtree1 = proxies1[cut1_idx].node;
  const auto subtree2 = proxies2[cut2_idx].node;
  ReplaceSubtree(root1, subtree2, cut1_idx, proxies1);
  ReplaceSubtree(root2, subtree1, cut2_idx, proxies2);
}

static void MutateRandomCsgTree(
  const std::vector<std::shared_ptr<primitive::SurfacePrimitive>>& primitives,
  const double subtree_prob, const int max_depth,
  const double mutate_prob, const std::vector<CsgNodeProxy>& proxies,
  std::shared_ptr<csg::CsgNode>& root) {
  const double prob = common::GenerateRandomFloat();
  if (prob < mutate_prob) {
    root = GenerateRandomCsgTree(primitives, subtree_prob, max_depth);
  } else {
    // Randomly pick a mutation point.
    const int node_num = static_cast<int>(proxies.size());
    const int idx = common::GenerateRandomInt(0, node_num);
    // Generate a random subtree.
    const std::shared_ptr<csg::CsgNode> subtree =
      GenerateRandomCsgTree(primitives, subtree_prob,
        max_depth - ComputeDistanceToRoot(proxies, idx));
    ReplaceSubtree(root, subtree, idx, proxies);
  }
}

static void EvaluatePointInCsgTree(const Eigen::Matrix3Xd& points,
  const std::shared_ptr<csg::CsgNode>& root, const int idx,
  const std::vector<CsgNodeProxy>& proxies, Eigen::VectorXd& values,
  Eigen::Matrix3Xd& gradients) {
  const int point_num = static_cast<int>(points.cols());
  values = Eigen::VectorXd::Zero(point_num);
  gradients = Eigen::Matrix3Xd::Zero(3, point_num);
  if (root->IsLeaf()) {
    const int prim_id = proxies[idx].primitive_idx;
    values = prim_scores[prim_id];
    gradients = prim_gradients[prim_id];
    return;
  }
  const std::shared_ptr<csg::CsgInternalNode> node =
    std::dynamic_pointer_cast<csg::CsgInternalNode>(root);
  const csg::CsgInternalNodeOperator set_operator =
    node->internal_operator();
  if (set_operator == csg::CsgInternalNodeOperator::kUnion) {
    values.array() = -common::Infinity();
    for (int i = 0; i < node->NumOfChildren(); ++i) {
      const auto& kid = node->children()[i];
      Eigen::VectorXd kid_value;
      Eigen::Matrix3Xd kid_gradient;
      EvaluatePointInCsgTree(points, kid, proxies[idx].children[i],
        proxies, kid_value, kid_gradient);
      const auto choice = (kid_value.array() > values.array());
      values = choice.select(kid_value, values);
      for (int i = 0; i < point_num; ++i) {
        if (choice(i)) gradients.col(i) = kid_gradient.col(i);
      }
    }
  } else if (set_operator == csg::CsgInternalNodeOperator::kIntersection) {
    values.array() = common::Infinity();
    for (int i = 0; i < node->NumOfChildren(); ++i) {
      const auto& kid = node->children()[i];
      Eigen::VectorXd kid_value;
      Eigen::Matrix3Xd kid_gradient;
      EvaluatePointInCsgTree(points, kid, proxies[idx].children[i],
        proxies, kid_value, kid_gradient);
      const auto choice = (kid_value.array() < values.array());
      values = choice.select(kid_value, values);
      for (int i = 0; i < point_num; ++i) {
        if (choice(i)) gradients.col(i) = kid_gradient.col(i);
      }
    }
  } else if (set_operator == csg::CsgInternalNodeOperator::kSubtraction) {
    if (root->NumOfChildren() != 2) {
      common::PrintError("command::EvaluatePointInCsgTree: subtraction should "
        "have only two children.");
    }
    // min(f1, -f2).
    Eigen::VectorXd left_values, right_values;
    Eigen::Matrix3Xd left_grad, right_grad;
    EvaluatePointInCsgTree(points, root->children()[0],
      proxies[idx].children[0], proxies, left_values, left_grad);
    EvaluatePointInCsgTree(points, root->children()[1],
      proxies[idx].children[1], proxies, right_values, right_grad);
    right_values *= -1.0;
    right_grad *= -1.0;
    const auto choice = (left_values.array() < right_values.array());
    values = choice.select(left_values, right_values);
    for (int i = 0; i < point_num; ++i)
      gradients.col(i) = choice(i) ? left_grad.col(i) : right_grad.col(i);
  } else {
    common::PrintError("command::EvaluatePointInCsgTree: invalid operator.");
  }
}

const double ComputeScore(const std::shared_ptr<csg::CsgNode>& root,
  const std::vector<CsgNodeProxy>& proxies,
  const std::vector<std::pair<Eigen::Vector3d, Eigen::Vector3d>>& samples,
  const double eps_d, const double alpha, const double lambda) {
  const int point_num = static_cast<int>(samples.size());
  Eigen::Matrix3Xd points(3, point_num);
  for (int i = 0; i < point_num; ++i)
    points.col(i) = samples[i].first;
  Eigen::VectorXd values;
  Eigen::Matrix3Xd gradients;
  EvaluatePointInCsgTree(points, root, 0, proxies, values, gradients);
  double score = (-values.array().square() / eps_d / eps_d).exp().sum();
  for (int i = 0; i < point_num; ++i) {
    const Eigen::Vector3d normal = samples[i].second;
    const Eigen::Vector3d gradient = gradients.col(i);
    const double cos_n = std::fabs(gradient.norm()) < common::Epsilon() ?
      0.0f : -gradient.dot(normal) / gradient.norm();
    const double theta_c = std::acos(cos_n) / alpha;
    score += std::exp(-theta_c * theta_c);
  }
  score -= lambda * proxies[0].num_of_nodes;
  return score;
}

struct Creature {
public:
  std::shared_ptr<csg::CsgNode> root;
  std::vector<CsgNodeProxy> proxies;
  double score;
};

// The input population should have correct (root, proxies). This function will
// compute score and sort the population.
static void Rank(std::vector<Creature>& population,
  const std::vector<std::pair<Eigen::Vector3d, Eigen::Vector3d>>& samples,
  const double eps_d, const double alpha, const double lambda) {
  // Compute score.
  for (auto& c : population) {
    c.score = ComputeScore(c.root, c.proxies, samples, eps_d, alpha, lambda);
  }
  // Sort: larger c.score are better.
  std::sort(population.begin(), population.end(), [](const Creature& c0,
    const Creature& c1) { return c0.score > c1.score; });
}

static std::vector<int> RunTournamentSelection(
  const std::vector<Creature>& population,
  const int tournament_size, const int tournament_num) {
  std::unordered_set<int> champions(0);
  const int pop_size = static_cast<int>(population.size());
  for (int i = 0; i < tournament_num; ++i) {
    std::unordered_set<int> contestants(0);
    double best_score = common::Infinity();
    int best_idx = -1;
    for (int j = 0; j < tournament_size; ++j) {
      int idx = 0;
      do {
        idx = common::GenerateRandomInt(0, pop_size);
      } while (champions.find(idx) != champions.end() ||
        contestants.find(idx) != contestants.end());
      contestants.insert(idx);
      if (population[idx].score < best_score) {
        best_score = population[idx].score;
        best_idx = idx;
      }
    }
    if (best_idx >= 0 && best_idx < pop_size)
      champions.insert(best_idx);
  }
  return std::vector<int>(champions.begin(), champions.end());
}

static const std::shared_ptr<csg::CsgNode> CopyCsgTree(
  const std::shared_ptr<csg::CsgNode>& root) {
  if (root->IsLeaf()) {
    const int idx = prim_idx[root];
    if (root->type_name() == "cube") {
      const auto node = std::dynamic_pointer_cast<csg::CsgCubeNode>(root);
      const auto node_dup = std::make_shared<csg::CsgCubeNode>(
        node->transform(), node->size());
      prim_idx[node_dup] = idx;
      return node_dup;
    } else if (root->type_name() == "sphere") {
      const auto node = std::dynamic_pointer_cast<csg::CsgSphereNode>(root);
      const auto node_dup = std::make_shared<csg::CsgSphereNode>(
        node->transform(), node->radius(), node->resolution());
      prim_idx[node_dup] = idx;
      return node_dup;
    } else if (root->type_name() == "cylinder") {
      const auto node = std::dynamic_pointer_cast<csg::CsgCylinderNode>(root);
      const auto node_dup = std::make_shared<csg::CsgCylinderNode>(
        node->transform(), node->height(), node->radius(), node->resolution());
      prim_idx[node_dup] = idx;
      return node_dup;
    } else {
      common::PrintError("command::CopyCsgTree: unsupported leaf.");
    }
    // Should never happen.
    return nullptr;
  }
  const std::shared_ptr<csg::CsgInternalNode> node =
    std::dynamic_pointer_cast<csg::CsgInternalNode>(root);
  const csg::CsgInternalNodeOperator choice = node->internal_operator();
  const int num_children = node->NumOfChildren();
  std::shared_ptr<csg::CsgInternalNode> node_dup =
    std::make_shared<csg::CsgInternalNode>(node->children(),
      node->transform(), choice);
  for (int i = 0; i < num_children; ++i) {
    node_dup->set_children(i, CopyCsgTree(node->children()[i]));
  }
  return node_dup;
}

static void PreComputePrimitiveScores(
  const std::vector<std::shared_ptr<primitive::SurfacePrimitive>>& primitives,
  const std::vector<std::pair<Eigen::Vector3d, Eigen::Vector3d>>& samples) {
  const int point_num = static_cast<int>(samples.size());
  Eigen::Matrix3Xd points(3, point_num);
  for (int i = 0; i < point_num; ++i) {
    points.col(i) = samples[i].first;
  }
  const Eigen::VectorXd x2 = points.row(0).array().square(),
    y2 = points.row(1).array().square(),
    z2 = points.row(2).array().square();
  const Eigen::VectorXd s2 = x2 + y2 + z2;
  const int prim_num = static_cast<int>(primitives.size());
  prim_scores.clear();
  prim_gradients.clear();
  prim_scores.reserve(prim_num + 1);
  prim_gradients.reserve(prim_num + 1);
  for (const auto& prim : primitives) {
    Eigen::VectorXd value = Eigen::VectorXd::Zero(point_num);
    Eigen::Matrix3Xd gradient = Eigen::Matrix3Xd::Zero(3, point_num);
    if (prim->type_name() == "plane") {
      const auto plane = std::dynamic_pointer_cast<
        primitive::PlaneSurface>(prim);
      const Eigen::Vector3d n = plane->Normal();
      const double d = plane->Offset();
      // n.dot(p) + d >= 0.
      value = (n.transpose() * points).array() + d;
      gradient.colwise() = n;
    } else if (prim->type_name() == "sphere") {
      const auto sphere = std::dynamic_pointer_cast<
        primitive::SphericalSurface>(prim);
      const Eigen::Vector3d center = sphere->Center();
      const double radius = sphere->Radius();
      const Eigen::Matrix3Xd offsets = points.colwise() - center;
      value = -(offsets.colwise().squaredNorm().array() - radius * radius);
      gradient = -2.0 * offsets;
    } else if (prim->type_name() == "cylinder") {
      const auto cylinder = std::dynamic_pointer_cast<
        primitive::CylindricalSurface>(prim);
      const Eigen::Vector3d center = cylinder->Center();
      const Eigen::Vector3d axis = cylinder->Direction();
      const double radius = cylinder->Radius();
      const Eigen::Quaterniond q = Eigen::Quaterniond::FromTwoVectors(
        Eigen::Vector3d::UnitZ(), axis);
      const Eigen::Matrix4d T = common::RotationAndTranslationToTransform(
        q, center);
      const Eigen::Matrix4d inv_T = common::InverseTransform(T);
      const Eigen::Matrix3Xd local_points = common::TransformPoints(
        inv_T, points);
      value = -(local_points.topRows(2).colwise().squaredNorm().array()
        - radius * radius);
      gradient.topRows(2) = -2.0 * local_points.topRows(2);
      gradient = q.toRotationMatrix() * gradient;
    } else {
      common::PrintError("command::PreComputePrimitiveScores: unsupported "
        "primitives.");
    }
    prim_scores.push_back(value);
    prim_gradients.push_back(gradient);
  }
  // The bounding sphere: centered at the origin, radius = max_bound.
  // r * r - (x * x + y * y + z * z) >= 0.
  Eigen::VectorXd value = -(s2.array() -
    max_bound * max_bound);
  prim_scores.push_back(value);
  prim_gradients.push_back(-2.0 * points);
}

void GeneticCommand(const bool help, const std::string& mesh_file,
  const std::string& prim_file, const std::string output_scad_file,
  const bool verbose) {
  if (help) {
    std::cout
      << "genetic             Implement the genetic algorithm." << std::endl
      << "  -h                Print help information." << std::endl
      << "  -i <OFF file>     Input triangle mesh." << std::endl
      << "  -p <PRIM file>    Input primitive file." << std::endl
      << "  -o <SCAD file>    Output OpenSCAD file." << std::endl
      << "  -v                Verbose mode." << std::endl << std::endl
      << "Implement the genetic algorithm mentioned in paper: An" << std::endl
      << "evolutionary approach to the extraction of object" << std::endl
      << "construction trees from 3D point clouds." << std::endl << std::endl;
    return;
  }
  CheckGeneticCommandFileName(mesh_file, prim_file, output_scad_file);

  // Clear global variables.
  prim_scores.clear();
  prim_gradients.clear();
  prim_idx.clear();

  // Load input mesh and sample points on its surfaces.
  mesh::TriMesh shape;
  shape.Initialize(mesh_file);
  std::vector<std::pair<Eigen::Vector3d, Eigen::Vector3d>> samples(0);
  if (verbose) {
    std::cout << "command::GeneticCommand: beginning sampling..." << std::endl;
  }
  SampleFromTriangleMesh(shape, density, samples);
  const Eigen::Vector3d box_min = shape.box_min(), box_max = shape.box_max();
  eps_d *= (box_max - box_min).norm();
  lambda = std::log(samples.size() * 1.0);

  // Load primitives.
  std::vector<std::shared_ptr<primitive::SurfacePrimitive>> primitives(0);
  common::ReadPrimFile(prim_file, primitives);

  // Pre-compute primitive scores.
  PreComputePrimitiveScores(primitives, samples);

  // Randomly generate initial csg trees.
  if (verbose) {
    std::cout << "command::GeneticCommand: generating initial population."
      << std::endl;
  }
  std::vector<Creature> population;
  population.reserve(population_size);
  for (int i = 0; i < population_size; ++i) {
    const auto root = GenerateRandomCsgTree(primitives, subtree_prob, max_depth);
    std::vector<CsgNodeProxy> proxies(0);
    CreateCsgNodeProxy(root, proxies);
    population.push_back({ root, proxies, 0.0 });
  }
  // Major iteration.
  int iter = 0;
  while (iter < max_iter) {
    // Rank all populations.
    if (verbose) {
      std::cout << "command::GeneticCommand: iter " << iter << std::endl;
      std::cout << "command::GeneticCommand: ranking..." << std::endl;
    }
    Rank(population, samples, eps_d, alpha, lambda);
    Eigen::VectorXd scores(population_size);
    for (int i = 0; i < population_size; ++i)
      scores(i) = population[i].score;
    common::WriteMatrixToBinaryFile(scores, "scores_" + std::to_string(iter));
    if (verbose) {
      std::cout << "command::GeneticCommand: scores:" << std::endl;
      for (int i = 0; i < 10; ++i) {
        std::cout << population[i].score << ", node number = "
          << population[i].proxies[0].num_of_nodes << ", tree depth = "
          << population[i].proxies[0].depth << std::endl;
      }
    }
    auto population_prime = population;
    // Keeps only the first n candidates.
    if (n < static_cast<int>(population_prime.size()))
      population_prime.resize(n);
    while (static_cast<int>(population_prime.size()) <= population_size) {
      // Select c1 and c2.
      const std::vector<int> c_n = RunTournamentSelection(population,
        static_cast<int>(population.size()) / 2, 2);
      Creature c1 = population.at(c_n.at(0)), c2 = population.at(c_n.at(1));
      c1.root = CopyCsgTree(c1.root);
      CreateCsgNodeProxy(c1.root, c1.proxies);
      c2.root = CopyCsgTree(c2.root);
      CreateCsgNodeProxy(c2.root, c2.proxies);
      // Crossover.
      CrossOverCsgTrees(c1.root, c1.proxies, c2.root, c2.proxies,
        max_depth, crossover_rate);
      // Update proxies.
      CreateCsgNodeProxy(c1.root, c1.proxies);
      CreateCsgNodeProxy(c2.root, c2.proxies);
      // Mutate.
      MutateRandomCsgTree(primitives, subtree_prob, max_depth,
        mutation_rate, c1.proxies, c1.root);
      CreateCsgNodeProxy(c1.root, c1.proxies);
      MutateRandomCsgTree(primitives, subtree_prob, max_depth,
        mutation_rate, c2.proxies, c2.root);
      CreateCsgNodeProxy(c2.root, c2.proxies);
      // Append.
      population_prime.push_back(c1);
      population_prime.push_back(c2);
    }
    population = population_prime;
    ++iter;
  }
  // Pick the best one and write it back to the scad file.
  Rank(population, samples, eps_d, alpha, lambda);
  common::WriteScadFile(population[0].root, output_scad_file);
}

}
