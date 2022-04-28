//
// Created by Kiarash Vosough on 4/14/22.
//

#include "ForKMeans.h"

template <typename T> ForKMeans<T>::ForKMeans(int demandClusterNumber, int iterations, int threadCountToBeUsed) : KMeans<T>(demandClusterNumber, iterations, threadCountToBeUsed) {}

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