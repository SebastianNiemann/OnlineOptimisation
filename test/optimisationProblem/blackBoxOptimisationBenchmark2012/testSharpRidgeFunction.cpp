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

TEST_CASE("bbob2012::SharpRidgeFunction", "") {
  for (const auto& numberOfDimensions : {2, 40}) {
    mant::bbob2013::SharpRidgeFunction sharpRidgeFunction(numberOfDimensions);

    arma::Mat<double> parameters;
    parameters.load(testDirectory + "/data/optimisationProblem/blackBoxOptimisationBenchmark2013/parameters,dim" + std::to_string(numberOfDimensions) +".mat");

    arma::Col<double> translation;
    translation.load(testDirectory + "/data/optimisationProblem/blackBoxOptimisationBenchmark2013/translation,dim" + std::to_string(numberOfDimensions) +".mat");

    arma::Mat<double> rotationR;
    rotationR.load(testDirectory + "/data/optimisationProblem/blackBoxOptimisationBenchmark2013/rotationR,dim" + std::to_string(numberOfDimensions) +".mat");

    arma::Mat<double> rotationQ;
    rotationQ.load(testDirectory + "/data/optimisationProblem/blackBoxOptimisationBenchmark2013/rotationQ,dim" + std::to_string(numberOfDimensions) +".mat");

    arma::Col<double> expected;
    expected.load(testDirectory + "/data/optimisationProblem/blackBoxOptimisationBenchmark2013/expectedSharpRidgeFunction,dim" + std::to_string(numberOfDimensions) +".mat");

    sharpRidgeFunction.setObjectiveValueTranslation(0);
    sharpRidgeFunction.setTranslation(translation);
    sharpRidgeFunction.setRotationR(rotationR);
    sharpRidgeFunction.setRotationQ(rotationQ);

    for (std::size_t n = 0; n < parameters.n_cols; ++n) {
      CHECK(sharpRidgeFunction.getObjectiveValue(parameters.col(n)) == Approx(expected.at(n)));
    }
  }

  SECTION("Returns the specified class name.") {
    CHECK(mant::bbob2012::SharpRidgeFunction(5).to_string() == "SharpRidgeFunction");
  }
}