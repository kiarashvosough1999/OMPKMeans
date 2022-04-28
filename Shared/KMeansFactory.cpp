//
// Created by kiarashvosough on 4/15/22.
//

#include "KMeansFactory.h"

template<typename T>
int KMeansFactory<T>::execute(string inputFilename,
                              ParallelClasses parallelClass,
                              int demandClusterCount,
                              int threadToBeUsedCount,
                              int iterationCount,
                              int paddingCount,
                              int testNumber) {

    vector<Data<T>> vectorData = KMeansFactory<T>::load_input(inputFilename);

    // Return if number of clusters > number of datas
    if (vectorData.size() < demandClusterCount) {
        throw "Number of clusters greater than number of datas";
        return 1;
    }

    KMeans<T> *kmeans;

    auto startTime = chrono::high_resolution_clock::now();

    switch (parallelClass) {
        case ForKMeansType:
            kmeans = new ForKMeans<T>(demandClusterCount, iterationCount, threadToBeUsedCount);
            break;
        case D2KMeansType:
            kmeans = new D2KMeans<T>(demandClusterCount, iterationCount, threadToBeUsedCount);
            break;
        case D3PadKmeansType:
            kmeans = new D3PadKMeans<T>(demandClusterCount, iterationCount, threadToBeUsedCount, paddingCount);
            break;
        case SerialKMeansType:
            kmeans = new SerialKMeans<T>(demandClusterCount, iterationCount, threadToBeUsedCount);
            break;
        case CriticalKMeansType:
            kmeans = new CriticalKMeans<T>(demandClusterCount, iterationCount, threadToBeUsedCount);
            break;
    };

    int usedIteration = kmeans->fit(vectorData);

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