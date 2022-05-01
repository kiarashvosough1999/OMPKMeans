//
// Created by Kiarash Vosough on 4/14/22.
//

#include <string>
#include <mutex>
#include "KMeansFactory.h"

using namespace std;

mutex *txtMtx = new mutex();
mutex *csvMtx = new mutex();

int main(int argc, char **argv) {

    string filename = "../inputData50000.txt";
    int K = 10;
    int maxThreads =  omp_get_max_threads();
    int padding = 8;
    int iterations = 200;

    vector<Data<double>> vectorData = KMeansFactory<double>::load_input(filename);

    for (int i = ForKMeansType; i != LAST ; i++) {
        ParallelClasses parallelClass = static_cast<ParallelClasses>(i);
        for (int j = 1 ; j <= maxThreads; j++) {
            KMeansFactory<double>::execute(filename,
                                           parallelClass,
                                           K,
                                           j,
                                           iterations,
                                           padding,
                                           j,
                                           txtMtx,
                                           vectorData,
                                           csvMtx);
        }
    }

    return 0;
}