
#include <algorithm>
#include <ctime>
#include <iostream>
#include <string>

#include "HierarchicalClustering.h"

void Test1()
{
    std::cout << "################################################" << std::endl;
    std::cout << "                     TEST 1" << std::endl;
    std::cout << "################################################" << std::endl;
    srand(0);
    Dataset data = DatasetCreator::GenerateBlobsDataset(5, 0, 1, 2, 0.5).trainingSet;

    // Give data to the clustering algorithm
    CS397::HierarchicalClustering hierarchy(data);

    // create cluster for the provided data, 
    // number of merges is datapoint count minus 1
    for (int i = 0; i < int(data.size() - 1); i++)
    {
        hierarchy.Iteration();
    }
    // get clusters with the indices of the datapoints
    std::vector<std::vector<size_t>> clusters = hierarchy.GetClusters(2);

    // output clusters
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << clusters.size() << " CLUSTERS" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    for (size_t i = 0; i < clusters.size(); i++)
    {
        std::cout << "Cluster " << i << ": ";
        for (int j = 0; j < int(clusters[i].size() - 1); j++)
        {
            std::cout << clusters[i][j] << ", ";
        }
        std::cout << clusters[i][clusters[i].size() - 1] << std::endl;
    }

    // get clusters with the indices of the datapoints
    std::vector<std::vector<size_t>> clusters2 = hierarchy.GetClusters(4);

    // output clusters
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << clusters2.size() << " CLUSTERS" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    for (unsigned i = 0; i < clusters2.size(); i++)
    {
        std::cout << "Cluster " << i << ": ";
        for (int j = 0; j < int(clusters2[i].size() - 1); j++)
        {
            std::cout << clusters2[i][j] << ", ";
        }
        std::cout << clusters2[i][clusters2[i].size() - 1] << std::endl;
    }
    std::cout << std::endl;
}

void Test2()
{
    std::cout << "################################################" << std::endl;
    std::cout << "                     TEST 2" << std::endl;
    std::cout << "################################################" << std::endl;
    srand(0);
    Dataset data = DatasetCreator::GenerateBlobsDataset(15, 0, 3, 3, 0.5).trainingSet;

    // Give data to the clustering algorithm
    CS397::HierarchicalClustering hierarchy(data);

    // create cluster for the provided data,
    // number of merges is datapoint count minus 1
    for (int i = 0; i < int(data.size() - 1); i++)
    {
        hierarchy.Iteration();
    }

    // get clusters with the indices of the datapoints
    std::vector<std::vector<size_t>> clusters = hierarchy.GetClusters(3);

    // output clusters
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << clusters.size() << " CLUSTERS" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    for (size_t i = 0; i < clusters.size(); i++)
    {
        std::cout << "Cluster " << i << ": ";
        for (int j = 0; j < int(clusters[i].size() - 1); j++)
        {
            std::cout << clusters[i][j] << ", ";
        }
        std::cout << clusters[i][clusters[i].size() - 1] << std::endl;
    }

    // get clusters with the indices of the datapoints
    std::vector<std::vector<size_t>> clusters2 = hierarchy.GetClusters(7);

    // output clusters
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << clusters2.size() << " CLUSTERS" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    for (size_t i = 0; i < clusters2.size(); i++)
    {
        std::cout << "Cluster " << i << ": ";
        for (int j = 0; j < int(clusters2[i].size() - 1); j++)
        {
            std::cout << clusters2[i][j] << ", ";
        }
        std::cout << clusters2[i][clusters2[i].size() - 1] << std::endl;
    }
    std::cout << std::endl;
}

void Test3()
{
    std::cout << "################################################" << std::endl;
    std::cout << "                     TEST 3" << std::endl;
    std::cout << "################################################" << std::endl;
    srand(0);
    Dataset data = DatasetCreator::GenerateBlobsDataset(10, 0, 3, 1, 0.5).trainingSet;

    // Give data to the clustering algorithm
    CS397::HierarchicalClustering hierarchy(data);

    // create cluster for the provided data,
    // number of merges is datapoint count minus 1
    for (int i = 0; i < int(data.size() - 1); i++)
    {
        hierarchy.Iteration();
    }

    // get clusters with the indices of the datapoints
    std::vector<std::vector<size_t>> clusters = hierarchy.GetClusters(3);

    // output clusters
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << clusters.size() << " CLUSTERS" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    for (unsigned i = 0; i < clusters.size(); i++)
    {
        std::cout << "Cluster " << i << ": ";
        for (int j = 0; j < int(clusters[i].size() - 1); j++)
        {
            std::cout << clusters[i][j] << ", ";
        }
        std::cout << clusters[i][clusters[i].size() - 1] << std::endl;
    }

    // get clusters with the indices of the datapoints
    std::vector<std::vector<size_t>> clusters2 = hierarchy.GetClusters(10);

    // output clusters
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << clusters2.size() << " CLUSTERS" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    for (size_t i = 0; i < clusters2.size(); i++)
    {
        std::cout << "Cluster " << i << ": ";
        for (int j = 0; j < int(clusters2[i].size() - 1); j++)
        {
            std::cout << clusters2[i][j] << ", ";
        }
        std::cout << clusters2[i][clusters2[i].size() - 1] << std::endl;
    }
    std::cout << std::endl;
}

int main(int argc, char * argv[])
{
    int test = -1;

    if (argc == 2)
        test = std::atoi(argv[1]);

    switch (test)
    {
        case 1:
            Test1();
            break;
        case 2:
            Test2();
            break;
        case 3:
            Test3();
            break;
        default:
            Test1();
            Test2();
            Test3();
            break;
    }

    return 0;
}