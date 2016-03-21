#pragma once

// Armadillo
#include <armadillo>

// Mantella
#include "mantella_bits/optimisationAlgorithm.hpp"

namespace mant {
  class OptimisationProblem;
}

namespace mant {
  class CovarianceMatrixAdaptationEvolutionStrategy : public OptimisationAlgorithm {
   public:
    explicit CovarianceMatrixAdaptationEvolutionStrategy();

    void initialise(
        const arma::uword numberOfDimensions,
        const arma::Mat<double>& initialParameters) override;

    void optimise(
        OptimisationProblem& optimisationProblem);
    void optimise(
        OptimisationProblem& optimisationProblem,
        const arma::uword populationSize);
    void optimise(
        OptimisationProblem& optimisationProblem,
        const arma::Col<double>& meanParameter);
    void optimise(
        OptimisationProblem& optimisationProblem,
        const arma::Mat<double>& initialParameters);
    void optimise(
        OptimisationProblem& optimisationProblem,
        const arma::Col<double>& meanParameter,
        const arma::uword populationSize);

    void setInitialStepSize(const double initialStepSize); //insigma
    double getInitialStepSize();
    double getStepSize();
    void setPopulationSize(const arma::uword populationSize, const arma::uword numberOfDimensions);
    arma::uword getPopulationSize();

    double getCcov1() const;
    void setCcov1(double ccov1);
    double getCcovmu() const;
    void setCcovmu(double ccovmu);
    double getCcum() const;
    void setCcum(double ccum);
    double getCs() const;
    void setCs(double cs);
    arma::uword getMu() const;
    void setMu(arma::uword numberOfParents);
    arma::Col<double> getRecombinationWeights();
    void setRecombinationWeights(arma::Col<double> weights);
    arma::Col<double> getXmean() const;
    void setXmean(arma::Col<double> xmean);

    arma::Mat<double> newGeneration_;

   protected:
    //Notation: comments always start with matlab name of variable
    //          comments after ';' are from matlab code
    //          comments after '-' are from mantella

    arma::uword mu_; //defopts.ParentNumber/mu
    double mueff_; //mueff
    arma::Col<double> recombinationWeights_; //weights
    double cs_; //defopts.CMA.cs/cs; cumulation constant for step-size
    double damping_; //defopts.CMA.damps; damping for step-size
    double ccum_; //defopts.CMA.ccum/cc;
    double ccov1_; //defopts.CMA.ccov1;
    double ccovmu_; //defopts.CMA.ccovmu;

    //arxvalid needs to be here so it is available after the loop
    arma::Mat<double> newGenerationRaw_;

    arma::Mat<double> newGenerationValid_; //arxvalid
    arma::Col<double> xmean_; //xmean
    arma::Col<double> xold_; //xold
    arma::uword populationSizeLast_;
    arma::uword populationSize_; //population size
    double stepSize_; //sigma
    double initialStepSize_;
    arma::Col<double> pc_; //pc; evolution path for C
    arma::Col<double> ps_; //ps; evolution path for sigma
    arma::Mat<double> B_; //B
    arma::Mat<double> C_; //C
    arma::Mat<double> D_; //D
    arma::Mat<double> BD_; //BD
    arma::Col<double> diagC_; //diagC
    arma::Col<double> diagD_; //diagD; diagonal matrix D defines the scaling
    double chiN_; //chiN
    double negCcov_; //neg.ccov
  };
}
