#include <mantella_bits/propertyAnalysis/passivePropertyAnalysis/quadraticFunctionModelAnalysis.hpp>

// C++ standard library
#include <cassert>

namespace mant {
  QuadraticFunctionModelAnalysis::QuadraticFunctionModelAnalysis(
      const std::unordered_map<arma::Col<double>, double, Hash, IsEqual>& samples) 
    : PassivePropertyAnalysis(samples),
      quadraticCoefficients_(numberOfDimensions_, numberOfDimensions_),
      errorTerm_(0),
      residuals_(samples_.size()) {
    
  }

  void QuadraticFunctionModelAnalysis::analyseImplementation() {
    assert(samples_.size() > 1);
    
    arma::Mat<double> parameters(numberOfDimensions_ * (numberOfDimensions_ + 3) / 2 + 1, samples_.size());
    arma::Col<double> objectiveValues(parameters.n_cols);
    arma::uword n = 0;
    for (const auto& sample : samples_) {
      const arma::Col<double>& parameter = sample.first;

      parameters.submat(0, n, numberOfDimensions_ - 1, n) = parameter;
      parameters.submat(numberOfDimensions_, n, 2 * numberOfDimensions_ - 1,  n) = arma::square(parameter);

      arma::uword k = 2 * numberOfDimensions_;
      for (arma::uword l = 0; l < numberOfDimensions_; ++l) {
        for (arma::uword m = l + 1; m < numberOfDimensions_; ++m) {
          parameters(k++, n) = parameter(l) * parameter(m);
        }
      }

      objectiveValues(n) = sample.second;
      ++n;
    }
    parameters.row(parameters.n_rows - 1).fill(1.0);
    
    arma::Col<double> model;
    try {
      model = (parameters * parameters.t()).i() * parameters * objectiveValues;
    } catch (...) {
      model = arma::pinv(parameters * parameters.t()) * parameters * objectiveValues;
    }
    
    quadraticCoefficients_.diag() = model.subvec(numberOfDimensions_, 2 * numberOfDimensions_ - 1);
    
    n = 2 * numberOfDimensions_;
    for (arma::uword k = 0; k < numberOfDimensions_; ++k) {
      for (arma::uword l = k + 1; l < numberOfDimensions_; ++l) {
        quadraticCoefficients_(k, l) = model(n++) / 2.0;
      }
    }
    quadraticCoefficients_ = arma::symmatu(quadraticCoefficients_);
    
    linearCoefficients_ = model.head(numberOfDimensions_);
    errorTerm_ = model(model.n_elem - 1);
    
    for (arma::uword n = 0; n < samples_.size(); ++n) {
      residuals_(n) = objectiveValues(n) - arma::dot(parameters.col(n), model);
    }
  }
      
  arma::Mat<double> QuadraticFunctionModelAnalysis::getQuadraticCoefficients() const {
    return quadraticCoefficients_;
  }
      
  arma::Col<double> QuadraticFunctionModelAnalysis::getLinearCoefficients() const {
    return linearCoefficients_;
  }
      
  double QuadraticFunctionModelAnalysis::getErrorTerm() const {
    return errorTerm_;
  }
  
  arma::Col<double> QuadraticFunctionModelAnalysis::getResiduals() const {
    return residuals_;
  }

  std::string QuadraticFunctionModelAnalysis::toString() const {
    return "quadratic_function_model_analysis";
  }
}