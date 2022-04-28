//
// Created by kiarashvosough on 4/20/22.
//

#include "SerialKMeans.h"

template <typename T> SerialKMeans<T>::SerialKMeans(int demandClusterNumber, int iterations, int threadCountToBeUsed) : KMeans<T>(demandClusterNumber, iterations, threadCountToBeUsed) {}

template<typename T>
int SerialKMeans<T>::fit(vector<Data<T>> &inputData) {
    // store the count of data
    this->totalDataNumber = inputData.size();

    // store dimension of data
    this->dimensions = this->detectDataDimensions(inputData);

    srand(time(NULL));

    this->initializeClusters(inputData);

    cout << "Fitting Serial-KMeans Clustering.." << endl;

    int iterationUntilNow = 1;

    while (true) { // while 1

        bool isAllDataInASuitableCluster = true;

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
                            // directly delete point from cluster
                            this->clusters[j].removeData(inputData[i].getID());

                // find the current cluster of point, so that we can add point to it
                for (int j = 0; j < this->demandClusterNumber; j++)
                    if (this->clusters[j].getId() == nearestClusterId)
                        this->clusters[j].addData(inputData[i]);

                inputData[i].setClusterId(nearestClusterId);
                isAllDataInASuitableCluster = false;
            } // end // if 2-1
        } // end for 2

        // revise the center of each cluster
        this->reviseCentroidsOfClusters();

        this->storeCentroidWithUsedIteration(iterationUntilNow);

        if (this->checkForCompletion(isAllDataInASuitableCluster, iterationUntilNow))
            break;

        iterationUntilNow++;
    } // end while
    return iterationUntilNow;
}

template class SerialKMeans<double>;