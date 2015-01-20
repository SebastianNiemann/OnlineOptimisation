#include <mantella_bits/helper/random.hpp>

// C++ Standard Library
#include <cstdlib>
#include <cmath>
#include <stdexcept>
#include <algorithm>

// Mantella
#include <mantella_bits/helper/rng.hpp>

namespace mant {
  arma::Mat<double> getRandomRotationMatrix(
      const unsigned int& numberOfDimensions) noexcept {
    arma::Mat<double> Q;
    arma::Mat<double> R;

    if(arma::qr(Q, R, arma::randn<arma::Mat<double>>(numberOfDimensions, numberOfDimensions))) {
      return Q * arma::sign(arma::diagmat(R));
    } else {
      const arma::Col<double>& angles = arma::datum::pi * arma::randu<arma::Col<double>>(numberOfDimensions);
      const arma::Col<double>& sineAngles = arma::sin(angles);
      const arma::Col<double>& cosineAngles = arma::cos(angles);

      arma::Mat<double> rotationMatrix = arma::eye<arma::Mat<double>>(numberOfDimensions, numberOfDimensions);
      for(std::size_t n = 0; n < angles.n_elem; ++n) {
        arma::Mat<double> subRotationMatrix = arma::eye<arma::Mat<double>>(numberOfDimensions, numberOfDimensions);
        subRotationMatrix.at(0, 0) = sineAngles.at(n);
        subRotationMatrix.at(0, n) = cosineAngles.at(n);
        subRotationMatrix.at(n, 0) = cosineAngles.at(n);
        subRotationMatrix.at(n, n) = -sineAngles.at(n);

        rotationMatrix *= subRotationMatrix;
      }

      return rotationMatrix;
    }
  }

  arma::Col<unsigned int> getRandomPermutation(
      const unsigned int& numberOfElements,
      const unsigned int& cycleSize) {
    if(numberOfElements < cycleSize) {
      throw std::logic_error("The cycle size (" + std::to_string(cycleSize) + ") must be lower than or equal to the number of elements (" + std::to_string(numberOfElements) + ").");
    }

    arma::Col<unsigned int> permutation(numberOfElements);
    for (std::size_t n = 0; n < numberOfElements; ++n) {
      permutation.at(n) = n;
    }

    unsigned int length = std::min(cycleSize, numberOfElements - 1);
    for (std::size_t n = 0; n < length; ++n) {
      permutation.swap_rows(n, std::uniform_int_distribution<unsigned int>(n, length)(Rng::generator));
    }

    return permutation.head(cycleSize);
  }

  arma::Col<unsigned int> getRandomPermutation(
      const unsigned int& numberOfElements) noexcept {
    return getRandomPermutation(numberOfElements, numberOfElements);
  }
}
