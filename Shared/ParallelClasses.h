//
// Created by kiarashvosough on 4/15/22.
//

#ifndef INC_1_3OMP_PARALLELCLASSES_H
#define INC_1_3OMP_PARALLELCLASSES_H

#include <string>

using namespace std;

enum ParallelClasses { ForKMeansType = 0, D2KMeansType, D3PadKmeansType, SerialKMeansType, CriticalKMeansType };

static string ParallelClassNames[] = {"ForKMeansType",
                               "D2KMeansType",
                               "D3PadKmeansType",
                               "SerialKMeansType",
                               "CriticalKMeansType" };

#endif //INC_1_3OMP_PARALLELCLASSES_H
