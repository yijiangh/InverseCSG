#include "intersection.h"

namespace mesh {

const bool Intersection::uncertain() const {
  return uncertain_;
}

const bool Intersection::hit() const {
  return hit_;
}

const double Intersection::t() const {
  return t_;
}

const bool Intersection::outside() const {
  return outside_;
}

const struct Intersection Intersection::UncertainIntersection() {
  Intersection inter;
  inter.uncertain_ = true;
  return inter;
}

const struct Intersection Intersection::NoIntersection() {
  Intersection inter;
  inter.uncertain_ = false;
  inter.hit_ = false;
  return inter;
}

std::ostream& operator<<(std::ostream& os,
  const struct Intersection& inter) {
  os << "Uncertain: " << (inter.uncertain() ? "true" : "false") << "; "
    << "hit: " << (inter.hit() ? "true" : "false") << "; "
    << "t: " << inter.t() << "; "
    << "outside: " << (inter.outside() ? "true" : "false") << ".";
  return os;
}

}