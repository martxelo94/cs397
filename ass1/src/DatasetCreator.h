//---------------------------------------------------------------------------
#ifndef DATASET_CREATION_H
#define DATASET_CREATION_H
//---------------------------------------------------------------------------

#include <vector>
#include <algorithm>

// Dataset type contains the input data
// and the output stores all the outputs (both vectors should always same size)
struct Dataset
{
    Dataset(const Dataset & copy, size_t from, size_t size) :
        input(size),
        output(size)
    {
        std::copy_n(copy.input.begin() + from, size, input.begin());
        std::copy_n(copy.output.begin() + from, size, output.begin());
    }

    Dataset(size_t size = 0) :
        input(size),
        output(size)
    {
    }

    std::vector<std::vector<double>> input;
    std::vector<double>              output;
};

namespace DatasetCreator
{

    struct FunctionFeature
    {
        int    index;
        int    power;
        double weight;
    };

    Dataset GenerateDataset(unsigned size, std::vector<FunctionFeature> & features, int numberInputs, double scale, double noise);

} // namespace DatasetCreator

#endif