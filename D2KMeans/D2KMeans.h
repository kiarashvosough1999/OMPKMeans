#ifndef KMEANS3WAY_H
#define KMEANS3WAY_H

#include "SetKMeans.h"


template <typename T> class D2KMeans: public SetKMeans<T> {

public:

    D2KMeans(int demandClusterNumber, int iterations, int threadCountToBeUsed);

    int fit(vector<Data<T>>& inputData) override;

};
#endif