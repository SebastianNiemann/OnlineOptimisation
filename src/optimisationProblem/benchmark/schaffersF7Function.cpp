#include <hop_bits/optimisationProblem/benchmark/schaffersF7Function.hpp>

namespace hop {
  double SchaffersF7Function::getObjectiveValueImplementation(const arma::Col<double>& parameter) const {
    arma::Col<double> z = arma::square(delta_ % (rotationQ_ * getAsymmetricTransformation(0.5, rotationR_ * (parameter - translation_))));
    arma::Col<double> s = arma::pow(z.subvec(0, z.n_elem - 2) + z.subvec(1, z.n_elem - 1), 0.25);

    return std::pow(arma::mean(s % (1 + arma::square(arma::sin(50 * arma::pow(s, 0.4))))), 2) + 10.0 * getPenality(parameter);
  }
}
