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

#include "SPMDKMeans.h"

template<typename T>
SPMDKMeans<T>::SPMDKMeans(int demandClusterNumber, int iterations, int threadCountToBeUsed, mutex* txtMutex, mutex* csvMutex)
        : SetKMeans<T>(demandClusterNumber, iterations, threadCountToBeUsed, txtMutex, csvMutex) {}

template<typename T>
int SPMDKMeans<T>::fit(vector<Data<T>> &inputData) {

    // store the count of data
    this->totalDataNumber = inputData.size();

    // store dimension of data
    this->dimensions = this->detectDataDimensions(inputData);

    srand(time(NULL));

    this->initializeClusters(inputData);

    cout << "Fitting SPMD-KMeans Clustering.." << endl;

    int iterationUntilNow = 1;
    // [Rows count == Thread Num][Column count == demandClusterNumber]
    // for each thread we have demandClusterNumber cluster
    // Thread/Cluster  K1  K2  K3  K4  .....
    //       T1
    //       T2
    //       T3
    // it is purpose is to map threads to clusters and avoiding false sharing
    Cluster<T> clusterMap[this->threadCountToBeUsed][this->demandClusterNumber];
    // Assign one cluster to its own column
    // attention that all cluster in one column are one unique object
    for (int i = 0; i < this->demandClusterNumber; i++) {
        for (int j = 0; j < this->threadCountToBeUsed; j++) {
            clusterMap[j][i] = this->clusters[i];
        }
    }

    while (true) { // while 1PadMergerTemplateMethod

        // Assign one cluster to its own column
        // attention that all cluster in one column are one unique object
        for (int i = 0; i < this->demandClusterNumber; i++) { // for 1
            for (int j = 0; j < this->threadCountToBeUsed; j++) { // for 1-1
                clusterMap[j][i] = this->clusters[i];
            } // end for 1-1
        } // end for 1

        bool isAllDataInASuitableCluster = true;

        // Add all datas to their nearest cluster
        omp_set_num_threads(this->threadCountToBeUsed);

        #pragma omp parallel
        {
            int this_thread_id = omp_get_thread_num(); // get this thread id
            int threads_count = omp_get_num_threads(); // get threads count

            // iterate on thread count and process each data for specific thread based pn thread id
            // Example: if we have 2 threads
            // first thread will process odd indexes of datas
            // second thread will process even indexes of data
            for (int i = this_thread_id; i < this->totalDataNumber; i += threads_count) { // for 2
                int currentPointClusterId = inputData[i].getClusterId();
                int nearestClusterId = this->findClosestClusterId(inputData[i]);

                // check if the point cluster and the found nearest cluster are not the same
                if (currentPointClusterId != nearestClusterId) { // if 2-1
                    if (currentPointClusterId != 0)
                        // find the current cluster of point, so that we can delete point from it
                        for (int j = 0; j < this->demandClusterNumber; j++)
                            if (this->clusters[j].getId() == currentPointClusterId)
                                clusterMap[this_thread_id][j].removeData(inputData[i].getID());

                    // find the found cluster of point, so that we can add point to it
                    for (int j = 0; j < this->demandClusterNumber; j++)
                        if (this->clusters[j].getId() == nearestClusterId)
                            clusterMap[this_thread_id][j].addData(inputData[i]);

                    inputData[i].setClusterId(nearestClusterId);
                    isAllDataInASuitableCluster = false;
                } // end // if 2-1
            } // end for 2
        } // end omp parrallel

        // Merge the Results from Map
        // Thread/Cluster  K1  K2  K3  K4  .....
        //       T1
        //       T2
        //       T3
        for (int i = 0; i < this->demandClusterNumber; i++) {
            vector<Data<T>> intersectionDatas;
            vector<Data<T>> unionDatas;
            Cluster<T> temp[this->threadCountToBeUsed];

            for (int j = 0; j < this->threadCountToBeUsed; j++)
                temp[j] = clusterMap[j][i];

            unionDatas = this->findUnion(temp, this->clusters[i]);
            intersectionDatas = this->findIntersection(temp);

            this->clusters[i].removeAllData();

            for (auto & unionPoint : unionDatas)
                this->clusters[i].addData(unionPoint);

            for (auto & intersectionPoint : intersectionDatas)
                this->clusters[i].addData(intersectionPoint);
        }

        // revise the center of each cluster
        this->reviseCentroidsOfClusters();

        this->storeCentroidWithUsedIteration(iterationUntilNow);

        if (this->checkForCompletion(isAllDataInASuitableCluster, iterationUntilNow))
            break;

        iterationUntilNow++;
    } // end while
    return iterationUntilNow;
}

template class SPMDKMeans<double>;