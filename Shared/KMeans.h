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

#ifndef INC_1_3OMP_KMEANS_H
#define INC_1_3OMP_KMEANS_H

#include "Cluster.h"
#include <cmath>
#include "Data.h"
#include <omp.h>
#include <fstream>
#include <mutex>

using namespace std;

template <typename T>
class KMeans {

protected:

    mutex* txtMutex;

    mutex* csvMutex;

    int threadCountToBeUsed{};

    int demandClusterNumber{};

    int maxIterations{};

    int dimensions{};

    int totalDataNumber{};

    vector<Cluster<T>> clusters;

    vector<T> clusterCenters[100];

    int findClosestClusterId(Data<T> data);

    void initializeClusters(vector<Data<T>> &inputData);

    int detectDataDimensions(vector<Data<T>> &inputData) const;

    void storeCentroidWithUsedIteration(int usedIteration);

    void reviseCentroidsOfClusters();

    bool checkForCompletion(bool doneFlag, int iterationUntilNow);

    void saveStringToFileAndPrintOnConsole(ofstream& outputStream, string message);

public:

    KMeans(int demandClusterNumber, int iterations, int threadCountToBeUsed, mutex* txtMutex, mutex* csvMutex);

    const vector<double>* getClusterCenters() const;

    vector<Cluster<T>> getClusters() const;

    virtual int fit(vector<Data<T>>& inputData) = 0;

    virtual void printResults(int usedIteration, bool saveToFile, string beginOutput);

    virtual void saveCSV(string type, string test);
};

#endif //INC_1_3OMP_KMEANS_H