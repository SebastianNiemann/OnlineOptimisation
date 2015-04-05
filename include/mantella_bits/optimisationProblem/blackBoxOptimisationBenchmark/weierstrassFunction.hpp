namespace mant {
  namespace bbob {
    class WeierstrassFunction : public BlackBoxOptimisationBenchmark {
      public:
        inline explicit WeierstrassFunction(
            const unsigned int numberOfDimensions) noexcept;

        inline void setParameterRotationR(
            const arma::Mat<double>& parameterRotationR);

        inline void setRotationQ(
            const arma::Mat<double>& rotationQ);
            
        inline std::string toString() const noexcept override;

      protected:
        const double f0_;
        const arma::Col<double> parameterConditioning_;

        arma::Mat<double> parameterRotationR_;
        arma::Mat<double> rotationQ_;

        inline double getSoftConstraintsValueImplementation(
            const arma::Col<double>& parameter) const noexcept override;

        inline double getObjectiveValueImplementation(
            const arma::Col<double>& parameter) const noexcept override;

#if defined(MANTELLA_USE_PARALLEL)
        friend class cereal::access;

        template <typename Archive>
        void serialize(
            Archive& archive) noexcept {
          archive(cereal::make_nvp("BlackBoxOptimisationBenchmark", cereal::base_class<BlackBoxOptimisationBenchmark>(this)));
          archive(cereal::make_nvp("numberOfDimensions", numberOfDimensions_));
          archive(cereal::make_nvp("parameterRotationR", parameterRotationR_));
          archive(cereal::make_nvp("rotationQ", rotationQ_));
        }

        template <typename Archive>
        static void load_and_construct(
            Archive& archive,
            cereal::construct<WeierstrassFunction>& construct) noexcept {
          unsigned int numberOfDimensions;
          archive(cereal::make_nvp("numberOfDimensions", numberOfDimensions));
          construct(numberOfDimensions);

          archive(cereal::make_nvp("BlackBoxOptimisationBenchmark", cereal::base_class<BlackBoxOptimisationBenchmark>(construct.ptr())));
          archive(cereal::make_nvp("parameterRotationR", construct->parameterRotationR_));
          archive(cereal::make_nvp("rotationQ", construct->rotationQ_));
        }
#endif
    };

    //
    // Implementation
    //

    inline WeierstrassFunction::WeierstrassFunction(
        const unsigned int numberOfDimensions) noexcept
      : BlackBoxOptimisationBenchmark(numberOfDimensions),
        f0_(-1.99951171875),
        parameterConditioning_(getParameterConditioning(std::sqrt(0.01))) {
      setParameterTranslation(getRandomParameterTranslation());
      setParameterRotationR(getRandomRotationMatrix(numberOfDimensions_));
      setRotationQ(getRandomRotationMatrix(numberOfDimensions_));
    }

    inline void WeierstrassFunction::setParameterRotationR(
        const arma::Mat<double>& parameterRotationR) {
      isEqual("The number of rows", parameterRotationR.n_rows, "the number of dimensions", numberOfDimensions_);
      isRotationMatrix("The matrix", parameterRotationR);

      parameterRotationR_ = parameterRotationR;
    }

    inline void WeierstrassFunction::setRotationQ(
        const arma::Mat<double>& rotationQ) {
      isEqual("The number of rows", rotationQ.n_rows, "the number of dimensions", numberOfDimensions_);
      isRotationMatrix("The matrix", rotationQ);

      rotationQ_ = rotationQ;
    }

    inline double WeierstrassFunction::getSoftConstraintsValueImplementation(
        const arma::Col<double>& parameter) const noexcept {
      return 10.0 * getBoundConstraintsValue(parameter) / static_cast<double>(numberOfDimensions_);
    }
    
    inline double WeierstrassFunction::getObjectiveValueImplementation(
        const arma::Col<double>& parameter) const noexcept {
      const arma::Col<double>& z = parameterRotationR_ * (parameterConditioning_ % (parameterRotationQ_ * getOscillatedParameter(parameterRotationR_ * parameter)));

      double sum = 0.0;
      for (std::size_t n = 0; n < parameter.n_elem; ++n) {
        for (unsigned int k = 0; k < 12; ++k) {
          sum += std::pow(0.5, k) * std::cos(2.0 * arma::datum::pi * std::pow(3.0, k) * (z(n) + 0.5));
        }
      }

      return 10 * std::pow(sum / static_cast<double>(numberOfDimensions_) - f0_, 3);
    }

    inline std::string WeierstrassFunction::toString() const noexcept {
      return "bbob_weierstrass_function";
    }
  }
}

#if defined(MANTELLA_USE_PARALLEL)
CEREAL_REGISTER_TYPE(mant::bbob::WeierstrassFunction);
#endif
