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

#include "Data.h"


template<typename T> Data<T>::Data(int id, string dataLine) {
    this->dimensions = 0;
    this->Id = id;
    this->clusterId = 0;
    this->loadData(dataLine);
}

template<typename T> int Data<T>::getDimensions() const {
    return dimensions;
}

template<typename T> int Data<T>::getClusterId() const {
    return clusterId;
}

template<typename T> int Data<T>::getID() const {
    return Id;
}

template<typename T> void Data<T>::setClusterId(int id) {
    clusterId = id;
}

template<typename T> T Data<T>::getValueByIndex(int index) const {
    return values[index];
}

template<typename T> bool Data<T>::operator!=(Data<T> const &obj) const {
    bool flag = true;
    for (int i = 0; i < dimensions; i++) {
        if (this->values[i] != obj.values[i]) {
            flag = false;
            break;
        }
    }
    return !flag;
}

template<typename T> bool Data<T>::operator==(Data<T> const &obj) const {
    bool flag = true;
    for (int i = 0; i < dimensions; i++) {
        if (this->values[i] != obj.values[i]) {
            flag = false;
            break;
        }
    }
    return flag;
}

template<typename T> const vector<T> &Data<T>::getValues() const {
    return values;
}

template<typename T>
void Data<T>::loadData(string dataLine) {
    stringstream stream(dataLine);
    T val;

    while (stream >> val) {
        values.push_back(val);
        dimensions++;
    }
}

template class Data<double>;