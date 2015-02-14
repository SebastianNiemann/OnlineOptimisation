namespace mant {
  class CovarianceMatrixAdaptationEvolutionStrategy : public PopulationBasedAlgorithm<double> {
    public:
      //TODO: which input parameters should be added to the constructor?
      inline explicit CovarianceMatrixAdaptationEvolutionStrategy(
        const std::shared_ptr<OptimisationProblem<double>> optimisationProblem,
          const unsigned int& populationSize) noexcept;

      inline void setStepsize(
          const double& sigma) noexcept;

      inline std::string to_string() const noexcept override;

    protected:
      double stepSize_;

      inline void optimiseImplementation() override;
  };

  //
  // Implementation
  //

  inline CovarianceMatrixAdaptationEvolutionStrategy::CovarianceMatrixAdaptationEvolutionStrategy(
     const std::shared_ptr<OptimisationProblem<double>> optimisationProblem,
      const unsigned int& populationSize) noexcept
  : PopulationBasedAlgorithm<double>(optimisationProblem, populationSize) {
    setStepsize(0.3);
  }

  inline void CovarianceMatrixAdaptationEvolutionStrategy::optimiseImplementation() {
    unsigned int numberOfDimensions = this->optimisationProblem_->getNumberOfDimensions();
    arma::Col<double> objectiveValues = arma::randu<arma::Col<double>>(numberOfDimensions);

    //init selection parameters
    //unsigned int lambda_ = 4 + std::floor(3 * std::log(numberOfDimensions)); //overwritten by constructor value
    unsigned int numberOfParents = this->populationSize_ / 2.0;

    arma::Col<double> weights = arma::normalise(std::log((this->populationSize_ + 1.0) / 2.0) - arma::log(arma::linspace(1, std::floor(numberOfParents), std::floor(numberOfParents))), 1);

    double varianceEffectiveness = std::pow(arma::sum(weights), 2.0) / std::pow(arma::norm(weights), 2.0);
    //init adaptation parameters
    double cc = (4.0 + varianceEffectiveness) / (numberOfDimensions + 4.0 + 2.0 * varianceEffectiveness); //time constant for cumulation for C
    double cs = (varianceEffectiveness + 2.0) / (numberOfDimensions + varianceEffectiveness + 5.0); //t-const for cumulation for sigma control
    double c1 = 2.0 / (std::pow(numberOfDimensions + 1.3, 2.0) + varianceEffectiveness); //learning rate for rank-one update of C
    double cmu = std::min(1 - c1, 2 * (varianceEffectiveness - 2.0 + 1.0) / (varianceEffectiveness * (std::pow(numberOfDimensions + 2.0, 2.0) + 1.0))); //and for rank-mu update
    double damps = 1.0 + 2.0 * std::max(0.0, std::sqrt((varianceEffectiveness - 1.0) / (numberOfDimensions + 1.0)) - 1.0) + cs; //damping for sigma
    //init dynamic parameters and constants
    arma::Col<double> pc(numberOfDimensions, arma::fill::zeros);
    arma::Col<double> ps(numberOfDimensions, arma::fill::zeros);
    arma::Mat<double> B(numberOfDimensions, numberOfDimensions, arma::fill::eye);
    arma::Col<double> D(numberOfDimensions, arma::fill::ones);
    arma::Mat<double> C(numberOfDimensions, numberOfDimensions, arma::fill::eye);
    arma::Mat<double> invsqrtC(numberOfDimensions, numberOfDimensions, arma::fill::eye);
    double chiN = std::sqrt(numberOfDimensions) * (1.0 - (1.0 / (4.0 * numberOfDimensions)) + (1.0 / (21.0 * std::pow(numberOfDimensions, 2.0))));
    unsigned int numberOfDecompositions = 0;

    //LOOP START
    while (!this->isFinished() && !this->isTerminated()) {
      //generate and evaluate lambda offspring
      arma::Col<double> arfitness(this->populationSize_);
      arma::Mat<double> arx(numberOfDimensions, this->populationSize_);
      for (std::size_t n = 0; n < this->populationSize_; ++n) {
        arx.col(n) = objectiveValues + stepSize_ * B * (D % arma::randn<arma::Col<double>>(numberOfDimensions));
        arfitness(n) = this->optimisationProblem_->getObjectiveValue(arx.col(n));
        ++this->numberOfIterations_;

        //TODO: Consider soft-constraints.
        //TODO: For performance, this could be done in another loop after the best have been selected. Not sure if really worth it
        if (arfitness(n) < this->bestObjectiveValue_) {
          this->bestObjectiveValue_ = arfitness(n);
          this->bestParameter_ = arx.col(n);
          //otherwise it's always infinity, so isFinished() doesn't work ;)
          this->bestSoftConstraintsValue_ = 0.0;
        }

        if (this->isFinished() || this->isTerminated()) {
          break;
        }
      }

      //sort by fitness and compute weighted mean into objectiveValues
      arma::Col<unsigned int> arindex = static_cast<arma::Col<unsigned int>>(arma::sort_index(arfitness)).head(numberOfParents);
      arma::Col<double> oldObjectiveValues = objectiveValues;

      objectiveValues = arx.cols(arindex) * weights;

      //cumulation: update evolution paths
      ps = (1.0 - cs) * ps + std::sqrt(cs * (2.0 - cs) * varianceEffectiveness) * invsqrtC * (objectiveValues - oldObjectiveValues) / stepSize_;
      //original matlab line: hsig = norm(ps)/sqrt(1-(1-cs)^(2*numberOfIterations_/lambda))/chiN < 1.4 + 2/(numberOfDimensions+1);
      double hsigLeftSide = (arma::norm(ps) / std::sqrt(1.0 - std::pow((1.0 - cs), 2.0 * static_cast<double>(this->numberOfIterations_) / static_cast<double>(this->populationSize_)))) / chiN;
      double hsigRightSide = 1.4 + 2 / (numberOfDimensions + 1.0);
      double hsig = hsigLeftSide < hsigRightSide;

      pc = (1.0 - cc) * pc + hsig * std::sqrt(cc * (2.0 - cc) * varianceEffectiveness) * (objectiveValues - oldObjectiveValues) / stepSize_;

      //adapt covariance matrix C
      // TODO Relace repmat, as this might be the most time consuming task (besides the decomposition)
      arma::Mat<double> artmp = (1.0 / stepSize_) * arx.cols(arindex) - arma::repmat(oldObjectiveValues, 1, numberOfParents);
      C = (1.0 - c1 - cmu) * C + //old matrix
          c1 * (pc * pc.t() + //rank one update
          (1.0 - hsig) * cc * (2.0 - cc) * C) + //correction for hsig==0
          cmu * artmp * arma::diagmat(weights) * artmp.t(); // rank mu update

      //adapt stepsize sigma
      stepSize_ = stepSize_ * std::exp((cs / damps) * (arma::norm(ps) / chiN - 1.0));

      //decomposition of C into B*diag(D.^2)*B' (diagonalization)
      if (this->numberOfIterations_ - numberOfDecompositions > 10.0 * stepSize_ / ((c1 + cmu) * static_cast<double>(numberOfDimensions))) {
        numberOfDecompositions = this->numberOfIterations_;
        C = arma::symmatu(C);
        //matlab code is [B,D] = eig(C); arma uses switched arguments
        arma::eig_sym(D, B, C);
        D = arma::sqrt(D);
        invsqrtC = B * arma::diagmat(static_cast<arma::Col<double>>(1.0 / D)) * B.t();
      }
    }
    //LOOP END
  }

  inline void CovarianceMatrixAdaptationEvolutionStrategy::setStepsize(
      const double& sigma) noexcept {
    stepSize_ = sigma;
  }

  inline std::string CovarianceMatrixAdaptationEvolutionStrategy::to_string() const noexcept {
    return "CovarianceMatrixAdaptationEvolutionStrategy";
  }
}