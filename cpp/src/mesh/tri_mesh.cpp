#include "mesh/tri_mesh.h"
#include <sstream>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>
#include <queue>
#include "common/file_helper.h"
#include "common/math_helper.h"

namespace mesh {

static const Eigen::Vector2d ProjectPointToTriangle(
  const Eigen::Vector3d& point, const Eigen::Vector3d& v0,
  const Eigen::Vector3d& v1, const Eigen::Vector3d& v2) {
  // This function assumes the triangle is good.
  // |v0 + alpha * (v1 - v0) + beta * (v2 - v0) - point| = 0.
  Eigen::MatrixXd A(3, 2); A.col(0) = v1 - v0; A.col(1) = v2 - v0;
  Eigen::VectorXd b = point - v0;
  // Ax = b.
  const Eigen::Vector2d x = A.jacobiSvd(Eigen::ComputeThinU
    | Eigen::ComputeThinV).solve(b);
  const Eigen::MatrixXd A_transpose = A.transpose();
  const Eigen::Matrix2d AtA = A_transpose * A;
  const Eigen::Vector2d Atb = A_transpose * b;
  const double res = (AtA * x - Atb).norm();
  if (!x.allFinite() || (res > 0.01 * Atb.norm() && res > common::Epsilon())) {
    std::cerr << common::RedHead()
      << "mesh::ProjectPointToTriangle: bad triangle: " << std::endl
      << "v0: " << v0.transpose() << std::endl
      << "v1: " << v1.transpose() << std::endl
      << "v2: " << v2.transpose() << std::endl
      << "res: " << res << common::RedTail() << std::endl;
    exit(-1);
  }
  return x;
}

static const bool TwoLineSegmentsIntersect(const Eigen::Vector2d& p0,
  const Eigen::Vector2d& p1, const Eigen::Vector2d& q0,
  const Eigen::Vector2d& q1) {
  // We assume both (p1 - p0) and (q1 - q0) are nonzero.
  // Return false if it is a clear miss. If we are unsure, return true.
  // Intersect iff p0, p1 are on the different side of (q0, q1) AND q0, q1 are
  // on the different side of (p0, p1).
  // Line equation for (p0, p1):
  // pa * x + pb * y + pc = 0.
  // qa * x + qb * y + qc = 0.
  const Eigen::Vector2d p_dir = p1 - p0, q_dir = q1 - q0;
  const double eps = common::Epsilon();
  const double p_dir_norm = p_dir.norm(), q_dir_norm = q_dir.norm();
  if (p_dir_norm < eps || q_dir_norm < eps) {
    std::cerr << common::RedHead()
      << "mesh::TwoLineSegmentsIntersect: expects to see nonsingular "
      << "p and q:" << std::endl << "p0 = " << p0.transpose() << ", p1 = "
      << p1.transpose() << std::endl << "q0 = " << q0.transpose() << ", q1 = "
      << q1.transpose() << common::RedTail() << std::endl;
    exit(-1);
  }
  // (x - p0.x(), y - p0.y()) // p_dir
  // (x - p0.x()) * p_dir.y() = (y - p0.y()) * p_dir.x().
  Eigen::Vector3d p_line(p_dir.y(), -p_dir.x(),
    p0.y() * p_dir.x() - p0.x() * p_dir.y());
  p_line /= p_dir_norm;
  Eigen::Vector3d q_line(q_dir.y(), -q_dir.x(),
    q0.y() * q_dir.x() - q0.x() * q_dir.y());
  q_line /= q_dir_norm;

  const double p0_dist = q_line.dot(Eigen::Vector3d(p0.x(), p0.y(), 1.0));
  const double p1_dist = q_line.dot(Eigen::Vector3d(p1.x(), p1.y(), 1.0));
  const double q0_dist = p_line.dot(Eigen::Vector3d(q0.x(), q0.y(), 1.0));
  const double q1_dist = p_line.dot(Eigen::Vector3d(q1.x(), q1.y(), 1.0));

  return !(// Clearly a miss.
    (// p0 and p1 are on the same side of q.
      std::fabs(p0_dist) > eps && std::fabs(p1_dist) > eps && p0_dist * p1_dist > 0.0
    ) ||
    (// q0 and q1 are on the same side of p.
      std::fabs(q0_dist) > eps && std::fabs(q1_dist) > eps && q0_dist * q1_dist > 0.0
    )
  );
}

static const bool IsInsideBarycentricTriangle(const Eigen::Vector2d& p) {
  // Return false if it is clearly outside.
  const double eps = common::Epsilon();
  return p.x() > -eps && p.y() > -eps && p.sum() < 1.0f + eps;
}

static const bool IntersectBarycentricTriangle(const Eigen::Vector2d& p0,
  const Eigen::Vector2d& p1) {
  // Given a 2D line segment (p0, p1), check if it intersects the following
  // triangle:
  // v0 = (0, 0), v1 = (0, 1), v2 = (1, 0).
  // Return false if the line segment clearly misses the triangle. Return true
  // if it intersects the triangle or if we are uncertain.
  // No intersection if both p0 and p1 are outside AND (p0, p1) does not
  // intersect any edges.
  const Eigen::Vector2d v0(0.0, 0.0), v1(0.0, 1.0), v2(1.0, 0.0);
  return IsInsideBarycentricTriangle(p0) ||
    IsInsideBarycentricTriangle(p1) ||
    TwoLineSegmentsIntersect(p0, p1, v0, v1) ||
    TwoLineSegmentsIntersect(p0, p1, v1, v2) ||
    TwoLineSegmentsIntersect(p0, p1, v0, v2);
}

TriMesh::TriMesh()
  : vertices_(3, 0), faces_(3, 0), areas_(0), sorted_face_id_(0),
  vertex_normals_(3, 0), face_normals_(3, 0), kd_tree_(*this),
  box_min_(0.0, 0.0, 0.0), box_max_(0.0, 0.0, 0.0), face_neighbors_(0),
  face_edges_(0), edge_neighbors_(0) {}

void TriMesh::Initialize(const std::string& file_name) {
  common::ReadOffFile(file_name, vertices_, faces_);
  InitializeAfterVerticesAndFaces();
}

void TriMesh::Initialize(const Eigen::Matrix3Xd& vertices,
  const Eigen::Matrix3Xi& faces) {
  vertices_ = vertices;
  faces_ = faces;

  InitializeAfterVerticesAndFaces();
}

const Eigen::Matrix3Xd TriMesh::vertices() const {
  return vertices_;
}

const Eigen::Vector3d TriMesh::vertex(const int vertex_id) const {
  if (vertex_id < 0 || vertex_id >= NumOfVertices()) {
    common::PrintError("mesh::TriMesh::vertex: invalid vertex id.");
  }
  return vertices_.col(vertex_id);
}

const Eigen::Matrix3Xi TriMesh::faces() const {
  return faces_;
}

const Eigen::Vector3i TriMesh::face(const int face_id) const {
  if (face_id < 0 || face_id >= NumOfFaces()) {
    common::PrintError("mesh::TriMesh::face: invalid face id.");
  }
  return faces_.col(face_id);
}

const Eigen::VectorXd TriMesh::areas() const {
  return areas_;
}

const Eigen::Matrix3Xd TriMesh::vertex_normals() const {
  return vertex_normals_;
}

const Eigen::Matrix3Xd TriMesh::face_normals() const {
  return face_normals_;
}

const double TriMesh::area(const int face_id) const {
  if (face_id < 0 || face_id >= NumOfFaces()) {
    common::PrintError("mesh::TriMesh::area: invalid face id.");
  }
  return areas_(face_id);
}

const Eigen::Vector3d TriMesh::vertex_normal(const int vertex_id) const {
  if (vertex_id < 0 || vertex_id >= NumOfVertices()) {
    common::PrintError("mesh::TriMesh::vertex_normal: invalid vertex id.");
  }
  return vertex_normals_.col(vertex_id);
}

const Eigen::Vector3d TriMesh::face_normal(const int face_id) const {
  if (face_id < 0 || face_id >= NumOfFaces()) {
    common::PrintError("mesh::TriMesh::face_normal: invalid face id.");
  }
  return face_normals_.col(face_id);
}

const int TriMesh::NumOfVertices() const {
  return static_cast<int>(vertices_.cols());
}

const int TriMesh::NumOfFaces() const {
  return static_cast<int>(faces_.cols());
}

const int TriMesh::NumOfEdges() const {
  return static_cast<int>(edge_neighbors_.size());
}

const Eigen::Matrix3d TriMesh::Triangle(const int face_id) const {
  assert(face_id >= 0 && face_id < NumOfFaces());
  Eigen::Matrix3d triangle;
  for (int i = 0; i < 3; ++i) {
    triangle.col(i) = vertices_.col(faces_(i, face_id));
  }
  return triangle;
}

const Eigen::Vector3d TriMesh::box_min() const {
  return box_min_;
}

const Eigen::Vector3d TriMesh::box_max() const {
  return box_max_;
}

const std::vector<int> TriMesh::face_neighbor(const int face_id) const {
  if (face_id < 0 || face_id >= NumOfFaces()) {
    common::PrintError("mesh::TriMesh::face_neighbor: invalid face id.");
  }
  return face_neighbors_[face_id];
}

const Eigen::Vector3i TriMesh::face_edge(const int face_id) const {
  if (face_id < 0 || face_id >= NumOfFaces()) {
    common::PrintError("mesh::TriMesh::face_edge: invalid face id.");
  }
  return face_edges_[face_id];
}

const std::vector<int> TriMesh::edge_neighbor(const int edge_id) const {
  if (edge_id < 0 || edge_id >= NumOfEdges()) {
    common::PrintError("mesh::TriMesh::edge_neighbor: invalid edge id.");
  }
  return edge_neighbors_[edge_id];
}

void TriMesh::WriteToFile(const std::string& file_name) const {
  if (!common::HasExtension(file_name, ".off")) {
    std::cerr << common::RedHead()
      << "mesh::TriMesh: expect to see .OFF file: " << file_name
      << common::RedTail() << std::endl;
    exit(-1);
  }
  std::ofstream fout(file_name);
  fout << "OFF" << std::endl;
  fout << NumOfVertices() << " " << NumOfFaces() << " 0" << std::endl;
  for (int i = 0; i < NumOfVertices(); ++i) {
    fout << vertices_(0, i) << " " << vertices_(1, i)
      << " " << vertices_(2, i) << std::endl;
  }
  for (int i = 0; i < NumOfFaces(); ++i) {
    fout << "3 " << faces_(0, i) << " " << faces_(1, i)
      << " " << faces_(2, i) << std::endl;
  }
  fout.close();
}

void TriMesh::Sample(const double density, const bool fully_random,
  Eigen::Matrix3Xd& points, Eigen::Matrix3Xd& normals,
  Eigen::VectorXi& point_to_face) const {
  if (fully_random)
    SampleWithFullRandomness(density, points, normals, point_to_face);
  else
    SampleWithoutFullRandomness(density, points, normals, point_to_face);
}

const KdTree& TriMesh::kd_tree() const {
  return kd_tree_;
}

const bool TriMesh::IsInside(const Eigen::Vector3d& point) const {
  const double eps = common::Epsilon();
  const Eigen::Vector3d box_min = vertices_.rowwise().minCoeff(),
    box_max = vertices_.rowwise().maxCoeff();
  const double max_dist = (point - box_min).norm() + (box_max - box_min).norm();
  // First, try random directions and hope we are lucky.
  const int max_trial = 4096000;
  for (int i = 0; i < max_trial; ++i) {
    const Eigen::Vector3d random_dir = Eigen::Vector3d::Random().normalized();
    if (std::fabs(random_dir.norm() - 1.0) > eps) continue;
    Intersection inter;
    kd_tree_.Intersect(point, random_dir, 0.0, max_dist + eps, inter);
    if (inter.uncertain()) continue;
    return inter.hit() && !inter.outside();
  }
  // Second, loop over all face centers.
  const int face_num = NumOfFaces();
  for (int i = 0; i < face_num; ++i) {
    const int idx = sorted_face_id_(i);
    const Eigen::Matrix3d triangle = Triangle(idx);
    const Eigen::Vector3d target = triangle.rowwise().mean();
    // Shoot a ray from point to target.
    Eigen::Vector3d dir = target - point;
    const double dir_norm = dir.norm();
    if (dir_norm < eps) continue;
    dir /= dir_norm;
    Intersection inter;
    kd_tree_.Intersect(point, dir, 0.0, dir_norm + 2.0 * eps, inter);
    if (inter.uncertain()) continue;
    if (!inter.hit()) {
      common::PrintError("mesh::TriMesh::IsInside: should hit.");
    }
    return !inter.outside();
  }
  // All trials fail. This is terrible.
  std::ostringstream ss;
  ss << "mesh::TriMesh::IsInside: point (" << point.transpose() << ") used up "
    << "all trials. Please improve your mesh to avoid singular triangles.";
  common::PrintError(ss.str());
  // Dummy return.
  return false;
}

const void TriMesh::IntersectTriangle(const int idx,
  const Eigen::Vector3d& origin, const Eigen::Vector3d& dir, const double tmin,
  const double tmax, Intersection& inter) const {
  if (idx < 0 || idx >= NumOfFaces()) {
    std::ostringstream ss;
    ss << "mesh::TriMesh::IntersectTriangle: triangle idx out of bound.";
    common::PrintError(ss.str());
  }
  const double inf = common::Infinity();
  const double eps = common::Epsilon();
  if (tmin == -inf || tmax == inf || tmin + eps >= tmax - eps) {
    std::ostringstream ss;
    ss << "mesh::TriMesh::IntersectTriangle: expect to see finite tmin"
      << " and tmax: tmin = " << tmin << ", tmax = " << tmax;
    common::PrintError(ss.str());
  }

  // Initialize the intersection. This corresponds to 'clearly a miss':
  inter.uncertain_ = false;
  inter.t_ = inf;
  inter.hit_ = false;
  inter.outside_ = false;

  // Easy, non-singular case:
  const Eigen::Matrix3d triangle = Triangle(idx);
  // Scale the triangle for better conditioning.
  const Eigen::Vector3d box_min = triangle.rowwise().minCoeff();
  const Eigen::Vector3d box_diag = triangle.rowwise().maxCoeff() - box_min;
  Eigen::Vector3d scale = Eigen::Vector3d::Ones();
  for (int i = 0; i < 3; ++i) {
    if (std::fabs(box_diag(i)) > eps) scale(i) = 1.0f / box_diag(i);
  }
  // Space transform: p -> (p - box_min) * scale.
  const Eigen::Matrix3d transformed_triangle = scale.asDiagonal()
    * (triangle.colwise() - box_min);
  const Eigen::Vector3d v0 = transformed_triangle.col(0),
    v1 = transformed_triangle.col(1), v2 = transformed_triangle.col(2);
  const Eigen::Vector3d new_dir = dir.cwiseProduct(scale);
  const Eigen::Vector3d o0 = (origin + tmin * dir - box_min
    ).cwiseProduct(scale);
  const Eigen::Vector3d o1 = (origin + tmax * dir - box_min
    ).cwiseProduct(scale);
  // o0 + (t - tmin) * new_dir = v0 + a * (v1 - v0) + b * (v2 - v0).
  Eigen::Matrix3d A;
  A.col(0) = v1 - v0; A.col(1) = v2 - v0; A.col(2) = -new_dir;
  const Eigen::Vector3d b = o0 - v0;
  const Eigen::Vector3d x = A.inverse() * b;
  if (x.allFinite() && (A * x - b).norm() < eps * b.norm()) {
    // Easy cases.
    const double alpha = x(0), beta = x(1), t = x(2) + tmin;
    if (alpha > eps && beta > eps && alpha + beta < 1.0f - eps &&
      t > tmin + eps && t < tmax - eps) {
      // Clearly hit.
      inter.hit_ = true;
      inter.t_ = t;
      const Eigen::Vector3d normal = (v1 - v0).cross(v2 - v1).normalized();
      if (!normal.allFinite() || std::fabs(normal.norm() - 1.0) > eps) {
        std::ostringstream ss;
        ss << "mesh::TriMesh::IntersectTriangle: "
          << "expect to see a well-defined normal: " << normal.transpose();
        common::PrintError(ss.str());
      }
      inter.outside_ = normal.dot(new_dir) < 0.0;
    } else {
      const bool clear_miss = alpha < -eps || beta < -eps ||
        alpha + beta > 1.0 + eps || t < tmin - eps || t > tmax + eps;
      // clear_miss = true => uncertain = false.
      // clear_miss = false => uncertain = true.
      inter.uncertain_ = !clear_miss;
    };
    return;
  }
  // Now we need to handle hard, singular cases.
  // A.inverse() fails only in the following cases:
  // - The first two columns are dependent: this corresponds to degenerated
  //   triangles: a point, a line, or a tiny and thin triangle.
  // - The first two columns are independent but the last column can be spanned
  //   by them: in this case the triangle is fine, but the ray is parallel to
  //   the plane.
  Eigen::Vector3d normal = (v1 - v0).cross(v2 - v1);
  const double area = normal.norm() * 0.5;
  const Eigen::Vector3d v_array[3] = { v0, v1, v2 };
  // We know the triangle lies in [0, 1]^3. TODO: remove this magic number.
  const double area_threshold = 0.05;
  if (area < area_threshold) {
    // Singular, degenerated triangle.
    Eigen::Vector3d edge_len((v0 - v1).norm(), (v1 - v2).norm(),
      (v2 - v0).norm());
    int max_idx = -1;
    const double max_edge_len = edge_len.maxCoeff(&max_idx);
    const double new_dir_len = new_dir.norm();
    // Case 1: (Almost) a single point.
    if (max_edge_len < (std::sqrt(3.0) + 1.0) * eps) {
      const Eigen::Vector3d center = (v0 + v1 + v2) / 3.0;
      const double radius = Eigen::Vector3d((v0 - center).norm(),
        (v1 - center).norm(), (v2 - center).norm()).maxCoeff();
      // Check the sphere (center, radius) intersects the line or not.
      const double t_proj = new_dir.dot(center - o1)
        / new_dir_len / new_dir_len;
      const double dist = std::sqrt((center - o1).squaredNorm()
        - t_proj * t_proj);
      const double t = t_proj + tmin;
      // Clearly a miss if the sphere is far from the line, or colinear but
      // away from the two end points.
      const bool miss = dist > radius + eps
        || t + radius / new_dir_len < tmin - eps
        || t - radius / new_dir_len > tmax + eps;
      // Unsure if it is not a clear miss.
      inter.uncertain_ = !miss;
    } else {
      // Case 2: (Almost) a strict line.
      const int end_i = max_idx;
      const int end_j = (max_idx + 1) % 3;
      Eigen::Vector3d end_p0 = v_array[end_i],
        end_p1 = v_array[end_j];
      Eigen::Vector3d axis = end_p1 - end_p0;
      const double axis_len = axis.norm();
      // There should be no problem with axis_len.
      if (axis_len < 1.0f - eps) {
        std::ostringstream ss;
        ss << "mesh::TriMesh::IntersectTriangle: "
          << "expect to see a better behaved axis_len: " << axis_len;
        common::PrintError(ss.str());
      }
      // The radius could be very small though. There is no guarantee here.
      const double radius = edge_len.minCoeff();
      end_p0 -= radius / axis_len * axis;
      end_p1 += radius / axis_len * axis;
      axis = end_p1 - end_p0;
      // We are checking a cylinder whose endpoints are end_p0 and end_p1. It
      // should be sufficiently compact now.
      // <o0 + t * (o1 - o0) - (end_p0 + s * axis), o1 - o0> = 0.
      // <o0 + t * (o1 - o0) - (end_p0 + s * axis), axis> = 0.
      // So:
      // <(o1 - o0) * t - axis * s + o0 - end_p0, o1 - o0> = 0.
      // <(o1 - o0) * t - axis * s + o0 - end_p0, axis> = 0.
      Eigen::Matrix2d A2;
      A2(0, 0) = (o1 - o0).squaredNorm(); A2(0, 1) = -axis.dot(o1 - o0);
      A2(1, 0) = (o1 - o0).dot(axis); A2(1, 1) = -axis.squaredNorm();
      Eigen::Vector2d b2((end_p0 - o0).dot(o1 - o0), (end_p0 - o0).dot(axis));
      // A2 * [t; s] = b2. We know A2(0, 0) != 0 and A2(1, 1) != 0 for sure.
      // A2(0, 0) * t + A2(0, 1) * s = b2(0).
      // t = u * s + v.
      // A2(1, 0) * (u * s + v) + A2(1, 1) * s = b2(1).
      const double u = -A2(0, 1) / A2(0, 0), v = b2(0) / A2(0, 0);
      // a0 * s + a1 = 0.
      const double a0 = A2(1, 0) * u + A2(1, 1), a1 = A2(1, 0) * v - b2(1);
      if (std::fabs(a0) < eps) {
        // In this case, axis and new_dir are almost in parallel.
        const double s = 0.0;
        const double min_dist =
          (o0 + v * (o1 - o0) - (end_p0 + s * axis)).norm();
        // Try to project o0 and o1 to axis.
        double t0 = (o0 - end_p0).dot(axis) / axis.squaredNorm(),
          t1 = (o1 - end_p0).dot(axis) / axis.squaredNorm();
        if (t0 > t1) {
          // Swap.
          const double t_tmp = t0; t0 = t1; t1 = t_tmp;
        }
        inter.uncertain_ = !(// Clearly a miss.
          min_dist > radius + eps ||
          t0 > 1.0f + eps || t1 < -eps
        );
      } else {
        const double s = -a1 / a0;
        const double t = (u * s + v) * (o1 - o0).norm() / new_dir_len + tmin;
        const double min_dist =
          (o0 + (u * s + v) * (o1 - o0) - (end_p0 + s * axis)).norm();
        inter.uncertain_ = min_dist < radius + eps &&
          !(tmax + radius + eps < t || tmin - radius - eps > t) &&
          !(s - (tmax - tmin) * new_dir_len - eps > 1.0
            || s + (tmax - tmin) * new_dir_len + eps < 0.0);
      }
    }    
  } else {
    // Triangle is fine but the ray is almost parallel.
    normal /= (area * 2.0);
    // Plane equation: normal.dot(x) + offset = 0.
    const double offset = -normal.dot(v0);
    const double d0 = normal.dot(o0) + offset, d1 = normal.dot(o1) + offset;
    // If both are on the same side, it is clearly a miss and we can skip.
    if ((d0 < eps || d1 < eps) && (d0 > -eps || d1 > -eps)) {
      // Project o0 and o1 to this plane.
      // v0 + (v1 - v0) * alpha0 + (v2 - v0) * beta0 - o0, 
      const Eigen::Vector2d coord0 = ProjectPointToTriangle(o0, v0, v1, v2),
        coord1 = ProjectPointToTriangle(o1, v0, v1, v2);
      inter.uncertain_ = IntersectBarycentricTriangle(coord0, coord1);
    }
  }
}

void TriMesh::InitializeAfterVerticesAndFaces() {
  const int face_num = static_cast<int>(faces_.cols());
  const int vertex_num = static_cast<int>(vertices_.cols());
  // Reorder faces by their areas in decreasing order.
  struct FaceMetaData {
  public:
    int index;
    double area;
  };
  std::vector<FaceMetaData> keys(face_num);
  areas_ = Eigen::VectorXd::Zero(face_num);
  face_normals_ = Eigen::Matrix3Xd::Zero(3, face_num);
  vertex_normals_ = Eigen::Matrix3Xd::Zero(3, vertex_num);
  sorted_face_id_ = Eigen::VectorXi::Zero(face_num);
  for (int i = 0; i < face_num; ++i) {
    const Eigen::Matrix3d triangle = Triangle(i);
    FaceMetaData data;
    data.index = i;
    const Eigen::Vector3d normal = (triangle.col(1) - triangle.col(0)).cross(
      triangle.col(2) - triangle.col(0));
    data.area = normal.norm() * 0.5;
    keys[i] = data;
    areas_(i) = data.area;
    face_normals_.col(i) = normal;
    for (int j = 0; j < 3; ++j) {
      vertex_normals_.col(faces_(j, i)) += normal;
    }
  }
  std::sort(keys.begin(), keys.end(), [](const FaceMetaData& a,
    const FaceMetaData& b) {
    return a.area > b.area || (a.area == b.area && a.index < b.index);
  });
  for (int i = 0; i < face_num; ++i) {
    sorted_face_id_(i) = keys[i].index;
  }

  // Normalize face normals and vertex normals.
  int bad_face_num = 0;
  for (int i = 0; i < face_num; ++i) {
    if (areas_(i) < common::Epsilon()) {
      face_normals_.col(i) = Eigen::Vector3d::Zero();
      ++bad_face_num;
    }
    else face_normals_.col(i) /= (areas_(i) * 2.0);
  }
  const double bad_face_ratio = bad_face_num * 1.0 / face_num;
  // Give a warning (error) if 5% (10%) of the triangles are bad.
  if (bad_face_ratio > 0.1) {
    std::stringstream ss;
    ss << "mesh::TriMesh::InitializeAfterVerticesAndFaces: "
      "too many triangles (" << bad_face_ratio * 100.0 << "%) are singular";
    common::PrintError(ss.str());
  } else if (bad_face_ratio > 0.05) {
    std::stringstream ss;
    ss << "mesh::TriMesh::InitializeAfterVerticesAndFaces: "
      "some triangles (" << bad_face_ratio * 100.0 << "%) are singular.";
    common::PrintWarning(ss.str());
  }

  for (int i = 0; i < vertex_num; ++i) {
    const double len = vertex_normals_.col(i).norm();
    if (len < common::Epsilon())
      vertex_normals_.col(i) = Eigen::Vector3d::Zero();
    else vertex_normals_.col(i) /= len;
  }

  // Computing the bounding boxes.
  box_min_ = vertices_.rowwise().minCoeff();
  box_max_ = vertices_.rowwise().maxCoeff();

  // Initialize the kd tree.
  kd_tree_.BuildKdTree();

  // Initialize topology.
typedef std::pair<int, int> edge;
  std::map<edge, std::vector<int>> edges;
  for (int i = 0; i < face_num; ++i) {
    for (int j = 0; j < 3; ++j) {
      int ii = faces_(j, i), jj = faces_((j + 1) % 3, i);
      // Swap if ii > jj.
      if (ii == jj || ii < 0 || jj < 0
        || ii >= vertex_num || jj >= vertex_num) {
        common::PrintError("mesh::TriMesh: invalid vertex id in faces.");
      }
      if (ii > jj) {
        const int tmp = ii; ii = jj; jj = tmp;
      }
      const edge e = std::make_pair(ii, jj);
      edges[e].push_back(i);
    }
  }
  face_neighbors_ = std::vector<std::vector<int>>(face_num);
  std::vector<std::vector<int>> face_edges_raw =
    std::vector<std::vector<int>>(face_num, std::vector<int>(0));
  edge_neighbors_ = std::vector<std::vector<int>>(0);
  edge_neighbors_.reserve(edges.size());
  int eid = 0;
  for (const auto& pair : edges) {
    const auto fid = pair.second;
    if (fid.size() == 1u) {
      common::PrintError("mesh::TriMesh: mesh is not watertight.");
    } else if (fid.size() == 2u) {
      const int i = fid[0], j = fid[1];
      face_neighbors_[i].push_back(j);
      face_neighbors_[j].push_back(i);
      edge_neighbors_.push_back({ i, j });
      face_edges_raw[i].push_back(eid);
      face_edges_raw[j].push_back(eid);
    } else {
      common::PrintError("mesh::TriMesh: mesh is not a manifold.");
    }
    ++eid;
  }
  face_edges_ = std::vector<Eigen::Vector3i>(0);
  face_edges_.reserve(face_num);
  for (const auto& e : face_edges_raw) {
    if (e.size() != 3u) {
      common::PrintError("mesh::TriMesh: each face should be a triangle.");
    }
    face_edges_.push_back(Eigen::Vector3i(e[0], e[1], e[2]));
  }
  // Check if the mesh is a single connected component.
  std::string visited(face_num, '0');
  std::queue<int> todo;
  todo.push(0);
  visited[0] = '1';
  while (!todo.empty()) {
    const int head = todo.front();
    todo.pop();
    // Consider its three neighbors.
    for (const int idx : face_neighbors_[head]) {
      if (visited[idx] == '1') continue;
      visited[idx] = '1';
      todo.push(idx);
    }
  }
  if (visited.find_first_of('0') != std::string::npos) {
    common::PrintError("mesh::TriMesh: not a single connected component.");
  }
}

void TriMesh::SampleWithFullRandomness(const double density,
  Eigen::Matrix3Xd& points, Eigen::Matrix3Xd& normals,
  Eigen::VectorXi& point_to_face) const {
  const int face_num = NumOfFaces();
  // Estimate the number of samples for each area.
  const double total_area = areas_.sum();
  const int total_num = static_cast<int>(total_area * density);
  std::vector<double> cutoff(face_num, 0.0);
  // Area i is sampled if cutoff[i - 1] < p <= cutoff[i].
  cutoff[0] = areas_(0) / total_area;
  for (int i = 1; i < face_num; ++i) {
    cutoff[i] = cutoff[i - 1] + areas_(i) / total_area;
  }
  cutoff.back() = 1.0;
  // Clamp for safety.
  for (double& prob : cutoff) {
    if (prob < 0.0) prob = 0.0;
    if (prob > 1.0) prob = 1.0;
  }

  // Sampling.
  std::vector<double> points_raw, normals_raw;
  std::vector<int> point_to_face_raw;
  const Eigen::VectorXd random_seed = Eigen::VectorXd::Random(total_num);
  for (int i = 0; i < total_num; ++i) {
    double prob = random_seed(i) * 0.5f + 0.5;
    // Make sure it is between 0 and 1.
    if (prob < 0.0) prob = 0.0;
    if (prob > 1.0) prob = 1.0;
    const auto ptr = std::lower_bound(cutoff.begin(), cutoff.end(), prob);
    // ptr points to the first element that is >= prob.
    const int idx = static_cast<int>(ptr - cutoff.begin());
    if (ptr == cutoff.end() || idx < 0 || idx >= face_num) {
      std::ostringstream ss;
      ss << "mesh::TriMesh::Sample: probability goes beyond 0 and 1: " << prob;
      common::PrintError(ss.str());
    }
    // Bad faces always have zero normals and good faces always have a unit
    // normal.
    if (face_normals_.col(i).norm() < common::Epsilon()) continue;
    const Eigen::Matrix3d triangle = Triangle(idx);
    const Eigen::Vector3d v0 = triangle.col(0), v1 = triangle.col(1),
      v2 = triangle.col(2);
    const Eigen::Matrix3Xd point = common::UniformSampleFromTriangle(
      v0, v1, v2, 1);
    for (int j = 0; j < 3; ++j) {
      points_raw.push_back(point(j, 0));
      normals_raw.push_back(face_normals_(j, idx));
    }
    point_to_face_raw.push_back(idx);
  }
  points = Eigen::Map<Eigen::Matrix3Xd>(points_raw.data(), 3,
    points_raw.size() / 3u);
  normals = Eigen::Map<Eigen::Matrix3Xd>(normals_raw.data(), 3,
    normals_raw.size() / 3u);
  point_to_face = Eigen::Map<Eigen::VectorXi>(point_to_face_raw.data(),
    point_to_face_raw.size());
}

void TriMesh::SampleWithoutFullRandomness(const double density,
  Eigen::Matrix3Xd& points, Eigen::Matrix3Xd& normals,
  Eigen::VectorXi& point_to_face) const {
  std::vector<double> points_raw, normals_raw;
  std::vector<int> point_to_face_raw;
  const int face_num = NumOfFaces();
  for (int i = 0; i < face_num; ++i) {
    // Bad faces always have zero normals and good faces always have a unit
    // normal.
    if (face_normals_.col(i).norm() < common::Epsilon()) continue;
    int sample_num = static_cast<int>(areas_(i) * density + 0.5);
    // Make sure we always see a sample.
    if (sample_num == 0) sample_num = 1;
    const Eigen::Matrix3d triangle = Triangle(i);
    const Eigen::Vector3d v0 = triangle.col(0), v1 = triangle.col(1),
      v2 = triangle.col(2);
    const Eigen::Matrix3Xd point = common::UniformSampleFromTriangle(
      v0, v1, v2, sample_num);
    for (int j = 0; j < sample_num; ++j) {
      for (int k = 0; k < 3; ++k) {
        points_raw.push_back(point(k, j));
        normals_raw.push_back(face_normals_(k, i));
      }
      point_to_face_raw.push_back(i);
    }
  }
  points = Eigen::Map<Eigen::Matrix3Xd>(points_raw.data(), 3,
    points_raw.size() / 3u);
  normals = Eigen::Map<Eigen::Matrix3Xd>(normals_raw.data(), 3,
    normals_raw.size() / 3u);
  point_to_face = Eigen::Map<Eigen::VectorXi>(point_to_face_raw.data(),
    point_to_face_raw.size());
}

}
