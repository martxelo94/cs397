#include "Regression.h"
namespace CS397
{
    Regression::Regression(const Dataset &      _dataset,  // Dataset that the regression will learn from
                   const std::vector<Feature> & _features, // Features
                   double                       _lr,       // Learning rate fo the linear regression
                   bool                         _meanNormalization)               // True if input data should be mean normalized
        : dataset(_dataset), features(_features), lr(_lr), meanNormalization(_meanNormalization)
    {
    
    }

        // Given a single or multiple input datapoint(s), computes the value(s) that the linear regression would predict
    double              Regression::Predict(const std::vector<double> & input_attributes) const
    {
        //_ASSERT((features.size() - 1) == input_attributes.size());
        double h = 0.0;
        for(int i = 0; i < (int)features.size(); ++i) {
            int idx = features[i].inputIdx;
            double h_i = features[i].theta;
            if(idx > -1) {
                _ASSERT(idx < (int)input_attributes.size());
                h_i *= pow(input_attributes[idx], features[i].power);
            }
            h += h_i;
        }
        return h;
    }
    std::vector<double> Regression::Predict(const std::vector<std::vector<double>> & input) const
    {
        std::vector<double> output;
        output.reserve(input.size());

        for(int i = 0; i < (int)input.size(); ++i) {
            double out = Predict(input[i]);
            output.push_back(out);
        }
        return output;
    }

    // Given the output predicted and the actual real value (target), computes the cost
    double Regression::Cost(const std::vector<double> & output,
                const std::vector<double> & target) const
    {
        _ASSERT(output.size() == target.size());
        double cost = 0.0;
        for(int i = 0; i < (int)output.size(); ++i) {
            double c = output[i] - target[i];
            cost += c * c;
        }
        cost = cost / (2.0 * output.size());
        return cost;
    }

    // delta cost for attribute
   double Regression::DeltaCost(const std::vector<double> & input,
                                const std::vector<double> & output,
                                const std::vector<double> & target) const
    {
        _ASSERT(input.size() == output.size());
        _ASSERT(input.size() == target.size());
        double dCost = 0.0;
        for(int i = 0; i < (int)input.size(); ++i) {
            dCost += (output[i] - target[i]) * input[i];
        }
        dCost = dCost / input.size();
        return dCost;
    }
    // delta cost for attribute
   double Regression::DeltaCost(const std::vector<double> & output,
                                const std::vector<double> & target) const
    {
        _ASSERT(output.size() == target.size());
        double dCost = 0.0;
        for(int i = 0; i < (int)output.size(); ++i) {
            dCost += (output[i] - target[i]);
        }
        dCost = dCost / output.size();
        return dCost;
    }
    // Linear regression values will be adjusted for the dataset using gradient descent.
    // Returns false when all derivatives are smaller than the minimum provided.
    bool Regression::Iteration(double minDerivative)
    {
        std::vector<double> output = Predict(dataset.input);
        std::vector<double> dCosts;
        dCosts.reserve(features.size());

        std::vector<double> input;  // columns of dataset.input (input/attr)
        input.reserve(dataset.input.size());
        for(int j = 0; j < (int)features.size(); ++j) {
            int feature_idx = features[j].inputIdx;
            double dCost = 0.0;
            if(feature_idx < 0) {
                dCost = DeltaCost(output, dataset.output);
            }
            else{
                // extract column from dataset.input 
                for(int i = 0; i < (int)dataset.input.size(); ++i)
                input.push_back(dataset.input[i][feature_idx]);
                dCost = DeltaCost(input, output, dataset.output);
            }
            dCosts.push_back(dCost);
            input.clear();  // reset column container
        }

        // update thetas
        for(int j = 0; j < (int)features.size(); ++j)
            features[j].theta -= lr * dCosts[j];

        // check derivatives
        int smallerDerivatives = 0;
        for(int j = 0; j < (int)dCosts.size(); ++j)
            if(abs(dCosts[j]) < minDerivative)
                smallerDerivatives++;
        if(smallerDerivatives == (int)dCosts.size())
            return false;
            
        ++current_iterations;
        if(current_iterations >= MAX_ITERATIONS -1)
            return false;
        return false;
    }


}   // namespace CS397
