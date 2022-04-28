//
// Created by Kiarash Vosough on 4/14/22.
//

#include "D3PadKMeans.h"

template <typename T> D3PadKMeans<T>::D3PadKMeans(int demandClusterNumber, int iterations, int threadCountToBeUsed, int paddingCountToBeUsed) : SetKMeans<T>(demandClusterNumber, iterations, threadCountToBeUsed) {
    this->paddingCountToBeUsed = paddingCountToBeUsed;
}

template <typename T> int D3PadKMeans<T>::fit(vector<Data<T>> &inputData) {

    // store the count of data
    this->totalDataNumber = inputData.size();

    // store dimension of data
    this->dimensions = this->detectDataDimensions(inputData);

    // Initializing Clusters
    this->initializeClusters(inputData);

    cout << "Fitting D3Pad-KMeans Clustering..." << endl;

    int iterationUntilNow = 1;
    // it is purpose is to map threads to clusters and avoiding false sharing
    Cluster<T> clusterPaddingMap[this->threadCountToBeUsed][this->paddingCountToBeUsed][this->demandClusterNumber];

    for (int i = 0; i < this->demandClusterNumber; i++)
        for (int j = 0; j < this->threadCountToBeUsed; j++)
            clusterPaddingMap[j][0][i] = this->clusters[i];

    while (true) {

        for (int i = 0; i < this->demandClusterNumber; i++)
            for (int j = 0; j < this->threadCountToBeUsed; j++)
                clusterPaddingMap[j][0][i] = this->clusters[i];

        bool isAllDataInASuitableCluster = true;
        omp_set_num_threads(this->threadCountToBeUsed);

        #pragma omp parallel
        {
            int this_thread_id = omp_get_thread_num();
            int total_threads_count = omp_get_num_threads();

            for (int i = this_thread_id; i < this->totalDataNumber; i += total_threads_count) {

                int currentClusterId = inputData[i].getClusterId();
                int nearestClusterId = this->findClosestClusterId(inputData[i]);

                if (currentClusterId != nearestClusterId) {
                    if (currentClusterId != 0) {
                        for (int j = 0; j < this->demandClusterNumber; j++)
                            if (this->clusters[j].getId() == currentClusterId)
                                clusterPaddingMap[this_thread_id][0][j].removeData(inputData[i].getID());
                    }

                    for (int j = 0; j < this->demandClusterNumber; j++)
                        if (this->clusters[j].getId() == nearestClusterId)
                            clusterPaddingMap[this_thread_id][0][j].addData(inputData[i]);

                    inputData[i].setClusterId(nearestClusterId);
                    isAllDataInASuitableCluster = false;
                }
            }
        }

        // Merge the Results
        for (int i = 0; i < this->demandClusterNumber; i++) {
            vector<Data<T>> intersectionDatas;
            vector<Data<T>> unionDatas;
            Cluster<T> temp[this->threadCountToBeUsed];

            for (int j = 0; j < this->threadCountToBeUsed; j++)
                temp[j] = clusterPaddingMap[j][0][i];

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
    }
    return iterationUntilNow;
}

template class D3PadKMeans<double>;