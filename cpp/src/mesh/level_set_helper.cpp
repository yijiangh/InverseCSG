#include "level_set_helper.h"
#include <iostream>
#include <cmath>
#include "common/file_helper.h"
#include "common/math_helper.h"

namespace mesh {

LevelSetHelper::LevelSetHelper(const Eigen::Vector3d& pmin,
  const double grid_size, const Eigen::Vector3i& dim,
  const std::unordered_set<long long int>& close_grid_idx)
  : pmin_(pmin), grid_size_(grid_size), dim_(dim),
  close_grid_idx_(close_grid_idx) {}

LevelSetHelper::LevelSetHelper(const TriMesh& shape, const double grid_size)
  : pmin_(0, 0, 0), grid_size_(0), dim_(0, 0, 0), close_grid_idx_() {
  ComputeLevelSet(shape, grid_size);
}

const Eigen::Vector3d LevelSetHelper::pmin() const {
  return pmin_;
}

const double LevelSetHelper::grid_size() const {
  return grid_size_;
}

const Eigen::Vector3i LevelSetHelper::dim() const {
  return dim_;
}

const std::unordered_set<long long int>& 
LevelSetHelper::close_grid_idx() const {
  return close_grid_idx_;
}

const bool LevelSetHelper::IsCloseToMesh(const Eigen::Vector3d& point) const {
  const Eigen::Vector3i grid_idx = ((point - pmin_) / grid_size_).cast<int>();
  for (int i = 0; i < 3; ++i) {
    if (grid_idx(i) < 0 || grid_idx(i) >= dim_(i)) return false;
  }
  const long long int linear_idx = GridIdxToLinearIdx(grid_idx);
  return close_grid_idx_.find(linear_idx) != close_grid_idx_.end();
}

void LevelSetHelper::ComputeLevelSet(const TriMesh& shape,
  const double grid_size) {
  if (grid_size <= 0.0) {
    std::cerr << common::RedHead()
      << "mesh::LevelSetHelper::ComputeLevelSet: nonpositive grid_size: "
      << grid_size << common::RedTail() << std::endl;
    exit(-1);
  }

  // Compute the bounding box.
  const Eigen::Vector3d bbox_min = shape.box_min(), bbox_max = shape.box_max();
  pmin_ = bbox_min.array() - 2.0 * grid_size;
  dim_ = ((bbox_max - bbox_min) / grid_size).cast<int>().array() + 5;
  grid_size_ = grid_size;

  // Compute close_grid_idx_.
  close_grid_idx_.clear();
  for (int i = 0; i < shape.NumOfFaces(); ++i) {
    const Eigen::Matrix3d triangle = shape.Triangle(i);
    const Eigen::Vector3d t_min = triangle.rowwise().minCoeff(),
      t_max = triangle.rowwise().maxCoeff();
    const Eigen::Vector3i t_min_idx = ClampGridIdx(
      PointToGridIdx(t_min).array() - 2);
    const Eigen::Vector3i t_max_idx = ClampGridIdx(
      PointToGridIdx(t_max).array() + 2);
    // Check each grid.
    for (int ii = t_min_idx.x(); ii <= t_max_idx.x(); ++ii)
      for (int jj = t_min_idx.y(); jj <= t_max_idx.y(); ++jj)
        for (int kk = t_min_idx.z(); kk <= t_max_idx.z(); ++kk) {
          const Eigen::Vector3d center = pmin_
            + Eigen::Vector3d(ii + 0.5, jj + 0.5, kk + 0.5) * grid_size_;
          const double min_dist = common::PointToTriangleDistance(
            center, triangle);
          // If \exists q\in grid s.t. dist(q, mesh) < grid_size_, then
          // dist(center, mesh) <= dist(q, mesh) + dist(q, center)
          // <= dist(q, mesh) + sqrt(3) / 2 * grid_size_
          // < (1 + sqrt(3) / 2) * grid_size_.
          if (min_dist < (1.0 + 0.5 * std::sqrt(3.0)) * grid_size_) {
            close_grid_idx_.insert(GridIdxToLinearIdx(
              Eigen::Vector3i(ii, jj, kk)));
          }
        }
  }
}

const Eigen::Vector3i LevelSetHelper::LinearIdxToGridIdx(
  const long long int linear_idx) const {
  Eigen::Vector3i grid_idx;
  const long long int dy = static_cast<long long int>(dim_.y());
  const long long int dz = static_cast<long long int>(dim_.z());
  grid_idx.x() = static_cast<int>(linear_idx / (dy * dz));
  grid_idx.y() = static_cast<int>((linear_idx / dz) % dy);
  grid_idx.z() = static_cast<int>(linear_idx % dz);
  AssertGridIdx(grid_idx);
  return grid_idx;
}

const long long int LevelSetHelper::GridIdxToLinearIdx(
  const Eigen::Vector3i& grid_idx) const {
  AssertGridIdx(grid_idx);
  const long long int dy = static_cast<long long int>(dim_.y());
  const long long int dz = static_cast<long long int>(dim_.z());
  const long long int gx = static_cast<long long int>(grid_idx.x());
  const long long int gy = static_cast<long long int>(grid_idx.y());
  const long long int gz = static_cast<long long int>(grid_idx.z());
  return gx * dy * dz + gy * dz + gz;
}

void LevelSetHelper::AssertGridIdx(const Eigen::Vector3i& grid_idx) const {
  for (int i = 0; i < 3; ++i) {
    if (grid_idx(i) < 0 || grid_idx(i) >= dim_(i)) {
      std::cerr << common::RedHead()
        << "mesh::LevelSetHelper::AssertGridIdx: invalid grid_idx: ("
        << grid_idx.transpose() << ") outside (" << dim_.transpose() << ")."
        << common::RedTail() << std::endl;
      exit(-1);
    }
  }
}

const Eigen::Vector3i LevelSetHelper::PointToGridIdx(
  const Eigen::Vector3d& point) const {
  return ((point - pmin_) / grid_size_).cast<int>();
}

const Eigen::Vector3i LevelSetHelper::ClampGridIdx(
  const Eigen::Vector3i& grid_idx) const {
  return grid_idx.cwiseMax(0).cwiseMin(Eigen::Vector3i(dim_.array() - 1));
}

}
