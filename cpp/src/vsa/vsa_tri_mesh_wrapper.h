#ifndef _VSA_VSA_TRI_MESH_WRAPPER_H_
#define _VSA_VSA_TRI_MESH_WRAPPER_H_

// See paper "Variational mesh segmentation via quadric surface fitting"
// Dong-Ming Yan, Wenping Wang, Yang Liu, Zhuowang Yang
// Computer-Aided Design

#include <map>
#include "mesh/tri_mesh.h"

namespace vsa {

class VsaTriMeshWrapper {
public:
  VsaTriMeshWrapper(const mesh::TriMesh& shape);

  const mesh::TriMesh& shape() const;

  const Eigen::VectorXd integrals(const int x_deg, const int y_deg,
    const int z_deg) const;
  const Eigen::MatrixXd l2_matrix(const int idx) const;
  const Eigen::MatrixXd l21_matrix(const int idx) const;
  const Eigen::VectorXd grad_norm_vector(const int idx) const;

  // See section 5.1. If face i and j are adjacent and <i, j> >= min_angle, then
  // they are in the same partition.
  void ComputeFeatureBasedPartition(const double min_dihedral_angle,
    std::vector<std::vector<int>>& partitions) const;

private:
  // Return a list of floats, one for each triangle. The double is the integral
  // of x^[x_deg]y^[y_deg]z^[z_deg] over the triangle.
  const Eigen::VectorXd ComputeIntegral(const int x_deg, const int y_deg,
    const int z_deg) const;
  // Compute Mt for triangle idx (See section 3.2.1 in the paper).
  const Eigen::MatrixXd ComputeL2EnergyMatrix(const int idx) const;
  // Compute Nt for triangle idx (See section 3.2.1 in the paper).
  const Eigen::MatrixXd ComputeL21EnergyMatrix(const int idx) const;
  // Compute Bn for triangle idx (See appendix in the paper).
  const Eigen::VectorXd ComputeGradNormVector(const int idx) const;

  const mesh::TriMesh& shape_;
  Eigen::VectorXd integrals_[5][5][5];
  // Pre-compute some useful integrals. See comments in ComputeIntegral.
  double basic_integrals_[5][5];

  // L2 energy of each triangle.
  // For a quadratic f = C.dot(F(x)), L2 is defined as:
  // \int_S f(x)^2 ds = C' * (\int_S F(x)F(x)' ds) * C
  // The middle integral can be precomputed for each triangle.
  std::vector<Eigen::MatrixXd> l2_matrix_;
  // L21 energy of each triangle.
  // grad f = [C.dot(Fx), C.dot(Fy), C.dot(Fz)].
  // \int_S |grad f|^2 ds = C' * (\int_S (FxFx' + FyFy' + FzFz') * ds) * C
  std::vector<Eigen::MatrixXd> l21_matrix_;
  // Let n be the unit normal of the triangle. We compute:
  // \int_S (grad f).dot(n) ds
  // = \int_S (C.dot(Fx)nx + C.dot(Fy)ny + C.dot(Fz)nz) ds
  // = C' \int_S [Fx, Fy, Fz]n ds.
  // So we pre-compute \int_S (Fx * nx + Fy * ny + Fz * nz) ds.
  std::vector<Eigen::VectorXd> grad_norm_vector_;
};

}

#endif