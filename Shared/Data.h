#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

template <typename T>
class Data {

private:

    int Id;

    int clusterId;

    int dimensions;

    vector<T> values;

    void loadData(string dataLine);

public:

    const vector<T>& getValues() const;

    Data(int id, string dataLine);

    int getDimensions() const;

    int getClusterId() const;

    int getID() const;

    void setClusterId(int id);

    T getValueByIndex(int index) const;

    bool operator != (Data const &obj) const;

    bool operator == (Data const &obj) const;
};

#endif