#ifndef _COMMAND_COMMAND_H_
#define _COMMAND_COMMAND_H_

#include <string>
#include "Eigen/Dense"

namespace command {

void AddSeparatorCommand(const std::string& aux_prim_file,
  const double min_dist, const bool help, const std::string& init_prim_file,
  const std::string& neg_data_file, const std::string& output_prim_file,
  const std::string& pos_data_file, const bool verbose);
void BhcCommand(const bool help, const std::string& input_prim_file,
  const std::string& neg_data_file, const std::string& output_scad_file,
  const std::string& pos_data_file, const bool verbose);
void CleanCsgCommand(const double epsilon, const bool help,
  const std::string& input_scad_file, const std::string& output_scad_file,
  const bool verbose);
void CsgFlagCommand(const std::string& input_data_file,
  const double min_dist, const bool help, const std::string& scad_file,
  const std::string& output_negative_data_file,
  const std::string& output_positive_data_file,
  const bool verbose);
void CsgMeshDiffCommand(const double grid_size, const bool help,
  const std::string& scad_file, const std::string& mesh_file,
  const bool verbose);
void EquivClassCommand(const double min_dist, const bool help,
  const std::string& input_data_file, const std::string& prim_file,
  const std::string& output_data_file, const bool verbose);
void EquivClassFlagCommand(const double min_dist,
  const std::string& pos_equiv_file, const bool help,
  const std::string& input_data_file, const std::string& level_set_file,
  const std::string& mesh_file, const std::string& neg_file,
  const std::string& pos_file, const std::string& prim_file,
  const std::string& neg_equiv_file, const bool verbose);
void GeneticCommand(const bool help, const std::string& mesh_file,
  const std::string& prim_file, const std::string output_scad_file,
  const bool verbose);
void HausdorffCommand(const std::string& input_mesh,
  const std::string& target_mesh, const double density,
  const bool help, const bool verbose);
void LegacySketchTreeCommand(const bool help,
  const std::string& input_scad_file, const std::string& output_txt_file,
  const bool verbose);
void LevelSetCommand(const bool help, const std::string& mesh_file,
  const double grid_size, const std::string& level_set_file,
  const bool verbose);
void MeshFlagCommand(const std::string& input_data_file,
  const double min_dist, const bool help, const std::string& mesh_file,
  const std::string& level_set_file,
  const std::string& output_negative_data_file,
  const std::string& output_positive_data_file,
  const bool verbose);
void PrimitiveCommand(const std::string& config_file, const bool help,
  const std::string& mesh_file, const std::string& cluster_file,
  const std::string& meta_file, const std::string& primitive_file,
  const bool verbose);
void PrimitiveLocalCommand(const bool help, const std::string& meta_file,
  const std::string& output_primitive_file,
  const std::string& input_primitive_file, const Eigen::Vector3d& pmin,
  const Eigen::Vector3d& pmax, const bool verbose);
void RansacCommand(const double cluster_epsilon, const double density,
  const double epsilon, const bool help, const std::string& mesh_file,
  const std::string& cluster_file, const int min_point,
  const double normal_threshold, const std::string& primitive_file,
  const double probability, const bool verbose);
void RemoveEquivClassCommand(const double min_dist, const bool help,
  const std::string& input_data_file, const std::string& output_data_file,
  const std::string& prim_file, const std::string& subtract_data_file,
  const bool verbose);
void RemovePrimCommand(const double min_dist, const bool help,
  const std::string& input_prim_file, const std::string& input_neg_data_file,
  const std::string& output_prim_file, const std::string& input_pos_data_file,
  const bool verbose);
void SurfaceSampleCommand(const double max_dist, const double density,
  const double min_dist, const bool help, const std::string& mesh_file,
  const std::string& level_set_file, const std::string& output_data_file,
  const std::string& primitive_file, const bool verbose);
void TraverseTreeCommand(const bool help, const std::string& scad_file,
  const std::string& output_folder, const bool verbose);
void TreeInfoCommand(const bool help, const std::string& scad_file);
void VolumeSampleCommand(const double density, const double min_dist,
  const bool help, const std::string& mesh_file,
  const std::string& level_set_file, const std::string& neg_data_file,
  const std::string& pos_data_file, const std::string& prim_file,
  const bool verbose);

}

#endif
