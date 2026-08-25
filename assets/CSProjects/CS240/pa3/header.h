#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "datapoint.h"
#include "dataset.h"


using namespace std;

// Definition of Neighbor struct
struct Neighbor
{
    DataPoint dp;   // DataPoint representing a mushroom
    double distance; // Euclidean distance to the test sample
};

// Function declarations
double calculateEuclideanDistance(const DataPoint& dp1, const DataPoint& dp2);
void classifyMushrooms(DataSet* dataset, DataSet& testData, int k);
Neighbor* getKNearestNeighbors(DataSet* dataset, const DataPoint& testMushroom, int k);
bool loadTestData(DataSet& testData, int& k);
void sortNeighborsByDistance(Neighbor* neighbors, int k);


#endif
