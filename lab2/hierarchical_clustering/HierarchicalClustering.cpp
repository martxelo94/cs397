
#include "HierarchicalClustering.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>
#include <string>

namespace CS397
{

double DistanceSquare(const std::vector<double> & datapoint1, const std::vector<double> & datapoint2)
{
    double distanceSq = 0.0;
    for (size_t i = 0; i < datapoint1.size(); i++)
    {
        double delta = datapoint2[i] - datapoint1[i];
        distanceSq += delta * delta;
    }

    return distanceSq;
}

HierarchicalClustering::HierarchicalClustering(const Dataset & data) :
    mDataset(data),
    mDissimilarityMatrix(data.size() * data.size()),
    mClosestDistance(data.size(), {0, std::numeric_limits<double>::max()})
{
    // fill the dissimilarity matrix and closest distances
    for (unsigned i = 0; i < mDataset.size(); i++)
    {
        double minDistanceSq = mClosestDistance[i].distaceSq;

        // distance to itself is always zero
        mDissimilarityMatrix[i * mDataset.size() + i] = 0.0;

        // compute distance to every other datapoint
        for (unsigned j = i + 1; j < mDataset.size(); j++)
        {
            // distance is symmetric so update the matrix symmetrically
            double distIJSq                               = DistanceSquare(mDataset[i], mDataset[j]);
            mDissimilarityMatrix[i * mDataset.size() + j] = distIJSq;
            mDissimilarityMatrix[j * mDataset.size() + i] = distIJSq;

            // update closesst distance data if found smaller data
            if (distIJSq < minDistanceSq)
            {
                mClosestDistance[i] = {j, distIJSq};
                minDistanceSq       = distIJSq;

                // update the pair if found a smaller distance
                if (distIJSq < mClosestDistance[j].distaceSq)
                {
                    mClosestDistance[j] = {i, distIJSq};
                }
            }
        }
    }
}

std::vector<double> RemoveRowColumn(const std::vector<double>& m, size_t idx) {
    std::vector<double> _m((m.size() - 1) * (m.size() - 1), 0.0);
    for (size_t i = 0; i < m.size(); ++i) {
        if (i == idx) continue;
        for (size_t j = 0; j < m.size(); ++j) {
            if (j == idx) continue;
            size_t k = i * (m.size() - 1) + j;
            _m.push_back(m[k]);
        }
    }
    return _m;
}

void HierarchicalClustering::Iteration()
{
    double minDistanceSq = mClosestDistance[0].distaceSq;
    size_t cluster1      = 0;
    size_t cluster2      = mClosestDistance[0].closestIndex;

    // STUDENT CODE

    // •Loop as long as there are more than 1 cluster
    if (mClosestDistance.empty())
        return;
    // Find the smallest distance between any 2 clusters
    // Clusters 𝐶𝑖 and 𝐶𝑗 at indices 𝑖 and 𝑗, 𝑖 < j
    for (size_t i = 0; i < mClosestDistance.size(); ++i) {
        if (minDistanceSq < mClosestDistance[i].distaceSq) {
            minDistanceSq = mClosestDistance[i].distaceSq;
            cluster1 = i;
            cluster2 = mClosestDistance[i].closestIndex;
        }
    }
    // Merged cluster will use location at index i

    // ▫For each other cluster 𝐶𝑘 at index 𝑘
    for (size_t k = 0; k < mClosestDistance.size(); ++k) {
        if (k == cluster1 || k == cluster2)
            continue;
        double dm_ik = mDissimilarityMatrix
    }

    // add merging link to the tree
    mClusterTree.push_back(cluster1);
    mClusterTree.push_back(cluster2);
}

std::vector<std::vector<size_t>> HierarchicalClustering::GetClusters(size_t numClusters)
{
    std::vector<std::vector<size_t>> clusters;

    // get links that will stay merged (last links are discarded here)
    std::vector<size_t> tree(mClusterTree.begin(), mClusterTree.end() - (numClusters - 1) * 2);

    // get the roots for each of those clusters
    std::set<size_t> roots(mClusterTree.end() - (numClusters - 1) * 2, mClusterTree.end());

    // traverse each root to get the datapoints that belong to the cluster
    for (const auto & root : roots)
    {
        std::vector<size_t> newCluster;

        // root is first element in cluster
        newCluster.push_back(root);

        // check the previous merges to find more elemnts
        for (int i = int(tree.size() - 2); i >= 0; i -= 2)
        {
            size_t index = i;
            if (std::find(newCluster.begin(), newCluster.end(), tree[index]) != newCluster.end())
            {
                newCluster.push_back(tree[index + 1]);
            }
        }
        // sort elements in cluster
        std::sort(newCluster.begin(), newCluster.end());
        clusters.push_back(newCluster);
    }

    return clusters;
}

} // namespace CS397