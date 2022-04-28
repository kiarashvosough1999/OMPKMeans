//
// Created by Kiarash Vosough on 4/14/22.
//

#ifndef INC_1_3OMP_KMEANS_H
#define INC_1_3OMP_KMEANS_H

#include "Cluster.h"
#include <cmath>
#include "Data.h"
#include <omp.h>
#include <fstream>

template <typename T>
class KMeans {

protected:

    int threadCountToBeUsed;

    int demandClusterNumber;

    int maxIterations;

    int dimensions;

    int totalDataNumber;

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

    KMeans(int demandClusterNumber, int iterations, int threadCountToBeUsed);

    const vector<double>* getClusterCenters() const;

    vector<Cluster<T>> getClusters() const;

    virtual int fit(vector<Data<T>>& inputData) = 0;

    virtual void printResults(int usedIteration, bool saveToFile, string beginOutput);

    virtual  void saveCSV(string type, string test);
};

#endif //INC_1_3OMP_KMEANS_H