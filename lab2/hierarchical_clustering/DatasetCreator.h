//---------------------------------------------------------------------------
#ifndef DATASET_CREATION_H
#define DATASET_CREATION_H
//---------------------------------------------------------------------------

#include <vector>

// Dataset contains just a vector of inputs that contains
// different values of each feature for each input
using Dataset = std::vector<std::vector<double>>;

namespace DatasetCreator
{

// Dataset type contiains a pair where first represents training dataset
// and the second stores the test dataset
class SplittedDataset
{
  public:
    Dataset trainingSet;
    Dataset testSet;
};

SplittedDataset GenerateBlobsDataset(unsigned sizeTraining, unsigned sizeTesting, unsigned numParams, unsigned numBlobs, double noise);

} // namespace DatasetCreator

#endif