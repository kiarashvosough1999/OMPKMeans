//
// Created by kiarashvosough on 4/15/22.
//

#ifndef INC_1_3OMP_PARALLELCLASSES_H
#define INC_1_3OMP_PARALLELCLASSES_H

#include <string>

using namespace std;

enum ParallelClasses { ForKMeansType = 0, SMPDKMeansType, PadKmeansType, SerialKMeansType, CriticalKMeansType, LAST };

static string ParallelClassNames[] = {"ForKMeansType",
                               "SMPDKMeansType",
                               "PadKmeansType",
                               "SerialKMeansType",
                               "CriticalKMeansType" };

#endif //INC_1_3OMP_PARALLELCLASSES_H
