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

TEST_CASE("bbob2015::LunacekBiRastriginFunction", "") {
  for (const auto& numberOfDimensions : {2, 40}) {
    mant::bbob2015::LunacekBiRastriginFunction lunacekBiRastriginFunction(numberOfDimensions);

    arma::Mat<double> parameters;
    parameters.load(testDirectory + "/data/optimisationProblem/blackBoxOptimisationBenchmark2015/parameters,dim" + std::to_string(numberOfDimensions) +".mat");

    arma::Col<double> one;
    one.load(testDirectory + "/data/optimisationProblem/blackBoxOptimisationBenchmark2015/one,dim" + std::to_string(numberOfDimensions) +".mat");

    arma::Mat<double> rotationR;
    rotationR.load(testDirectory + "/data/optimisationProblem/blackBoxOptimisationBenchmark2015/rotationR,dim" + std::to_string(numberOfDimensions) +".mat");

    arma::Mat<double> rotationQ;
    rotationQ.load(testDirectory + "/data/optimisationProblem/blackBoxOptimisationBenchmark2015/rotationQ,dim" + std::to_string(numberOfDimensions) +".mat");

    arma::Col<double> expected;
    expected.load(testDirectory + "/data/optimisationProblem/blackBoxOptimisationBenchmark2015/expectedLunacekBiRastriginFunction,dim" + std::to_string(numberOfDimensions) +".mat");

    lunacekBiRastriginFunction.setObjectiveValueTranslation(0);
    lunacekBiRastriginFunction.setOne(one);
    lunacekBiRastriginFunction.setRotationR(rotationR);
    lunacekBiRastriginFunction.setRotationQ(rotationQ);

    for (std::size_t n = 0; n < parameters.n_cols; ++n) {
      CHECK(lunacekBiRastriginFunction.getObjectiveValue(parameters.col(n)) == Approx(expected.at(n)));
    }
  }

  SECTION("Returns the specified class name.") {
    CHECK(mant::bbob2015::LunacekBiRastriginFunction(5).to_string() == "LunacekBiRastriginFunction");
  }
}