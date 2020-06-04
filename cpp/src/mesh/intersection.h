#ifndef _MESH_INTERSECTION_H_
#define _MESH_INTERSECTION_H_

#include <iostream>

namespace mesh {

struct Intersection {
public:
  const bool uncertain() const;
  const bool hit() const;
  const double t() const;
  const bool outside() const;

  static const struct Intersection UncertainIntersection();
  static const struct Intersection NoIntersection();

  friend class TriMesh;

private:
  // There are singular cases where we cannot reliably tell whether an
  // intersection happens or not. All data members will be undetermined if
  // uncertain_ is true.
  bool uncertain_;
  // If hit_ = true, then t_ is finite and outside_ indicates whether the ray
  // is shooting from the outside of this triangle.
  // If hit_ = false, then both t_ and outside_ are undetermined.
  bool hit_;
  double t_;
  bool outside_;
};

std::ostream& operator<<(std::ostream& os,
  const struct Intersection& inter);

}

#endif
