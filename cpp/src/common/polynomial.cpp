#include "common/polynomial.h"
#include "unsupported/Eigen/Polynomials"

namespace common {

Polynomial::Polynomial()
  : coeffs_(1, 0) {}

Polynomial::Polynomial(const std::vector<double>& coeffs)
  : coeffs_(coeffs) {
  RemoveTrailingZero();
}

Polynomial::Polynomial(const Eigen::VectorXd& coeffs)
  : coeffs_(coeffs.data(), coeffs.data() + coeffs.size()) {
  RemoveTrailingZero();
}

Polynomial::Polynomial(const double a0)
  : coeffs_(1, a0) {}

Polynomial::Polynomial(const double a0, const double a1)
  : coeffs_(2, 0) {
  coeffs_[0] = a0; coeffs_[1] = a1;
  RemoveTrailingZero();
}

Polynomial::Polynomial(const double a0, const double a1, const double a2)
  : coeffs_(3, 0) {
  coeffs_[0] = a0; coeffs_[1] = a2; coeffs_[2] = a2;
  RemoveTrailingZero();
}

const std::vector<double>& Polynomial::coeffs() const {
  return coeffs_;
}

const int Polynomial::Degree() const {
  return static_cast<int>(coeffs_.size());
}

Polynomial& Polynomial::operator+=(const double a0) {
  coeffs_[0] += a0;
  return *this;
}

Polynomial& Polynomial::operator+=(const Polynomial& other) {
  const int deg = Degree();
  const int other_deg = other.Degree();
  const int new_deg = deg > other_deg ? deg : other_deg;
  std::vector<double> new_coeffs(new_deg, 0);
  for (int i = 0; i < deg; ++i) new_coeffs[i] += coeffs_[i];
  for (int i = 0; i < other_deg; ++i) new_coeffs[i] += other.coeffs()[i];
  coeffs_.swap(new_coeffs);
  RemoveTrailingZero();
  return *this;
}

Polynomial& Polynomial::operator-=(const double a0) {
  coeffs_[0] -= a0;
  return *this;
}

Polynomial& Polynomial::operator-=(const Polynomial& other) {
  const int deg = Degree();
  const int other_deg = other.Degree();
  const int new_deg = deg > other_deg ? deg : other_deg;
  std::vector<double> new_coeffs(new_deg, 0);
  for (int i = 0; i < deg; ++i) new_coeffs[i] += coeffs_[i];
  for (int i = 0; i < other_deg; ++i) new_coeffs[i] -= other.coeffs()[i];
  coeffs_.swap(new_coeffs);
  RemoveTrailingZero();
  return *this;
}

Polynomial& Polynomial::operator*=(const double a0) {
  for (double& c : coeffs_) c *= a0;
  RemoveTrailingZero();
  return *this;
}

Polynomial& Polynomial::operator*=(const Polynomial& other) {
  const int deg = Degree();
  const int other_deg = other.Degree();
  const int new_deg = deg + other_deg - 1;
  std::vector<double> new_coeffs(new_deg, 0);
  for (int i = 0; i < deg; ++i) {
    for (int j = 0; j < other_deg; ++j) {
      new_coeffs[i + j] += coeffs_[i] * other.coeffs()[j];
    }
  }
  coeffs_.swap(new_coeffs);
  RemoveTrailingZero();
  return *this;
}

const double Polynomial::operator()(const double x) const {
  return Eigen::poly_eval(Eigen::Map<const Eigen::VectorXd>(coeffs_.data(),
    coeffs_.size()), x);
}

const std::vector<double> Polynomial::Roots() const {
  Eigen::PolynomialSolver<double, Eigen::Dynamic> solver;
  solver.compute(Eigen::Map<const Eigen::VectorXd>(coeffs_.data(),
    coeffs_.size()));
  std::vector<double> roots(0);
  solver.realRoots(roots);
  std::sort(roots.begin(), roots.end());
  return roots;
}

void Polynomial::RemoveTrailingZero() {
  while (coeffs_.size() > 1u && coeffs_.back() == 0) coeffs_.pop_back();
}

const Polynomial operator+(const Polynomial& f, const Polynomial& g) {
  Polynomial f_copy = f;
  f_copy += g;
  return f_copy;
}

const Polynomial operator+(const Polynomial& f, const double a0) {
  Polynomial f_copy = f;
  f_copy += a0;
  return f_copy;
}

const Polynomial operator+(const double a0, const Polynomial& f) {
  return f + a0;
}

const Polynomial operator-(const Polynomial& f, const Polynomial& g) {
  Polynomial f_copy = f;
  f_copy -= g;
  return f_copy;
}

const Polynomial operator-(const Polynomial& f, const double a0) {
  Polynomial f_copy = f;
  f_copy -= a0;
  return f_copy;
}

const Polynomial operator-(const double a0, const Polynomial& f) {
  Polynomial f_copy = f;
  f_copy *= -1;
  f_copy += a0;
  return f_copy;
}

const Polynomial operator*(const Polynomial& f, const Polynomial& g) {
  Polynomial f_copy = f;
  f_copy *= g;
  return f_copy;
}

const Polynomial operator*(const Polynomial& f, const double a0) {
  Polynomial f_copy = f;
  f_copy *= a0;
  return f_copy;
}

const Polynomial operator*(const double a0, const Polynomial& f) {
  return f * a0;
}

}