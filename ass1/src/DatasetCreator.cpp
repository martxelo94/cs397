
#include "DatasetCreator.h"

#include <cmath>
#include <cstdlib>

namespace DatasetCreator
{
Dataset GenerateDataset(unsigned size, std::vector<FunctionFeature> & features, int numberInputs, double scale, double noise)
{
    Dataset dataset(size);

    for (unsigned i = 0; i < size; i++)
    {
        // generate random inputs
        std::vector<double> inputs(numberInputs);
        for (int j = 0; j < numberInputs; j++)
        {
            inputs[j] = (std::rand() * 1.0 / RAND_MAX) * scale;
        }

        // compute the output with the generated random input
        double y = noise * (std::rand() * 2.0 / RAND_MAX - 1.0);
        for (unsigned f = 0; f < features.size(); f++)
        {
            if (features[f].index < 0)
                y += features[f].weight;
            else
                y += std::pow(inputs[features[f].index], features[f].power) * features[f].weight;
        }

        dataset.input[i]  = inputs;
        dataset.output[i] = y;
    }

    return dataset;
}
} // namespace DatasetCreator