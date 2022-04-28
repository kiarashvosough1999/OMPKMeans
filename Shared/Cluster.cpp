
#include "Cluster.h"

template <typename T> Cluster<T>::Cluster(int clusterId, Data<T> centroid) {
    this->clusterId = clusterId;
    for (int i = 0; i < centroid.getDimensions(); i++) {
        this->centroid.push_back(centroid.getValueByIndex(i));
    }
    this->addData(centroid);
}

template <typename T> Cluster<T>::Cluster() {}

template <typename T> void Cluster<T>::addData(Data<T> data) {
    data.setClusterId(this->clusterId);
    this->datas.push_back(data);
}

template <typename T>bool Cluster<T>::removeData(int dataId) {
    int size = datas.size();

    for (int i = 0; i < size; i++) {
        if (this->datas[i].getID() == dataId) {
            this->datas.erase(datas.begin() + i);
            return true;
        }
    }
    return false;
}

template <typename T> int Cluster<T>::getId() const {
    return this->clusterId;
}

template <typename T> Data<T> Cluster<T>::getData(int position) const {
    return this->datas[position];
}

template <typename T> int Cluster<T>::getSize() const {
    return this->datas.size();
}

template <typename T> vector<T> Cluster<T>::getCentroid() const {
    return this->centroid;
}

template <typename T> T Cluster<T>::getCentroidByIndex(int index) const {
    return this->centroid[index];
}

template <typename T> void Cluster<T>::setCentroidByIndex(int index, T newValue) {
    this->centroid[index] = newValue;
}

template <typename T> vector<Data<T>> Cluster<T>::getDatas() const {
    return this->datas;
}

template <typename T> void Cluster<T>::removeAllData() {
    this->datas.clear();
}

template class Cluster<double>;