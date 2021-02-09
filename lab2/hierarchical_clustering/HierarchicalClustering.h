//---------------------------------------------------------------------------
#ifndef HIERARCHICAL_CLUSTERING_H
#define HIERARCHICAL_CLUSTERING_H
//---------------------------------------------------------------------------

#include "DatasetCreator.h"

namespace CS397
{
double DistanceSquare(const std::vector<double> & datapoint1, const std::vector<double> & datapoint2);

class HierarchicalClustering
{
  public:
    HierarchicalClustering(const Dataset & data);

    void                             Iteration();
    std::vector<std::vector<size_t>> GetClusters(size_t numClusters);

  private:
    struct ClosestDist
    {
        size_t closestIndex;
        double distaceSq;
    };

    std::vector<std::vector<double>> mDataset;
    std::vector<double>              mDissimilarityMatrix;
    std::vector<ClosestDist>         mClosestDistance;

    std::vector<size_t> mClusterTree;
};
} // namespace CS397

#endif