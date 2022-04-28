//
// Created by Kiarash Vosough on 4/14/22.
//

#ifndef INC_1_3OMP_SETKMEANS_H
#define INC_1_3OMP_SETKMEANS_H

#include "KMeans.h"

template <typename T> class SetKMeans: public KMeans<T> {

public:

    SetKMeans(int demandClusterNumber, int iterations, int threadCountToBeUsed);

protected:
    vector<Data<T>> findIntersection(Cluster<T> cluster[]);

    vector<Data<T>> findUnion(Cluster<T> clusters[], Cluster<T> init);
};


#endif //INC_1_3OMP_SETKMEANS_H
