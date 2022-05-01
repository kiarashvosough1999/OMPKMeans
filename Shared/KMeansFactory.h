//  Copyright 2020 KiarashVosough and other contributors
//
//  Permission is hereby granted, free of charge, to any person obtaining
//  a copy of this software and associated documentation files (the
//  Software"), to deal in the Software without restriction, including
//  without limitation the rights to use, copy, modify, merge, publish,
//  distribute, sublicense, and/or sell copies of the Software, and to
//  permit persons to whom the Software is furnished to do so, subject to
//  the following conditions:
//
//  The above copyright notice and this permission notice shall be
//  included in all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
//  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
//  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
//  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef INC_1_3OMP_KMEANSFACTORY_H
#define INC_1_3OMP_KMEANSFACTORY_H

#include <string>
#include "ParallelClasses.h"
#include "Data.h"
#include "KMeans.h"
#include <fstream>
#include <chrono>
#include <mutex>
#include "../ForKMeans/ForKMeans.h"
#include "SPMDKMeans.h"
#include "../PadKMeans/PadKMeans.h"
#include "../SerialKmeans/SerialKMeans.h"
#include "../KMeansCritical/CriticalKMeans.h"
#include <mutex>

using namespace std;

template<typename T>
class KMeansFactory {


public:

    static int
    execute(string inputFilename, ParallelClasses parallelClass, int demandClusterCount, int threadToBeUsedCount,
            int iterationCount, int paddingCount, int testNumber, mutex *txtLock, vector<Data<T>> inputData,
            mutex *csvLock);

    static vector<Data<T>> load_input(const string &filename);


};


#endif //INC_1_3OMP_KMEANSFACTORY_H
