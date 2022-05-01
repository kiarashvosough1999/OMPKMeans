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

#include "SetKMeans.h"

template <typename T> SetKMeans<T>::SetKMeans(int demandClusterNumber, int iterations, int threadCountToBeUsed, mutex* txtMutex, mutex* csvMutex) :
        KMeans<T>(demandClusterNumber, iterations, threadCountToBeUsed, txtMutex, csvMutex) {}

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