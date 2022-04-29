cmake_minimum_required(VERSION 3.21)
project(1_3omp)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_C_COMPILER /your/path/to/gcc-5)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

include_directories(SPMDMeans)
include_directories(Shared)

add_executable(1_3omp
        inputData5000.txt
        inputData50000.txt
        inputData500000.txt
        SPMDMeans/SPMDKMeans.cpp
        SPMDMeans/SPMDKMeans.h
        Shared/Cluster.cpp
        Shared/Cluster.h
        Shared/Data.cpp
        Shared/Data.h
        Shared/KMeans.h main.cpp
        Shared/KMeans.cpp
        ForKMeans/ForKMeans.cpp
        ForKMeans/ForKMeans.h
        D3PadKMeans/D3PadKMeans.cpp
        D3PadKMeans/D3PadKMeans.h
        Shared/SetKMeans.cpp
        Shared/SetKMeans.h
        Shared/ParallelClasses.h
        Shared/KMeansFactory.cpp
        Shared/KMeansFactory.h
        SerialKmeans/SerialKMeans.cpp
        SerialKmeans/SerialKMeans.h
        KMeansCritical/CriticalKMeans.cpp
        KMeansCritical/CriticalKMeans.h)
