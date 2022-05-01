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

#include "KMeansFactory.h"

template<typename T>
int KMeansFactory<T>::execute(string inputFilename, ParallelClasses parallelClass, int demandClusterCount,
                              int threadToBeUsedCount,
                              int iterationCount,
                              int paddingCount,
                              int testNumber,
                              mutex *txtLock,
                              vector<Data<T>> inputData,
                              mutex *csvLock) {

//    vector<Data<T>> vectorData = KMeansFactory<T>::load_input(inputFilename);

    // Return if number of clusters > number of datas
    if (inputData.size() < demandClusterCount) {
        throw "Number of clusters greater than number of datas";
        return 1;
    }

    KMeans<T> *kmeans;

    auto startTime = chrono::high_resolution_clock::now();

    switch (parallelClass) {
        case ForKMeansType:
            kmeans = new ForKMeans<T>(demandClusterCount, iterationCount, threadToBeUsedCount, txtLock, csvLock);
            break;
        case SMPDKMeansType:
            kmeans = new SPMDKMeans<T>(demandClusterCount, iterationCount, threadToBeUsedCount, txtLock, csvLock);
            break;
        case PadKmeansType:
            kmeans = new PadKMeans<T>(demandClusterCount, iterationCount, threadToBeUsedCount, paddingCount, txtLock, csvLock);
            break;
        case SerialKMeansType:
            kmeans = new SerialKMeans<T>(demandClusterCount, iterationCount, threadToBeUsedCount, txtLock, csvLock);
            break;
        case CriticalKMeansType:
            kmeans = new CriticalKMeans<T>(demandClusterCount, iterationCount, threadToBeUsedCount, txtLock, csvLock);
            break;
        case LAST:
            return -1;
    };

    int usedIteration = kmeans->fit(inputData);

    auto endTime = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = endTime - startTime;

    string s1 = ParallelClassNames[parallelClass];

    string s2 = "System Processes Count: " + to_string(omp_get_num_procs());

    string s3 = "System Thread Count: " + to_string(omp_get_max_threads());

    string s4 = "Thread used: " + to_string(threadToBeUsedCount);

    string s5 = "Demand Cluster: " + to_string(demandClusterCount);

    string s6 = "Total Iteration: " + to_string(iterationCount);

    string s7 = "Padding Count (If Needed)" + to_string(paddingCount);

    string st = s1 +
            "\n" +
            s2 +
            "\n" +
            s3 +
            "\n" +
            s4 +
            "\n" +
            s5 +
            "\n" +
            s6 +
            "\n" +
            s7 +
            "\n" +
            "Test: " +
            to_string(testNumber) +
            "\n\n" +
            "Elapsed time: " +
            to_string(elapsed.count()) +
            "second\n";

    kmeans->printResults(usedIteration, true, st);

    kmeans->saveCSV(s1, to_string(testNumber));
}

template<typename T>
vector<Data<T>> KMeansFactory<T>::load_input(const string &filename) {

    ifstream inputStream(filename.c_str());

    if (!inputStream.is_open())
        throw "Failed to open file";

    int dataId = 1;
    vector<Data<T>> dataVector;
    string line;

    while (getline(inputStream, line)) {
        Data<T> data(dataId, line);
        dataVector.push_back(data);
        dataId++;
    }
    inputStream.close();

    return dataVector;
}

template
class KMeansFactory<double>;