#ifndef _COMMON_POLYNOMIAL_H_
#define _COMMON_POLYNOMIAL_H_

#include <vector>
#include "Eigen/Dense"

namespace common {

class Polynomial {
public:
  Polynomial();
  explicit Polynomial(const std::vector<double>& coeffs);
  explicit Polynomial(const Eigen::VectorXd& coeffs);
  // f(x) = a0.
  explicit Polynomial(const double a0);
  // f(x) = a0 + a1 * x.
  Polynomial(const double a0, const double a1);
  // f(x) = a0 + a1 * x + a2 * x^2.
  Polynomial(const double a0, const double a1, const double a2);

  const std::vector<double>& coeffs() const;
  const int Degree() const;

  Polynomial& operator+=(const double a0);
  Polynomial& operator+=(const Polynomial& other);
  Polynomial& operator-=(const double a0);
  Polynomial& operator-=(const Polynomial& other);
  Polynomial& operator*=(const double a0);
  Polynomial& operator*=(const Polynomial& other);

  // Return f(x).
  const double operator()(const double x) const;
  // Return all real roots in sorted order.
  const std::vector<double> Roots() const;

private:
  void RemoveTrailingZero();

  std::vector<double> coeffs_;
};

const Polynomial operator+(const Polynomial& f, const Polynomial& g);
const Polynomial operator+(const Polynomial& f, const double a0);
const Polynomial operator+(const double a0, const Polynomial& f);
const Polynomial operator-(const Polynomial& f, const Polynomial& g);
const Polynomial operator-(const Polynomial& f, const double a0);
const Polynomial operator-(const double a0, const Polynomial& f);
const Polynomial operator*(const Polynomial& f, const Polynomial& g);
const Polynomial operator*(const Polynomial& f, const double a0);
const Polynomial operator*(const double a0, const Polynomial& f);

}

#endif