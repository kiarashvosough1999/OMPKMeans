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

#include "KMeans.h"
#include <algorithm>

template<typename T>
KMeans<T>::KMeans(int demandClusterNumber, int iterations, int threadCountToBeUsed, mutex* txtMutex, mutex* csvMutex) {
    this->demandClusterNumber = demandClusterNumber;
    this->maxIterations = iterations;
    this->threadCountToBeUsed = threadCountToBeUsed;
    this->txtMutex = txtMutex;
    this->csvMutex = csvMutex;
}

template<typename T>
vector<Cluster<T>> KMeans<T>::getClusters() const {
    return this->clusters;
}

template<typename T>
int KMeans<T>::findClosestClusterId(Data<T> data) {
    double sumOfDistances = 0.0, minimumDistance;

    for (int i = 0; i < this->dimensions; i++) {
        double difference = this->clusters[0].getCentroidByIndex(i) - data.getValueByIndex(i);
        sumOfDistances += pow(difference, 2.0);
    }

    minimumDistance = sqrt(sumOfDistances);
    int NearestClusterId = this->clusters[0].getId();

    for (int i = 1; i < this->demandClusterNumber; i++) {
        double tempDistance;
        sumOfDistances = 0.0;

        for (int j = 0; j < this->dimensions; j++)
            sumOfDistances += pow(this->clusters[i].getCentroidByIndex(j) - data.getValueByIndex(j), 2.0);

        tempDistance = sqrt(sumOfDistances);

        if (tempDistance < minimumDistance) {
            minimumDistance = tempDistance;
            NearestClusterId = this->clusters[i].getId();
        }
    }
    return NearestClusterId;
}

template<typename T>
const vector<double> *KMeans<T>::getClusterCenters() const {
    return this->clusterCenters;
}

template<typename T>
void KMeans<T>::initializeClusters(vector<Data<T>> &inputData) {
    // Initializing Clusters
    // Randomly creat Clusters with datas
    // repeated until we initialized demandClusterNumber clusters
    vector<int> assignedDataIds;
    for (int i = 1; i <= this->demandClusterNumber; i++) {
        while (true) {
            int index = rand() % this->totalDataNumber;
            // Note that clusters are choosen from data
            // If this data has not been choosen so far...

            // find method: Returns an iterator to the first element in the range [first,last) that compares equal to index
            // If no such element is found, the function returns last as iterator.
            if (find(assignedDataIds.begin(), assignedDataIds.end(), index) == assignedDataIds.end()) {
                assignedDataIds.push_back(index);
                inputData[index].setClusterId(i);  // set choosen point cluster id
                Cluster<T> cluster(i, inputData[index]); // create cluster
                this->clusters.push_back(cluster);
                break;
            }
        }
    }
}

template<typename T>
int KMeans<T>::detectDataDimensions(vector<Data<T>> &inputData) const {
    int initialDimensions = inputData[0].getDimensions();

    for (const Data<T> &data: inputData)
        if (data.getDimensions() != initialDimensions)
            throw "Inconsistency in datas dimensions";
    return initialDimensions;
}

template<typename T>
void KMeans<T>::saveStringToFileAndPrintOnConsole(ofstream &outputStream, string message) {
    if (outputStream.is_open())
        outputStream << message;
    cout << message;
}

