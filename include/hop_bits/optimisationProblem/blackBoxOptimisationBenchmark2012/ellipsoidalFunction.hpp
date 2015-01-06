#pragma once

// HOP
#include <hop_bits/optimisationProblem/blackBoxOptimisationBenchmark2012.hpp>

namespace hop {
  namespace bbob2012 {
    class EllipsoidalFunction : public BlackBoxOptimisationBenchmark2012 {
      public:
        using BlackBoxOptimisationBenchmark2012::BlackBoxOptimisationBenchmark2012;

        EllipsoidalFunction(const EllipsoidalFunction&) = delete;
        EllipsoidalFunction& operator=(const EllipsoidalFunction&) = delete;

        std::string to_string() const noexcept override;

      protected:
        const arma::Col<double> scaling_ = getScaling(1000000.0);

        double getObjectiveValueImplementation(
            const arma::Col<double>& parameter) const noexcept override;

        friend class cereal::access;

        template <typename Archive>
        void serialize(Archive& archive) noexcept {
          archive(cereal::make_nvp("BlackBoxOptimisationBenchmark2012", cereal::base_class<BlackBoxOptimisationBenchmark2012>(this)));
          archive(cereal::make_nvp("numberOfDimensions", numberOfDimensions_));
          archive(cereal::make_nvp("translation", translation_));
        }

        template <typename Archive>
        static void load_and_construct(
            Archive& archive,
            cereal::construct<EllipsoidalFunction>& construct) noexcept {
          unsigned int numberOfDimensions;
          archive(cereal::make_nvp("numberOfDimensions", numberOfDimensions));
          construct(numberOfDimensions);

          archive(cereal::make_nvp("BlackBoxOptimisationBenchmark2012", cereal::base_class<BlackBoxOptimisationBenchmark2012>(construct.ptr())));
          archive(cereal::make_nvp("translation", construct->translation_));
        }
    };
  }
}
