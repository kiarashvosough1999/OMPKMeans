//
// Created by kiarashvosough on 4/21/22.
//

#ifndef INC_1_3OMP_CRITICALKMEANS_H
#define INC_1_3OMP_CRITICALKMEANS_H

#include "../Shared/KMeans.h"

template <typename T> class CriticalKMeans: public KMeans<T> {

public:

    CriticalKMeans(int demandClusterNumber, int iterations, int threadCountToBeUsed);

    int fit(vector<Data<T>>& inputData) override;
};


#endif //INC_1_3OMP_CRITICALKMEANS_H
