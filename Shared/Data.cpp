
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