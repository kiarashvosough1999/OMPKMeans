//
// Created by Kiarash Vosough on 4/14/22.
//

#include <string>
#include "KMeansFactory.h"

using namespace std;

int main(int argc, char **argv) {

    string filename = "../inputData5000.txt";
    int K = 10;
    int maxThreads =  omp_get_max_threads();
    int padding = 8;
    int iterations = 200;

    for (int i = ForKMeansType; i != CriticalKMeansType ; i++) {
        ParallelClasses parallelClass = static_cast<ParallelClasses>(i);
        for (int j = 1 ; j <= maxThreads; j++) {
            KMeansFactory<double>::execute(filename,
                                           parallelClass,
                                           K,
                                           j,
                                           iterations,
                                           padding,
                                           j);
        }
    }

    return 0;
}