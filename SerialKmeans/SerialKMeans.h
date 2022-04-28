//
// Created by kiarashvosough on 4/20/22.
//

#ifndef INC_1_3OMP_SERIALKMEANS_H
#define INC_1_3OMP_SERIALKMEANS_H


#include "KMeans.h"

template <typename T> class SerialKMeans: public KMeans<T> {

public:

    SerialKMeans(int demandClusterNumber, int iterations, int threadCountToBeUsed);

    int fit(vector<Data<T>>& inputData) override;
};


#endif //INC_1_3OMP_SERIALKMEANS_H
