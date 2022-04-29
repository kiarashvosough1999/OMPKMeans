//
// Created by Kiarash Vosough on 4/14/22.
//

#ifndef INC_1_3OMP_PADKMEANS_H
#define INC_1_3OMP_PADKMEANS_H

#include "SetKMeans.h"

template <typename T> class PadKMeans: public SetKMeans<T> {

private:

    int paddingCountToBeUsed;

public:

    PadKMeans(int demandClusterNumber, int iterations, int threadCountToBeUsed, int paddingCountToBeUsed);

    int fit(vector<Data<T>> &inputData) override;

};


#endif //INC_1_3OMP_PADKMEANS_H
