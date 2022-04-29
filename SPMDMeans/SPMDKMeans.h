#ifndef KMEANS3WAY_H
#define KMEANS3WAY_H

#include "SetKMeans.h"


template <typename T> class SPMDKMeans: public SetKMeans<T> {

public:

    SPMDKMeans(int demandClusterNumber, int iterations, int threadCountToBeUsed);

    int fit(vector<Data<T>>& inputData) override;

};
#endif