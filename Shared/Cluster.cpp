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