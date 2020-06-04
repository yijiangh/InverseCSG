#include "vsa_tri_mesh_wrapper.h"
#include <cmath>
#include <vector>
#include <cstring>  // memset.
#include <set>
#include "common/file_helper.h"
#include "common/math_helper.h"

namespace vsa {

VsaTriMeshWrapper::VsaTriMeshWrapper(const mesh::TriMesh& shape)
  : shape_(shape), l2_matrix_(shape.NumOfFaces()),
  l21_matrix_(shape.NumOfFaces()),
  grad_norm_vector_(shape.NumOfFaces()) {
  for (int i = 0; i < 5; ++i)
    for (int j = 0; j < 5; ++j)
      basic_integrals_[i][j] = 0.0;
  // F(1) = 1 / 2.
  basic_integrals_[0][0] = 0.5;
  // F(u) = 1 / 6.
  basic_integrals_[1][0] = 1.0 / 6.0;
  // F(v) = 1 / 6.
  basic_integrals_[0][1] = 1.0 / 6.0;
  // F(u^2) = 1 / 12.
  basic_integrals_[2][0] = 1.0 / 12.0;
  // F(v^2) = 1 / 12.
  basic_integrals_[0][2] = 1.0 / 12.0;
  // F(uv) = 1 / 24.
  basic_integrals_[1][1] = 1.0 / 24.0;
  // F(u^3) = 1 / 20.
  basic_integrals_[3][0] = 1.0 / 20.0;
  // F(v^3) = 1 / 20.
  basic_integrals_[0][3] = 1.0 / 20.0;
  // F(u^2v) = 1 / 60.
  basic_integrals_[2][1] = 1.0 / 60.0;
  // F(uv^2) = 1 / 60.
  basic_integrals_[1][2] = 1.0 / 60.0;
  // F(u^4) = 1 / 30.
  basic_integrals_[4][0] = 1.0 / 30.0;
  // F(u^3v) = 1 / 120.
  basic_integrals_[3][1] = 1.0 / 120.0;
  // F(u^2v^2) = 1 / 180.
  basic_integrals_[2][2] = 1.0 / 180.0;
  // F(uv^3) = 1 / 120.
  basic_integrals_[1][3] = 1.0 / 120.0;
  // F(v^4) = 1 / 30.
  basic_integrals_[0][4] = 1.0 / 30.0;
  // Computer integrals for all 0 <= x_deg + y_deg + z_deg <= 4.
  for (int i = 0; i < 5; ++i)
    for (int j = 0; j < 5; ++j)
      for (int k = 0; k < 5; ++k)
        integrals_[i][j][k] = Eigen::VectorXd::Zero(0);
  for (int x_deg = 0; x_deg <= 4; ++x_deg) {
    for (int y_deg = 0; y_deg <= 4 - x_deg; ++y_deg) {
      for (int z_deg = 0; z_deg <= 4 - x_deg - y_deg; ++z_deg) {
        integrals_[x_deg][y_deg][z_deg] = ComputeIntegral(x_deg, y_deg, z_deg);
      }
    }
  }
  // Pre-compute matrices.
  for (int i = 0; i < shape.NumOfFaces(); ++i) {
    l2_matrix_[i] = ComputeL2EnergyMatrix(i);
    l21_matrix_[i] = ComputeL21EnergyMatrix(i);
    grad_norm_vector_[i] = ComputeGradNormVector(i);
  }
}

const mesh::TriMesh& VsaTriMeshWrapper::shape() const {
  return shape_;
}

const Eigen::VectorXd VsaTriMeshWrapper::integrals(const int x_deg,
  const int y_deg, const int z_deg) const {
  if (x_deg < 0 || x_deg > 4 || y_deg < 0 || y_deg > 4
    || z_deg < 0 || z_deg > 4)
    common::PrintError("vsa::VsaTriMeshWrapper::integrals: "
      "index out of range.");
  return integrals_[x_deg][y_deg][z_deg];
}

const Eigen::MatrixXd VsaTriMeshWrapper::l2_matrix(const int idx) const {
  if (idx < 0 || idx >= shape_.NumOfFaces())
    common::PrintError("vsa::VsaTriMeshWrapper::l2_matrix: "
      "index out of range.");
  return l2_matrix_[idx];
}

const Eigen::MatrixXd VsaTriMeshWrapper::l21_matrix(const int idx) const {
  if (idx < 0 || idx >= shape_.NumOfFaces())
    common::PrintError("vsa::VsaTriMeshWrapper::l21_matrix: "
      "index out of range.");
  return l21_matrix_[idx];
}

const Eigen::VectorXd VsaTriMeshWrapper::grad_norm_vector(const int idx) const {
  if (idx < 0 || idx >= shape_.NumOfFaces())
    common::PrintError("vsa::VsaTriMeshWrapper::grad_norm_vector: "
      "index out of range.");
  return grad_norm_vector_[idx];
}

void VsaTriMeshWrapper::ComputeFeatureBasedPartition(
  const double min_dihedral_angle,
  std::vector<std::vector<int>>& partitions) const {
  // Bookkeeping the unclaimed faces.
  std::vector<int> all_faces(shape_.NumOfFaces());
  for (int i = 0; i < shape_.NumOfFaces(); ++i) all_faces[i] = i;
  std::set<int> unclaimed_faces(all_faces.begin(), all_faces.end());
  partitions.clear();
  while (!unclaimed_faces.empty()) {
    // Start a new partition.
    std::vector<int> partition(0);
    const int seed = *unclaimed_faces.begin();
    int to_check = 0;
    partition.push_back(seed);
    unclaimed_faces.erase(seed);
    while (to_check < static_cast<int>(partition.size())) {
      const int fid = partition[to_check];
      // Now check against its three neighbors.
      const Eigen::Vector3i e = shape_.face_edge(fid);
      for (int i = 0; i < 3; ++i) {
        const int eid = e(i);
        for (const int f_neighbor_id : shape_.edge_neighbor(eid)) {
          if (f_neighbor_id == fid || unclaimed_faces.find(f_neighbor_id)
            == unclaimed_faces.end()) continue;
          // Check the angle between fid and f_neighbor_id.
          const Eigen::Vector3d f_norm = shape_.face_normal(fid),
            f_neighbor_norm = shape_.face_normal(f_neighbor_id);
          double cos_angle = -f_norm.dot(f_neighbor_norm);
          if (cos_angle > 1.0) cos_angle = 1.0;
          if (cos_angle < -1.0) cos_angle = -1.0;
          const double angle = std::acos(cos_angle);
          // In mesh::TriMesh we ensure singular triangles have zero normals.
          if (f_norm.norm() == 0 || f_neighbor_norm.norm() == 0 ||
            angle >= min_dihedral_angle) {
            partition.push_back(f_neighbor_id);
            unclaimed_faces.erase(f_neighbor_id);
          }
        }
      }
      ++to_check;
    }
    partitions.push_back(partition);
  }
}

const Eigen::VectorXd VsaTriMeshWrapper::ComputeIntegral(const int x_deg,
  const int y_deg, const int z_deg) const {
  // How to integrate a scalar function f(x, y, z) over a triangle in R3. Let
  // v0, v1, v3 be its three vertices, we can parameterize it with u \in [0, 1],
  // v \in [0, 1] and u + v <= 1, such that (x, y, z) =
  // v0 + u * (v1 - v0) + v * (v2 - v0):
  // \int_S f(x, y, z) ds = |cross(v1 - v0, v2 - v0)|
  //    * \int_{v = 0}^{1}\int_{u = 0}^{1 - v} f(u, v) dudv.
  // Here are some very useful integrations:
  // Define F(f(u, v)) = \int_{v = 0}^{1}\int_{u = 0}^{1 - v} f dudv.
  // F(1) = 1 / 2.
  // F(u) = 1 / 6.
  // F(v) = 1 / 6.
  // F(u^2) = 1 / 12.
  // F(v^2) = 1 / 12.
  // F(uv) = 1 / 24.
  // F(u^3) = 1 / 20.
  // F(v^3) = 1 / 20.
  // F(u^2v) = 1 / 60.
  // F(uv^2) = 1 / 60.
  // F(u^4) = 1 / 30.
  // F(u^3v) = 1 / 120.
  // F(u^2v^2) = 1 / 180.
  // F(uv^3) = 1 / 120.
  // F(v^4) = 1 / 30.
  const int face_num = shape_.NumOfFaces();
  Eigen::MatrixX3d A(face_num, 3), B(face_num, 3), C(face_num, 3);
  for (int i = 0; i < face_num; ++i) {
    const Eigen::Matrix3d triangle = shape_.Triangle(i);
    const Eigen::Vector3d v0 = triangle.col(0), v1 = triangle.col(1),
      v2 = triangle.col(2);
    // (x, y, z) = v0 + u * (v1 - v0) + v * (v2 - v0).
    // x = a0 + b0 * u + c0 * v.
    // y = a1 + b1 * u + c1 * v.
    // z = a2 + b2 * u + c2 * v.
    A.row(i) = v0; B.row(i) = v1 - v0; C.row(i) = v2 - v0;
  }
  std::vector<std::vector<Eigen::VectorXd>> uv_poly(5,
    std::vector<Eigen::VectorXd>(5, Eigen::VectorXd::Zero(face_num)));
  const auto zero_poly = uv_poly;
  uv_poly[0][0] = Eigen::VectorXd::Ones(face_num);
  const int degrees[3] = { x_deg, y_deg, z_deg };
  for (int deg = 0; deg < 3; ++deg) {
    for (int iter = 0; iter < degrees[deg]; ++iter) {
      // Multiply uv_poly by (a(deg) + b(deg) * u + c(deg) * v).
      const auto uv_poly_copy = uv_poly;
      uv_poly = zero_poly;
      // Multiply first by a.
      for (int ii = 0; ii < 5; ++ii)
        for (int jj = 0; jj < 5; ++jj)
          uv_poly[ii][jj] = A.col(deg).cwiseProduct(uv_poly_copy[ii][jj]);
      // Then by b * u.
      for (int ii = 0; ii < 4; ++ii)
        for (int jj = 0; jj < 5; ++jj)
          uv_poly[ii + 1][jj] += B.col(deg).cwiseProduct(uv_poly_copy[ii][jj]);
      // Then by c * v.
      for (int ii = 0; ii < 5; ++ii)
        for (int jj = 0; jj < 4; ++jj)
          uv_poly[ii][jj + 1] += C.col(deg).cwiseProduct(uv_poly_copy[ii][jj]);
    }
  }
  // Now we can compute the integral.
  Eigen::VectorXd integral = Eigen::VectorXd::Zero(face_num);
  for (int ii = 0; ii < 5; ++ii)
    for (int jj = 0; jj < 5; ++jj)
      integral += uv_poly[ii][jj] * basic_integrals_[ii][jj];
  for (int i = 0; i < face_num; ++i) {
    const Eigen::Vector3d b = B.row(i), c = C.row(i);
    integral(i) *= b.cross(c).norm();
  }
  return integral;
}

const Eigen::MatrixXd VsaTriMeshWrapper::ComputeL2EnergyMatrix(
  const int idx) const {
  // F = [1, x, y, z, x * x, x * y, x * z, y * y, y * z, z * z]';
  const int x_degs[10] = { 0, 1, 0, 0, 2, 1, 1, 0, 0, 0 };
  const int y_degs[10] = { 0, 0, 1, 0, 0, 1, 0, 2, 1, 0 };
  const int z_degs[10] = { 0, 0, 0, 1, 0, 0, 1, 0, 1, 2 };
  Eigen::MatrixXd M = Eigen::MatrixXd::Zero(10, 10);
  for (int i = 0; i < 10; ++i)
    for (int j = 0; j < 10; ++j) {
      const int x_deg = x_degs[i] + x_degs[j];
      const int y_deg = y_degs[i] + y_degs[j];
      const int z_deg = z_degs[i] + z_degs[j];
      M(i, j) = integrals_[x_deg][y_deg][z_deg](idx);
    }
  return M;
}

const Eigen::MatrixXd VsaTriMeshWrapper::ComputeL21EnergyMatrix(
  const int idx) const {
  // F = [1, x, y, z, x * x, x * y, x * z, y * y, y * z, z * z]';
  // Fx = [0, 1, 0, 0, 2x, y, z, 0, 0, 0]';
  // Fy = [0, 0, 1, 0, 0, x, 0, 2y, z, 0]';
  // Fz = [0, 0, 0, 1, 0, 0, x, 0, y, 2z]';
  const std::vector<int> f_nonzeros[3] = {
    { 1, 4, 5, 6 },
    { 2, 5, 7, 8 },
    { 3, 6, 8, 9 }
  };
  const std::vector<std::vector<int>> f_degs[3] = {
    { { 0, 0, 0 }, { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 } },
    { { 0, 0, 0 }, { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 } },
    { { 0, 0, 0 }, { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 } }
  };
  const std::vector<double> f_scale[3] = {
    { 1.0, 2.0, 1.0, 1.0 },
    { 1.0, 1.0, 2.0, 1.0 },
    { 1.0, 1.0, 1.0, 2.0 }
  };
  // Fx = sum_i f_scale[0][i]
  //   * x^f_degs[0][i][0] * y^f_degs[0][i][1] * z^f_degs[0][i][2].
  Eigen::MatrixXd N = Eigen::MatrixXd::Zero(10, 10);
  for (int i = 0; i < 3; ++i) {
    // Loop over Fx, Fy, Fz.
    const int num = static_cast<int>(f_nonzeros[i].size());
    for (auto j = 0; j < num; ++j) {
      const int jj = f_nonzeros[i][j];
      for (auto k = 0; k < num; ++k) {
        const int kk = f_nonzeros[i][k];
        const int x_degs = f_degs[i][j][0] + f_degs[i][k][0];
        const int y_degs = f_degs[i][j][1] + f_degs[i][k][1];
        const int z_degs = f_degs[i][j][2] + f_degs[i][k][2];
        N(jj, kk) += f_scale[i][j] * f_scale[i][k] *
          integrals_[x_degs][y_degs][z_degs](idx);
      }
    }
  }
  return N;
}

const Eigen::VectorXd VsaTriMeshWrapper::ComputeGradNormVector(
  const int idx) const {
  const Eigen::Vector3d normal = shape_.face_normal(idx);
  // F = [1, x, y, z, x * x, x * y, x * z, y * y, y * z, z * z]';
  // Fx = [0, 1, 0, 0, 2x, y, z, 0, 0, 0]';
  // Fy = [0, 0, 1, 0, 0, x, 0, 2y, z, 0]';
  // Fz = [0, 0, 0, 1, 0, 0, x, 0, y, 2z]';
  const std::vector<int> f_nonzeros[3] = {
    { 1, 4, 5, 6 },
    { 2, 5, 7, 8 },
    { 3, 6, 8, 9 }
  };
  const std::vector<std::vector<int>> f_degs[3] = {
    { { 0, 0, 0 },{ 1, 0, 0 },{ 0, 1, 0 },{ 0, 0, 1 } },
    { { 0, 0, 0 },{ 1, 0, 0 },{ 0, 1, 0 },{ 0, 0, 1 } },
    { { 0, 0, 0 },{ 1, 0, 0 },{ 0, 1, 0 },{ 0, 0, 1 } }
  };
  const std::vector<double> f_scale[3] = {
    { 1.0, 2.0, 1.0, 1.0 },
    { 1.0, 1.0, 2.0, 1.0 },
    { 1.0, 1.0, 1.0, 2.0 }
  };
  Eigen::VectorXd V = Eigen::VectorXd::Zero(10);
  for (int i = 0; i < 3; ++i) {
    const int num = static_cast<int>(f_nonzeros[i].size());
    for (int j = 0; j < num; ++j) {
      const int jj = f_nonzeros[i][j];
      const int x_deg = f_degs[i][j][0];
      const int y_deg = f_degs[i][j][1];
      const int z_deg = f_degs[i][j][2];
      V(jj) += normal(i) * f_scale[i][j] *
        integrals_[x_deg][y_deg][z_deg](idx);
    }
  }
  return V;
}

}
