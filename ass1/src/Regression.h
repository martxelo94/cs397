//---------------------------------------------------------------------------
#ifndef REGRESSION_H
#define REGRESSION_H
//---------------------------------------------------------------------------

#include "DatasetCreator.h"

namespace CS397
{

struct Feature
{
    int    inputIdx; // Index of the input this feature refers to (negative index means intercept)
    int    power;    // Power of the feature
    double theta;    // Constant multiplier of the feature (what the algorithm will adjust)
};

class Regression
{
  public:
    // Constructor
    Regression(const Dataset &              _dataset,  // Dataset that the regression will learn from
               const std::vector<Feature> & _features, // Features
               double                       _lr,       // Learning rate fo the linear regression
               bool                         _meanNormalization); // True if input data should be mean normalized

    // Given a single or multiple input datapoint(s), computes the value(s) that the linear regression would predict
    double              Predict(const std::vector<double> & input) const;
    std::vector<double> Predict(const std::vector<std::vector<double>> & input) const;

    // Given the output predicted and the actual real value (target), computes the cost
    double Cost(const std::vector<double> & output,
                const std::vector<double> & target) const;

    // Linear regression values will be adjusted for the dataset using gradient descent.
    // Returns false when all derivatives are smaller than the minimum provided.
    bool Iteration(double minDerivative = 0.01);

  private:

   double DeltaCost(const std::vector<double> & input,
                    const std::vector<double> & output,
                    const std::vector<double> & target) const;

  // for intercept variable
   double Regression::DeltaCost(const std::vector<double> & output,
                                const std::vector<double> & target) const;

    Dataset dataset;
    std::vector<Feature> features;
    double lr;  // Learning rate
    bool meanNormalization; // True if input data should be mean normalized

    const int MAX_ITERATIONS = 10000;  // avoid infinite loop
    int current_iterations = 0;

};

} // namespace CS397
#endif