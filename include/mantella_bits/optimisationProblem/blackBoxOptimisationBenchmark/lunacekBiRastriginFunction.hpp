#pragma once

// Armadillo
#include <armadillo>

// Mantella
#include "mantella_bits/optimisationProblem/blackBoxOptimisationBenchmark.hpp"

namespace mant {
  namespace bbob {
    class LunacekBiRastriginFunction : public BlackBoxOptimisationBenchmark {
     public:
      explicit LunacekBiRastriginFunction(
          const arma::uword numberOfDimensions);

     protected:
      const double s_;
      const double mu_;
      const arma::vec parameterConditinong_;
      // Keeps randomly set data non-`const`, to be set within tests and Mex files.
      arma::mat rotationQ_;
      arma::mat rotationR_;
    };
  }
}
