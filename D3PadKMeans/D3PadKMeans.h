//
// Created by Kiarash Vosough on 4/14/22.
//

#ifndef INC_1_3OMP_D3PADKMEANS_H
#define INC_1_3OMP_D3PADKMEANS_H

#include "SetKMeans.h"

template <typename T> class D3PadKMeans: public SetKMeans<T> {

private:

    int paddingCountToBeUsed;

public:

    D3PadKMeans(int demandClusterNumber, int iterations, int threadCountToBeUsed, int paddingCountToBeUsed);

    int fit(vector<Data<T>> &inputData) override;

};


#endif //INC_1_3OMP_D3PADKMEANS_H
