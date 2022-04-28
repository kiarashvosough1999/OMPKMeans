//
// Created by Kiarash Vosough on 4/14/22.
//

#ifndef INC_1_3OMP_FORKMEANS_H
#define INC_1_3OMP_FORKMEANS_H


#include "KMeans.h"

template <typename T> class ForKMeans: public KMeans<T> {

public:

    ForKMeans(int demandClusterNumber, int iterations, int threadCountToBeUsed);

    int fit(vector<Data<T>> &inputData) override;

};


#endif //INC_1_3OMP_FORKMEANS_H
