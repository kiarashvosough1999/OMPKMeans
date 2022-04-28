//
// Created by Kiarash Vosough on 4/14/22.
//

#include "SetKMeans.h"

template <typename T> SetKMeans<T>::SetKMeans(int demandClusterNumber, int iterations, int threadCountToBeUsed) :
KMeans<T>(demandClusterNumber, iterations, threadCountToBeUsed) {}

template <typename T> vector<Data<T>> SetKMeans<T>::findIntersection(Cluster<T> cluster[]) {
    vector<Data<T>> intersectDatas;
    intersectDatas = cluster[0].getDatas();

    for (int i = 1; i < this->threadCountToBeUsed; i++) {
        vector<Data<T>> temp = cluster[i].getDatas();
        for (int j = 0; j < intersectDatas.size(); j++) {
            int k = 0;
            for (k = 0; k < temp.size(); k++)
                if (temp[k] == intersectDatas[j])
                    break;

            if (k == temp.size())
                intersectDatas.erase(intersectDatas.begin() + j);
        }
    }
    return intersectDatas;
}

template <typename T> vector<Data<T>> SetKMeans<T>::findUnion(Cluster<T> clusters[], Cluster<T> init) {
    vector<Data<T>> unionPoints;
    vector<Data<T>> temp;
    vector<Data<T>> temp2 = init.getDatas();

    for (int i = 0; i < this->threadCountToBeUsed; i++) {
        temp = clusters[i].getDatas();
        for (int j = 0; j < temp.size(); j++) {
            bool f = 0;
            for (int k = 0; k < temp2.size(); k++)
                if (temp[j] == temp2[k])
                    f = 1;

            if (f == 0)
                unionPoints.push_back(temp[j]);
        }
        temp = vector<Data<T>>();
    }
    return unionPoints;
}

template class SetKMeans<double>;