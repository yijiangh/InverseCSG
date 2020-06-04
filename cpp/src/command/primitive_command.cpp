#include "command/command.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cmath>
#include <unordered_set>
#include "GCoptimization.h"
#include "common/file_helper.h"
#include "common/math_helper.h"
#include "mesh/tri_mesh.h"
#include "primitive/surface_primitive.h"
#include "primitive/plane_surface.h"
#include "primitive/spherical_surface.h"
#include "primitive/cylindrical_surface.h"
#include "primitive/toric_surface.h"
#include "primitive/conical_surface.h"
#include "ransac/cgal_ransac_wrapper.h"

namespace command {

typedef std::shared_ptr<primitive::SurfacePrimitive> Primitive;

static void CheckPrimitiveCommandFileName(const std::string& config_file,
  const std::string& mesh_file, const std::string& cluster_file,
  const std::string& meta_file, const std::string& primitive_file) {
  if (!common::HasExtension(config_file, ".conf")) {
    std::cerr << common::RedHead()
      << "command::PrimitiveCommand: wrong config file: " << config_file
      << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(mesh_file, ".off")) {
    std::cerr << common::RedHead()
      << "command::PrimitiveCommand: wrong mesh file: " << mesh_file
      << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(cluster_file, ".clu")) {
    std::cerr << common::RedHead()
      << "command::PrimitiveCommand: wrong cluster file: " << cluster_file
      << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(meta_file, ".meta")) {
    std::cerr << common::RedHead()
      << "command::PrimitiveCommand: wrong meta file: " << meta_file
      << common::RedTail() << std::endl;
    exit(-1);
  }
  if (!common::HasExtension(primitive_file, ".prim")) {
    std::cerr << common::RedHead()
      << "command::PrimitiveCommand: wrong primitive file: "
      << primitive_file << common::RedTail() << std::endl;
      exit(-1);
  }
}

static void CheckPartition(const std::vector<std::vector<int>>& clusters,
  const int face_num) {
  std::string visited(face_num, '0');
  for (const auto& c : clusters) {
    for (const int idx : c) {
      if (idx < 0 || idx >= face_num) {
        std::ostringstream ss;
        ss << "command::CheckPartition: not a partition: " << idx
          << " out of bounds.";
        common::PrintError(ss.str());
      }
      if (visited[idx] == '1') {
        std::ostringstream ss;
        ss << "command::CheckPartition: not a partition: see " << idx
          << " twice.";
        common::PrintError(ss.str());
      }
      visited[idx] = '1';
    }
  }
  const auto pos = visited.find_first_of('0');
  if (pos != std::string::npos) {
    std::ostringstream ss;
    ss << "command::CheckPartition: not a partition: " << pos
      << " untouched.";
    common::PrintError(ss.str());
  }
}

// Here max_diam does not affect the results but will be used to sanity check
// the results.
static const std::vector<Primitive> MergeCandidatePrimitives(
  const std::vector<std::vector<Primitive>>& all_candidates,
  const double max_diam) {
  std::vector<Primitive> all_primitives;
  for (const auto& candidates : all_candidates) {
    const int candidate_num = static_cast<int>(candidates.size());
    Primitive new_prim = nullptr;
    const std::string type_name = candidates[0]->type_name();
    if (type_name == "plane") {
      Eigen::Vector3d normal = Eigen::Vector3d::Zero();
      double offset = 0;
      for (const auto& c : candidates) {
        const auto plane = std::dynamic_pointer_cast<
          primitive::PlaneSurface>(c);
        normal += plane->Normal();
        offset += plane->Offset();
      }
      normal /= candidate_num;
      offset /= candidate_num;
      new_prim = std::make_shared<primitive::PlaneSurface>(normal, offset);
    } else if (type_name == "sphere") {
      Eigen::Vector3d center = Eigen::Vector3d::Zero();
      double radius = 0.0;
      for (const auto& c : candidates) {
        const auto sphere = std::dynamic_pointer_cast<
          primitive::SphericalSurface>(c);
        center += sphere->Center();
        radius += sphere->Radius();
      }
      center /= candidate_num;
      radius /= candidate_num;
      new_prim = std::make_shared<primitive::SphericalSurface>(center, radius);
    } else if (type_name == "cylinder") {
      Eigen::Vector3d center = Eigen::Vector3d::Zero();
      Eigen::Vector3d dir = Eigen::Vector3d::Zero();
      double radius = 0.0;
      for (const auto& c : candidates) {
        const auto cylinder = std::dynamic_pointer_cast<
          primitive::CylindricalSurface>(c);
        center += cylinder->Center();
        dir += cylinder->Direction();
        radius += cylinder->Radius();
      }
      center /= candidate_num;
      dir /= candidate_num;
      radius /= candidate_num;
      new_prim = std::make_shared<primitive::CylindricalSurface>(center, dir,
        radius);
    } else if (type_name == "torus") {
      Eigen::Vector3d center = Eigen::Vector3d::Zero();
      Eigen::Vector3d axis = Eigen::Vector3d::Zero();
      double major_radii = 0.0, minor_radii = 0.0;
      for (const auto& c : candidates) {
        const auto torus = std::dynamic_pointer_cast<
          primitive::ToricSurface>(c);
        center += torus->Center();
        axis += torus->Axis();
        major_radii += torus->MajorRadii();
        minor_radii += torus->MinorRadii();
      }
      center /= candidate_num;
      axis /= candidate_num;
      major_radii /= candidate_num;
      minor_radii /= candidate_num;
      new_prim = std::make_shared<primitive::ToricSurface>(center, axis,
        major_radii, minor_radii);
    } else if (type_name == "cone") {
      Eigen::Vector3d apex = Eigen::Vector3d::Zero();
      Eigen::Vector3d axis = Eigen::Vector3d::Zero();
      double angle = 0.0;
      for (const auto& c : candidates) {
        const auto cone = std::dynamic_pointer_cast<
          primitive::ConicalSurface>(c);
        apex += cone->Apex();
        axis += cone->Axis();
        angle += cone->Angle();
      }
      apex /= candidate_num;
      axis /= candidate_num;
      angle /= candidate_num;
      new_prim = std::make_shared<primitive::ConicalSurface>(apex, axis, angle);
    } else {
      std::ostringstream ss;
      ss << "command::PrimitiveCommand: invalid primitive type: " << type_name;
      common::PrintError(ss.str());
    }
    all_primitives.push_back(new_prim);
  }
  return all_primitives;
}

static void VisualizePrimitivesInScad(const std::vector<Primitive>& primitives,
  const std::string& mesh_file, const std::string& scad_file) {
  // Generate an OpenSCAD file to visualize all primitives.
  std::ofstream scad_fout(scad_file);
  scad_fout << "union() {" << std::endl;
  // Include the mesh.
  scad_fout << "import(\"" << mesh_file << "\");" << std::endl;
  for (const auto& p : primitives) {
    const std::string type_name = p->type_name();
    if (type_name == "plane") {
      scad_fout << "// " << p->WriteToString() << std::endl;
      auto plane = std::dynamic_pointer_cast<primitive::PlaneSurface>(p);
      const Eigen::Vector3d normal = plane->Normal();
      const double offset = plane->Offset();
      const Eigen::Vector3d center = -offset * normal;
      scad_fout << "translate([" << center.x() << ", " << center.y() << ", "
        << center.z() << "])" << std::endl;
      const Eigen::Matrix3d R = Eigen::Quaterniond::FromTwoVectors(
        Eigen::Vector3d::UnitZ(), normal).matrix();
      const Eigen::Vector3d rpy = common::RotationToRollPitchYaw(R);
      const double roll = common::RadianToDegree(rpy.x()),
        pitch = common::RadianToDegree(rpy.y()),
        yaw = common::RadianToDegree(rpy.z());
      scad_fout << "rotate([" << roll << ", " << pitch << ", " << yaw << "])"
        << std::endl;
      scad_fout << "cube(size = [15.0, 15.0, 0.01], center = true);"
        << std::endl;
    } else if (type_name == "sphere") {
      scad_fout << "// " << p->WriteToString() << std::endl;
      auto sphere = std::dynamic_pointer_cast<primitive::SphericalSurface>(p);
      const Eigen::Vector3d center = sphere->Center();
      const double radius = sphere->Radius();
      scad_fout << "translate([" << center.x() << ", " << center.y() << ", "
        << center.z() << "])" << std::endl;
      scad_fout << "sphere(r = " << radius << ", center = true, "
        << "$fn = 12);" << std::endl;
    } else if (type_name == "cylinder") {
      scad_fout << "// " << p->WriteToString() << std::endl;
      auto cylinder = std::dynamic_pointer_cast<
        primitive::CylindricalSurface>(p);
      const Eigen::Vector3d center = cylinder->Center();
      const Eigen::Vector3d dir = cylinder->Direction();
      const double radius = cylinder->Radius();
      scad_fout << "translate([" << center.x() << ", " << center.y() << ", "
        << center.z() << "])" << std::endl;
      const Eigen::Matrix3d R = Eigen::Quaterniond::FromTwoVectors(
        Eigen::Vector3d::UnitZ(), dir).matrix();
      const Eigen::Vector3d rpy = common::RotationToRollPitchYaw(R);
      const double roll = common::RadianToDegree(rpy.x()),
        pitch = common::RadianToDegree(rpy.y()),
        yaw = common::RadianToDegree(rpy.z());
      scad_fout << "rotate([" << roll << ", " << pitch << ", " << yaw << "])"
        << std::endl;
      scad_fout << "cylinder(h = 15, r1 = " << radius << ", r2 = " << radius
        << ", center = true, $fn = 12);" << std::endl;
    } else if (type_name == "torus") {
      scad_fout << "// " << p->WriteToString() << std::endl;
      auto torus = std::dynamic_pointer_cast<primitive::ToricSurface>(p);
      const Eigen::Vector3d center = torus->Center();
      scad_fout << "translate([" << center.x() << ", " << center.y() << ", "
        << center.z() << "])" << std::endl;
      const Eigen::Vector3d axis = torus->Axis();
      const Eigen::Matrix3d R = Eigen::Quaterniond::FromTwoVectors(
        Eigen::Vector3d::UnitZ(), axis).matrix();
      const Eigen::Vector3d rpy = common::RotationToRollPitchYaw(R);
      const double roll = common::RadianToDegree(rpy.x()),
        pitch = common::RadianToDegree(rpy.y()),
        yaw = common::RadianToDegree(rpy.z());
      scad_fout << "rotate([" << roll << ", " << pitch << ", " << yaw << "])"
        << std::endl;
      scad_fout << "rotate_extrude($fn = 12)" << std::endl;
      const double major_radii = torus->MajorRadii();
      scad_fout << "translate([" << major_radii << ", 0, 0])" << std::endl;
      const double minor_radii = torus->MinorRadii();
      scad_fout << "circle(r = " << minor_radii << ", $fn = 12);" << std::endl;
    } else if (type_name == "cone") {
      scad_fout << "// " << p->WriteToString() << std::endl;
      auto cone = std::dynamic_pointer_cast<primitive::ConicalSurface>(p);
      const Eigen::Vector3d apex = cone->Apex();
      const Eigen::Vector3d axis = cone->Axis();
      const double angle = cone->Angle();
      const double height = 20.0;
      const double radius = std::tan(angle) * height;
      scad_fout << "translate([" << apex.x() << ", " << apex.y() << ", "
        << apex.z() << "])" << std::endl;
      const Eigen::Matrix3d R = Eigen::Quaterniond::FromTwoVectors(
        -Eigen::Vector3d::UnitZ(), axis).matrix();
      const Eigen::Vector3d rpy = common::RotationToRollPitchYaw(R);
      const double roll = common::RadianToDegree(rpy.x()),
        pitch = common::RadianToDegree(rpy.y()),
        yaw = common::RadianToDegree(rpy.z());
      scad_fout << "rotate([" << roll << ", " << pitch << ", " << yaw << "])"
        << std::endl;
      scad_fout << "translate([0.0, 0.0, " << -height * 0.5
        << "])" << std::endl;
      scad_fout << "cylinder(h = " << height << ", r1 = " << radius
        << ", r2 = 0.0, center = true, $fn = 12);" << std::endl;
    } else {
      std::ostringstream ss;
      ss << "command::PrimitiveCommand: unsupported primitive type: "
        << type_name;
      common::PrintError(ss.str());
    }
  }
  scad_fout << "}" << std::endl;
  scad_fout.close();
}

static const double FaceToPrimitiveEnergy(const ransac::CgalRansacWrapper& wrapper,
  const int face_id, const Primitive& primitive) {
  double energy = 0.0;
  const std::vector<int>& points = wrapper.face_to_points(face_id);
  if (points.empty()) return energy;
  for (const int pid : points) {
    const Eigen::Vector3d point = wrapper.point(pid);
    const double dist = std::fabs(primitive->DistToSurface(point));
    energy += dist;
  }
  energy /= static_cast<int>(points.size());
  energy *= wrapper.shape().area(face_id);
  return energy;
}

void PrimitiveCommand(const std::string& config_file, const bool help,
  const std::string& mesh_file, const std::string& cluster_file,
  const std::string& meta_file, const std::string& primitive_file,
  const bool verbose) {
  if (help) {
    std::cout
      << "primitive           Detect all primitives." << std::endl
      << "  -c <CONF file>    Configuration file." << std::endl
      << "  -h                Print help information." << std::endl
      << "  -i <OFF file>     Input triangle mesh." << std::endl
      << "  -l <CLU file>     Output cluster file." << std::endl
      << "  -m <META file>    Output primitive metadata file." << std::endl
      << "  -o <PRIM file>    Output primitive file." << std::endl
      << "  -v                Verbose mode." << std::endl << std::endl
      << "Given a triangle mesh, detect all surface primitives." << std::endl
      << "The detected primitives are stored in a primitive file," << std::endl
      << "and all the sample points used in the detection are" << std::endl
      << "written into a meta file. Each point in the meta file" << std::endl
      << "is associated with an index to the primitive that can" << std::endl
      << "best fit this point." << std::endl << std::endl;
    std::cout
      << "We may support different methods in this command in the" << std::endl
      << "future. As a result, we accept a configuration file to" << std::endl
      << "read method-dependent parameters instead of putting" << std::endl
      << "them in the command line." << std::endl << std::endl;
    return;
  }
  // Sanity check.
  CheckPrimitiveCommandFileName(config_file, mesh_file, cluster_file,
    meta_file, primitive_file);
  const std::string debug_folder = common::GetParentFolder(primitive_file);

  // The algorithm looks like this: we call RANSAC multiple times with various
  // combinations of parameters. In this way we collect a list of candidates for
  // every face. Next, we clean up all candidates by merging close primitives.
  // Finally, we run graph-cut to select a subset of candidates that covers all
  // faces.

  //////////////////////////////////////////////////////////////////////////////
  // Configuration.
  //////////////////////////////////////////////////////////////////////////////
  // Plan to collect target_sample_num samples.
  std::map<std::string, std::string> kv_pairs;
  common::ReadConfFile(config_file, kv_pairs);
  const int target_sample_num = std::stoi(kv_pairs.at("target_sample_num"));
  // Below are the default RANSAC parameters.
  const double probability = std::stod(kv_pairs.at("probability"));
  const int min_points = std::stoi(kv_pairs.at("min_points"));
  const double epsilon = std::stod(kv_pairs.at("epsilon"));
  const double cluster_epsilon = std::stod(kv_pairs.at("cluster_epsilon"));
  const double normal_threshold = std::stod(kv_pairs.at("normal_threshold"));
  // Optional parameter.
  const double epsilon_cutoff =
    kv_pairs.find("epsilon_cutoff") == kv_pairs.end() ? epsilon
    : std::stod(kv_pairs.at("epsilon_cutoff"));
  // Max RANSAC iterations.
  const int max_iter = std::stoi(kv_pairs.at("max_iter"));
  // Use this value to merge close primitives.
  const double max_diam = std::stod(kv_pairs.at("max_diam"));
  // Max graph-cut iterations.
  const int gc_max_iter = std::stoi(kv_pairs.at("gc_max_iter"));
  // Used to randomize the parameters.
  const double base = std::stod(kv_pairs.at("base"));
  // Used to define the smooth cost in graph-cut.
  const double smooth_cost = std::stod(kv_pairs.at("smooth_cost"));
  // Used to define the label cost in graph-cut.
  const double label_cost = std::stod(kv_pairs.at("label_cost"));

  mesh::TriMesh shape;
  shape.Initialize(mesh_file);
  ransac::CgalRansacWrapper wrapper(shape);
  double area = 0.0;
  const int face_num = shape.NumOfFaces();
  for (int i = 0; i < face_num; ++i) {
    area += shape.area(i);
  }
  // Intentionally use 1.1 here to collect slightly more samples.
  const double density = target_sample_num * 1.1 / area;
  wrapper.BuildPointSamples(density);
  // How good are they?
  double uncovered_area = 0.0;
  for (int i = 0; i < face_num; ++i) {
    if (wrapper.face_to_points(i).empty()) uncovered_area += shape.area(i);
  }
  const double uncovered_rate = uncovered_area / area;
  // Send a warning if 5% are uncovered.
  std::ostringstream ss;
  ss << "command::PrimitiveCommand: " << uncovered_rate * 100.0 << "% of the"
    " area is uncovered.";
  if (uncovered_rate > 0.05) {
    common::PrintWarning(ss.str());
  }
  // Terminate if 10% are uncovered.
  if (uncovered_rate > 0.1) {
    common::PrintError(ss.str());
  }
  if (verbose) {
    std::cout << "command::RansacCommand: sampling " << wrapper.NumOfSamples()
      << " points. " << ss.str() << std::endl;
  }

  //////////////////////////////////////////////////////////////////////////////
  // RANSAC.
  //////////////////////////////////////////////////////////////////////////////
  std::vector<std::vector<Primitive>> all_candidates(0);
  std::vector<std::set<int>> all_face_to_primitive(face_num);
  for (int iter = 0; iter < max_iter; ++iter) {
    if (verbose) {
      std::cout << "command::RansacCommand: RANSAC iter " << iter << std::endl;
    }
    // Now run RANSAC with randomly perturbed parameters. Here we randomly
    // pick parameters that are in the range of default / base to default
    // * base.
    const Eigen::VectorXd rand_seed = Eigen::VectorXd::Random(5);
    double prob_iter = std::pow(base, rand_seed(0)) * probability;
    // Clamp prob_iter.
    prob_iter = std::min(std::max(prob_iter, 0.0), 1.0);
    const int min_points_iter = static_cast<int>(
      std::pow(base, rand_seed(1)) * min_points);
    const double epsilon_iter = std::pow(base, rand_seed(2)) * epsilon;
    const double cluster_epsilon_iter = std::pow(base, rand_seed(3))
      * cluster_epsilon;
    double normal_threshold_iter = std::pow(base, rand_seed(4))
      * normal_threshold;
    // Clamp normal_threshold to (0, 1).
    normal_threshold_iter = std::min(std::max(normal_threshold_iter, 0.0), 1.0);
    // Now call RANSAC.
    std::vector<Primitive> primitives;
    std::vector<std::vector<int>> face_to_primitive;
    if (verbose) {
      std::cout << "command::RansacCommand: RANSAC parameters: probabilty = "
        << prob_iter << ", min_points = " << min_points_iter << ", epsilon = "
        << epsilon_iter << ", cluster_epsilon = " << cluster_epsilon_iter
        << ", normal_threshold = " << normal_threshold_iter << std::endl;
    }
    wrapper.RunRansac(prob_iter, min_points_iter, epsilon_iter,
      cluster_epsilon_iter, normal_threshold_iter, primitives,
      face_to_primitive);
    if (verbose) {
      std::cout << "command::RansacCommand: " << primitives.size()
        << " primitives:" << std::endl;
      for (const auto& p : primitives) {
        std::cout << p->WriteToString() << std::endl;
      }
    }
    // Attempt to merge new primitives.
    // prim_to_cand[i] maps the i-th primitive in primitives to all_candidates.
    std::map<int, int> prim_to_cand;
    const int prim_num = static_cast<int>(primitives.size());
    for (int i = 0; i < prim_num; ++i) {
      const Primitive& p = primitives[i];
      bool is_new = true;
      const int cand_num = static_cast<int>(all_candidates.size());
      for (int j = 0; j < cand_num; ++j) {
        if (p->type_name() != all_candidates[j][0]->type_name()) continue;
        // See if p is close to all primitives in all_candidates[j].
        bool all_close = true;
        for (const auto& c : all_candidates[j]) {
          // Compare p and c.
          const Eigen::VectorXd diff_param =
            (p->parameters() - c->parameters()).cwiseAbs();
          const double diff = diff_param.maxCoeff();
          if (diff > max_diam) {
            all_close = false;
            break;
          }
        }
        if (all_close) {
          // p belongs to this cluster.
          is_new = false;
          all_candidates[j].push_back(p);
          prim_to_cand[i] = j;
          break;
        }
      }
      if (is_new) {
        // Create a new cluster.
        prim_to_cand[i] = cand_num;
        all_candidates.push_back({ p });
      }
    }
    // Update face_to_primitive.
    for (int i = 0; i < face_num; ++i) {
      for (const int pid : face_to_primitive[i]) {
        all_face_to_primitive[i].insert(prim_to_cand.at(pid));
      }
    }
  }
  if (verbose) {
    // See how many faces are unclaimed.
    int unclaimed_face_cnt = 0;
    double unclaimed_area = 0.0;
    for (int i = 0; i < face_num; ++i) {
      if (all_face_to_primitive[i].empty()) {
        ++unclaimed_face_cnt;
        unclaimed_area += shape.area(i);
      }
    }
    std::ostringstream ss;
    ss << "command::PrimitiveCommand: " << unclaimed_face_cnt << " faces"
      << " are uncovered (" << unclaimed_area * 100.0 / area << "% of the "
      << "area).";
    std::cout << ss.str() << std::endl;
  }
  // Now merge non-singleton elements in all_candidates.
  const std::vector<Primitive> all_primitives = MergeCandidatePrimitives(
    all_candidates, max_diam);
  // Print all primitives and all face to candidates.
  if (verbose) {
    std::cout << "command::PrimitiveCommand: all primitives after merging:"
      << std::endl;
    for (const auto& p : all_primitives) {
      std::cout << p->WriteToString() << std::endl;
    }
    const std::string scad_file = common::AppendFileToPath(debug_folder,
      "all_primitives.scad");
    VisualizePrimitivesInScad(all_primitives, mesh_file, scad_file);
  }
  // Add primitives to triangles that are close to it. Here we use the maximal
  // possible epsilon.
  const int all_primitive_num = static_cast<int>(all_primitives.size());
  for (int i = 0; i < all_primitive_num; ++i) {
    const auto& prim = all_primitives[i];
    for (int j = 0; j < face_num; ++j) {
      auto& cands = all_face_to_primitive[j];
      if (cands.find(i) != cands.end()) continue;
      const double energy = FaceToPrimitiveEnergy(wrapper, j, prim);
      if (energy <= epsilon_cutoff * shape.area(j)) cands.insert(i);
    }
  }

  //////////////////////////////////////////////////////////////////////////////
  // Graph-cut.
  //////////////////////////////////////////////////////////////////////////////
  // Construct our problem:
  // Nodes: each face.
  // Edges: each pair of adjacent faces. Don't plan to use it now.
  // Labels: all_candidates.
  // Data cost: D_p(l_p): distance of the face to the candidate.
  // Smooth cost: 0.
  // Label cost: has to be some big number so that it has incentive to use fewer
  // candidates, but not too big to converge to a trivial solution.

  // First, let's initialize the sparse cost.
  const int label_num = all_primitive_num;
  std::vector<std::vector<GCoptimization::SparseDataCost>>
    costs_for_label(label_num);
  // For unassigned faces, check all primitives and select the candidates.
  // Remember that epsilon defines the distance from a point to a surface. If
  // the energy <= epsilon * area then we should include it as a candidate.
  for (int i = 0; i < face_num; ++i) {
    if (!all_face_to_primitive[i].empty()) continue;
    std::vector<double> all_energies;
    double min_energy = common::Infinity();
    for (const auto& p : all_primitives) {
      const double energy = FaceToPrimitiveEnergy(wrapper, i, p);
      all_energies.push_back(energy);
      if (energy < min_energy) min_energy = energy;
    }
    double energy_cutoff = epsilon * shape.area(i);
    // If all primitives are bad, we will allow all primitives and rely on the
    // smooth energy to select the best one.
    if (min_energy > energy_cutoff) energy_cutoff = common::Infinity();
    for (int j = 0; j < all_primitive_num; ++j)
      if (all_energies[j] <= energy_cutoff)
        all_face_to_primitive[i].insert(j);
    // At this point it should never be empty.
    if (all_face_to_primitive[i].empty()) {
      common::PrintError("command::PrimitiveCommand: expect to see a non "
        "empty set of primitives for each face.");
    }
  }
  // Collect some statistics.
  double min_cost = common::Infinity();
  double max_cost = -common::Infinity();
  double average_cost = 0.0;
  int total_cost_num = 0;
  for (int i = 0; i < face_num; ++i) {
    for (const int idx : all_face_to_primitive[i]) {
      // Face i can use label idx.
      GCoptimization::SparseDataCost cost;
      cost.site = i;
      cost.cost = FaceToPrimitiveEnergy(wrapper, i, all_primitives[idx]);
      if (cost.cost < min_cost) min_cost = cost.cost;
      if (cost.cost > max_cost) max_cost = cost.cost;
      average_cost += cost.cost;
      ++total_cost_num;
      costs_for_label[idx].push_back(cost);
    }
  }
  average_cost /= total_cost_num;
  if (verbose) {
    std::cout << "command::PrimitiveCommand: min data cost = " << min_cost
      << ", max data cost = " << max_cost
      << ", average data cost = " << average_cost << std::endl;
  }

  // Second, let's define the smooth energy.
  std::vector<double> smooth_energies(label_num * label_num);
  for (int i = 0; i < label_num; ++i)
    for (int j = 0; j < label_num; ++j)
      smooth_energies[i + j * label_num] = (i == j) ? 0 : smooth_cost;

  // Copied from example.cpp in gco.
  try {
    GCoptimizationGeneralGraph* gc = new GCoptimizationGeneralGraph(
      face_num, label_num);
    for (int i = 0; i < label_num; ++i) {
      const int cnt = static_cast<int>(costs_for_label[i].size());
      gc->setDataCost(i, costs_for_label[i].data(), cnt);
    }
    gc->setSmoothCost(smooth_energies.data());
    // Set label cost term.
    gc->setLabelCost(label_cost);
    // Set the graph structure.
    for (int i = 0; i < face_num; ++i) {
      for (const int j : shape.face_neighbor(i)) {
        if (i < j) {
          gc->setNeighbors(i, j);
        }
      }
    }

    // Optimization.
    if (verbose) {
      std::cout << "command::PrimitiveCommand: graph cut energy before "
        "optimization: " << gc->compute_energy() << std::endl;
    }
    gc->expansion(gc_max_iter);
    if (verbose) {
      std::cout << "command::PrimitiveCommand: graph cut energy after "
        "optimization: " << gc->compute_energy() << std::endl;
    }

    // Get results.
    std::vector<std::vector<int>> clusters(label_num);
    for (int i = 0; i < face_num; ++i) {
      const int label = gc->whatLabel(i);
      clusters[label].push_back(i);
    }
    std::vector<std::vector<int>> active_clusters(0);
    for (int i = 0; i < label_num; ++i) {
      if (!clusters[i].empty()) active_clusters.push_back(clusters[i]);
    }
    // Save cluster file.
    common::WriteClusterFile(active_clusters, cluster_file);
    // Save primitives.
    std::vector<Primitive> active_primitives(0);
    for (int i = 0; i < label_num; ++i) {
      if (!clusters[i].empty()) active_primitives.push_back(all_primitives[i]);
    }
    common::WritePrimFile(active_primitives, primitive_file);
    // Save meta files.
    const int sample_num = wrapper.NumOfSamples();
    std::vector<std::pair<Eigen::Vector3d, int>> meta_points(sample_num,
      std::make_pair(Eigen::Vector3d::Zero(), -1));
    const int cluster_num = static_cast<int>(active_clusters.size());
    for (int i = 0; i < cluster_num; ++i) {
      for (const int fid : active_clusters[i]) {
        for (const int pid : wrapper.face_to_points(fid)) {
          meta_points.at(pid).first = wrapper.point(pid);
          meta_points.at(pid).second = i;
        }
      }
    }
    // Sanity check.
    for (const auto& p : meta_points) {
      if (p.second == -1) {
        common::PrintError("command::PrimitiveCommand: unclaimed meta points.");
      }
    }
    common::WriteMetaFile(meta_points, meta_file);
    if (verbose) {
      // Print the final clusters.
      const std::string name = common::AppendFileToPath(debug_folder, "result");
      common::VisualizeMeshSegmentation(shape, active_clusters, name, true);
      std::cout << "command::PrimitiveCommand: final clusters:" << std::endl;
      int cnt = 0;
      for (const auto& cluster : active_clusters) {
        std::cout << "Cluster " << cnt << ":";
        for (const int idx : cluster) {
          std::cout << " " << idx;
        }
        std::cout << std::endl;
        ++cnt;
      }
      // Print the active primitives.
      std::cout << "command::PrimitiveCommand: final primitives ("
        << active_primitives.size() << "):" << std::endl;
      cnt = 0;
      for (const auto& p : active_primitives) {
        std::cout << "Primitive " << cnt << ": "
          << p->WriteToString() << std::endl;
        ++cnt;
      }
      const std::string scad_file = common::AppendFileToPath(debug_folder,
        "active_primitives.scad");
      VisualizePrimitivesInScad(active_primitives, mesh_file, scad_file);
    }
    delete gc;
  } catch (GCException e) {
    std::cerr << common::RedHead() << "command::PrimitiveCommand: graph cut "
      "failed." << common::RedTail() << std::endl;
    e.Report();
    exit(-1);
  }
}

}