template<typename T>
void KMeans<T>::printResults(int usedIteration, bool saveToFile, string beginOutput) {

    this->txtMutex->lock();

    ofstream outputStream;
    if (saveToFile) {
        outputStream.open("../outputResults.txt", ios::app);
        if (!outputStream.is_open())
            throw "Can not open file to print output";
    }

    this->saveStringToFileAndPrintOnConsole(outputStream,  "======================================================================================================\n\n");

    this->saveStringToFileAndPrintOnConsole(outputStream, beginOutput);

    this->saveStringToFileAndPrintOnConsole(outputStream, "\nCluster's Center During Fitting Iteration\n");

    const vector<T> *clusterCenters = this->getClusterCenters();
    const int dataDimension = this->clusters[0].getData(0).getDimensions();

    for (int i = 0; i < usedIteration; i++) {

        this->saveStringToFileAndPrintOnConsole(outputStream, "Iteration " + to_string(i) + " : ");

        for (int j = 0; j < clusterCenters[i].size(); j++) {
            if (j % dataDimension == 0 && j != 0)
                this->saveStringToFileAndPrintOnConsole(outputStream, "  ****AND****  ");

            this->saveStringToFileAndPrintOnConsole(outputStream, to_string(clusterCenters[i][j]) + " " +
                                                                  to_string(clusterCenters[i][++j]));
        }
        this->saveStringToFileAndPrintOnConsole(outputStream, "\n");
    }

    this->saveStringToFileAndPrintOnConsole(outputStream, "\n");

    this->saveStringToFileAndPrintOnConsole(outputStream, "Final Centroids:\n\n");

    for (const Cluster<T> &cluster: this->clusters) {

        this->saveStringToFileAndPrintOnConsole(outputStream, "Cluster " + to_string(cluster.getId()) + " : ");

        for (int i = 0; i < cluster.getData(0).getDimensions(); ++i)
            this->saveStringToFileAndPrintOnConsole(outputStream, to_string(cluster.getCentroidByIndex(i)) + " ");

        this->saveStringToFileAndPrintOnConsole(outputStream, "\ndatas: { ");

        for (Data<T> dataModel: cluster.getDatas()) {
            this->saveStringToFileAndPrintOnConsole(outputStream, "(");
            for (T data: dataModel.getValues())
                this->saveStringToFileAndPrintOnConsole(outputStream, to_string(data) + ", ");

            this->saveStringToFileAndPrintOnConsole(outputStream, ")  ****AND****  ");
        }
        this->saveStringToFileAndPrintOnConsole(outputStream, "\n } \n");
    }
    this->saveStringToFileAndPrintOnConsole(outputStream, "\n");

    if(outputStream.is_open()) {
        outputStream.close();
    }

    this->txtMutex->unlock();
}

template<typename T>
void KMeans<T>::storeCentroidWithUsedIteration(int usedIteration) {

    for (int i = 0; i < this->demandClusterNumber; i++) {
        vector<double> centroid = this->clusters[i].getCentroid();
        for (int j = 0; j < centroid.size(); j++) {
            this->clusterCenters[usedIteration].push_back(centroid[j]);
        }
    }
}

template<typename T>
void KMeans<T>::reviseCentroidsOfClusters() {

    // using collapse here does not work
    int i,j,p;
    for (i = 0; i < this->demandClusterNumber; i++) {
        int ClusterSize = this->clusters[i].getSize();
        for (j = 0; j < this->dimensions; j++) {
            double sum = 0.0;
            if (ClusterSize > 0) {
                // using reduction here increase computation time in overall
                for (p = 0; p < ClusterSize; p++)
                    sum += this->clusters[i].getData(p).getValueByIndex(j);
                this->clusters[i].setCentroidByIndex(j, sum / ClusterSize);
            }
        }
    }
}

template<typename T>
bool KMeans<T>::checkForCompletion(bool doneFlag, int iterationUntilNow) {
    if (doneFlag || iterationUntilNow >= this->maxIterations) {
        return true;
    }
    return false;
}

template<typename T>
void KMeans<T>::saveCSV(string type, string test) {

    this->csvMutex->lock();
    ofstream myfile;
    myfile.open("../" + type + "_" + test + ".csv");

    char start = 'a';
    int i = 0;
    for (i = 0; i < this->dimensions ; ++i) {
        string temp = "";
        temp.push_back(static_cast<char>(start + i));
        myfile << temp << ",";
    }
    myfile << static_cast<char>(start + i) << endl;

    for (const Cluster<T> &cluster: this->clusters) {
        for (Data<T> dataModel: cluster.getDatas()) {
            for (T data: dataModel.getValues()) {
                myfile << to_string(data) << ",";
            }
            myfile << to_string(cluster.getId()) << endl;
        }
    }

    myfile.close();
    this->csvMutex->unlock();
}

template
class KMeans<double>;