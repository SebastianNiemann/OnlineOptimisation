// Catch
#include <catch.hpp>

// C++ Standard Library
#include <cstdlib>
#include <string>

// Armadillo
#include <armadillo>

// Mantella
#include <mantella>

extern std::string testDirectory;

TEST_CASE("bbob2009::RastriginFunction", "") {
  for (const auto& numberOfDimensions : {2, 40}) {
    mant::bbob2009::RastriginFunction rastriginFunction(numberOfDimensions);

    arma::Mat<double> parameters;
    parameters.load(testDirectory + "/data/optimisationProblem/blackBoxOptimisationBenchmark2013/parameters,dim" + std::to_string(numberOfDimensions) +".mat");

    arma::Col<double> translation;
    translation.load(testDirectory + "/data/optimisationProblem/blackBoxOptimisationBenchmark2013/translation,dim" + std::to_string(numberOfDimensions) +".mat");

    arma::Col<double> expected;
    expected.load(testDirectory + "/data/optimisationProblem/blackBoxOptimisationBenchmark2013/expectedRastriginFunction,dim" + std::to_string(numberOfDimensions) +".mat");

    rastriginFunction.setObjectiveValueTranslation(0);
    rastriginFunction.setTranslation(translation);

    for (std::size_t n = 0; n < parameters.n_cols; ++n) {
      CHECK(rastriginFunction.getObjectiveValue(parameters.col(n)) == Approx(expected.at(n)));
    }
  }

  SECTION("Returns the specified class name.") {
    CHECK(mant::bbob2009::RastriginFunction(5).to_string() == "RastriginFunction");
  }
}