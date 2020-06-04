#ifndef _MESH_LEVEL_SET_HELPER_H_
#define _MESH_LEVEL_SET_HELPER_H_

#include <memory>
#include <string>
#include <unordered_set>
#include "Eigen/Dense"
#include "tri_mesh.h"

namespace mesh {

class LevelSetHelper {
public:
  LevelSetHelper(const Eigen::Vector3d& pmin, const double grid_size,
    const Eigen::Vector3i& dim,
    const std::unordered_set<long long int>& close_grid_idx);
  LevelSetHelper(const TriMesh& shape, const double grid_size);

  const Eigen::Vector3d pmin() const;
  const double grid_size() const;
  const Eigen::Vector3i dim() const;
  const std::unordered_set<long long int>& close_grid_idx() const;

  // Returns true if dist(point, mesh) <= grid_size_. For other points the
  // return value is undefined and up to the implementation.
  const bool IsCloseToMesh(const Eigen::Vector3d& point) const;

private:
  void ComputeLevelSet(const TriMesh& shape, const double grid_size);
  const Eigen::Vector3i LinearIdxToGridIdx(
    const long long int linear_idx) const;
  const long long int GridIdxToLinearIdx(
    const Eigen::Vector3i& grid_idx) const;
  void AssertGridIdx(const Eigen::Vector3i& grid_idx) const;
  const Eigen::Vector3i PointToGridIdx(const Eigen::Vector3d& point) const;
  const Eigen::Vector3i ClampGridIdx(const Eigen::Vector3i& grid_idx) const;

  // Define the grid.
  Eigen::Vector3d pmin_;
  double grid_size_;
  Eigen::Vector3i dim_; // Number of grids.

  // If a point has dist(p, mesh) <= grid_size then it must be covered by at
  // least one grid in this set. The level-set method tries its best to ensure
  // the cardinality of this set is as small as possible. 
  // Use long long int because it has at least 64 bits. Sometimes int is not
  // big enough: 2000^3 > MAX_INT.
  std::unordered_set<long long int> close_grid_idx_;
};

}

#endif
