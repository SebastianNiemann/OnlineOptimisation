#include <hop_bits/optimisationProblem/benchmark/bentCigarFunction.hpp>

namespace hop {
  double BentCigarFunction::getObjectiveValueImplementation(const arma::Col<double>& parameter) const {
    arma::Col<double> z = arma::square(rotationR_ * getAsymmetricTransformation(0.5, rotationR_ * (parameter - translation_)));
    return z.at(0) + 1000000.0 * arma::accu(z.subvec(1, z.n_elem - 1));
  }
}
