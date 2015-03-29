namespace mant {
  template <typename ParameterType>
  class RandomSearch : public SamplingBasedOptimisationAlgorithm<ParameterType> {
    public:
      explicit RandomSearch(
          const std::shared_ptr<OptimisationProblem<ParameterType>> optimisationProblem) noexcept;

      std::string toString() const noexcept override;

    protected:
      void optimiseImplementation() noexcept override;
  };

  //
  // Implementation
  //

  template <typename ParameterType>
  RandomSearch<ParameterType>::RandomSearch(
      const std::shared_ptr<OptimisationProblem<ParameterType>> optimisationProblem) noexcept
    : SamplingBasedOptimisationAlgorithm<ParameterType>(optimisationProblem) {

  }

  template <typename ParameterType>
  void RandomSearch<ParameterType>::optimiseImplementation() noexcept {
    while(!this->isFinished() && !this->isTerminated()) {
      ++this->numberOfIterations_;

      const arma::Col<ParameterType>& candidateParameter = this->distanceFunction_.getRandomNeighbour(this->getLowerBounds(), this->getUpperBounds() - this->getLowerBounds());
      const double& candidateSoftConstraintsValue = this->getSoftConstraintsValue(candidateParameter);
      const double& candidateObjectiveValue = this->getObjectiveValue(candidateParameter);

      if(candidateSoftConstraintsValue < this->bestSoftConstraintsValue_ || (candidateSoftConstraintsValue == this->bestSoftConstraintsValue_ && candidateObjectiveValue < this->bestObjectiveValue_)) {
        this->bestParameter_ = candidateParameter;
        this->bestSoftConstraintsValue_ = candidateSoftConstraintsValue;
        this->bestObjectiveValue_ = candidateObjectiveValue;
      }
    };
  }

  template <typename ParameterType>
  std::string RandomSearch<ParameterType>::toString() const noexcept {
    return "RandomSearch";
  }
}