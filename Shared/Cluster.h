#ifndef Cluster_H
#define Cluster_H

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "Data.h"

using namespace std;

template <typename T> class Cluster {

private:

    int clusterId;
    vector<T> centroid;
    vector<Data<T>> datas;

public:
    Cluster(int clusterId, Data<T> centroid);

    Cluster ();

    void addData(Data<T> data);

    bool removeData(int dataId);

    int getId() const;

    Data<T> getData(int position) const;

    int getSize() const;

    vector<T> getCentroid() const;

    T getCentroidByIndex(int index) const;

    void setCentroidByIndex(int index, T newValue);

    vector<Data<T>> getDatas() const;

    void removeAllData();
};

#endif