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

#include "ForKMeans.h"

template <typename T> ForKMeans<T>::ForKMeans(int demandClusterNumber, int iterations, int threadCountToBeUsed, mutex* txtMutex, mutex* csvMutex)
: KMeans<T>(demandClusterNumber, iterations, threadCountToBeUsed, txtMutex, csvMutex) {}

template <typename T> int ForKMeans<T>::fit(vector<Data<T>> &inputData) {

    // store the count of data
    this->totalDataNumber = inputData.size();

    // store dimension of data
    this->dimensions = this->detectDataDimensions(inputData);

    //Initializing Clusters

    this->initializeClusters(inputData);

    cout << "Fitting For-KMeans-Clustering.." << endl;

    int iterationUntilNow = 1;

    while (true) {
        bool isAllDataInASuitableCluster = true;
        omp_set_dynamic(1);
        omp_set_num_threads(this->threadCountToBeUsed);
        #pragma omp parallel
        {
            int currentClusterId;
            int nearestClusterId;

            // Add all datas to their nearest cluster
            #pragma omp barrier // every thread will wait when reach here for other threads to be completed
            #pragma omp for nowait
            for (int i = 0; i < this->totalDataNumber; i++) {
                currentClusterId = inputData[i].getClusterId();
                nearestClusterId = this->findClosestClusterId(inputData[i]);

                if (currentClusterId != nearestClusterId) {
                    if (currentClusterId != 0) {
                        #pragma omp parallel for
                        for (int j = 0; j < this->demandClusterNumber; j++) {
                            if (this->clusters[j].getId() == currentClusterId)
                                this->clusters[j].removeData(inputData[i].getID());
                        }
                    }
                    #pragma omp parallel for
                    for (int j = 0; j < this->demandClusterNumber; j++) {
                        if (this->clusters[j].getId() == nearestClusterId)
                            this->clusters[j].addData(inputData[i]);
                    }
                    inputData[i].setClusterId(nearestClusterId);
                    isAllDataInASuitableCluster = false;
                }
            }
        }

        // revise the center of each cluster
        this->reviseCentroidsOfClusters();

        this->storeCentroidWithUsedIteration(iterationUntilNow);

        if (this->checkForCompletion(isAllDataInASuitableCluster, iterationUntilNow))
            break;
        iterationUntilNow++;
    }
    return iterationUntilNow;
}

template class ForKMeans<double>;