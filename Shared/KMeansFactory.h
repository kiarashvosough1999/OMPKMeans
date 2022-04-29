//
// Created by kiarashvosough on 4/15/22.
//

#ifndef INC_1_3OMP_KMEANSFACTORY_H
#define INC_1_3OMP_KMEANSFACTORY_H

#include <string>
#include "ParallelClasses.h"
#include "Data.h"
#include "KMeans.h"
#include <fstream>
#include <chrono>
#include "../ForKMeans/ForKMeans.h"
#include "SPMDKMeans.h"
#include "../D3PadKMeans/D3PadKMeans.h"
#include "../SerialKmeans/SerialKMeans.h"
#include "../KMeansCritical/CriticalKMeans.h"


using namespace std;

template<typename T>
class KMeansFactory {


public:

    static int
    execute(string inputFilename, ParallelClasses parallelClass, int demandClusterCount, int threadToBeUsedCount,
            int iterationCount, int paddingCount, int testNumber);

    static vector<Data<T>> load_input(const string& filename);


};


#endif //INC_1_3OMP_KMEANSFACTORY_H
