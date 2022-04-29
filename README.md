# OMPKMeans

![Swift](https://img.shields.io/badge/C++-14-orange?style=flat-square)
![Platforms](https://img.shields.io/badge/Platforms-Linux-yellowgreen?style=flat-square)

We have implemented KMeans with the omp library to parallelize and decrease clustering time consumption. 


- [Requirements](#requirements)
- [Features](#features)
- [Implementation](#implementation)
- [Installation](#installation)
- [Output](#output)
- [Contribution](#contribution)


## Requirements

| Platform | Minimum g++ Version | Minimum CMake Version | Status |
| --- | --- | --- | --- |
| Linux | 5.0 | 3.21 | Tested |

## Features

- [x] Used 5 Approaches To Use OMP.
- [x] Structured Implementation
- [x] Support Multi Deminsion DataSets.
- [x] Support Generic DataSets.

## Implementation

We Used 4 Approaches to use omp constructs 1 Serial and a simple one. Each of them is a class that implements an algorithm and specific constructs: 

- SerialKMeans
- CriticalKMeans
- SPMDKMeans
- ForKmeans
- D3PadKmeans

## Serial KMeans

SerialKMeans is the simple serial implementation of KMeans and uses no parallelism.

## Critical KMeans

In this approach, We used `omp parallel` construction, and to avoid data-race, 'omp critical' was used to modify clusters.

## SPMD KMeans

In computing, SPMD (single program, multiple data) is a technique employed to achieve parallelism; it is a subcategory of MIMD. Tasks are split up and run simultaneously on multiple processors with different inputs to obtain results faster. SPMD is the most common style of parallel programming.

So to achieve this approach, We used a 2D Array to store Clusters for each thread and modify each of them on its running thread; this way, we split up our tasks and avoided data races, but in the end, we should merge the results of each thread's cluster.

## ForKmeans

We used `omp for` construct for several for loops inside the algorithm within this approach.

## D3PadKmeans

As you may know, there is much going on in the back scene of omp and hardware to provide us parallelism.
One of them is **False-Sharing**, which puts lots of pressure on the parallelism process.

To avoid **False-Sharing**, we use Padding in our parallel constructions.

## Installation

To see if GCC is already installed on your system, open a Terminal window and enter the following command:

``` bash
GCC -v
```

If GCC is not installed, run the following command from the Terminal window to update the Ubuntu package lists. An out-of-date Linux distribution can interfere with getting the latest packages.

``` bash
sudo apt-get update
```

Next, install the GNU compiler, make, and the GDB debugger with this command:

``` bash
sudo apt-get install build-essential gdb
```


### CMake

Use the following command to use GUI CMake for building project:

``` bash
make-GUI
```

Alternatively, use the command line:

For example, from the command line, we could navigate to the main root of the project's directory of the CMake source code tree and create a build directory:

``` bash
mkdir Step1_build
```

Next, navigate to the build directory and run CMake to configure the project and generate a native build system:

``` bash
cd Step1_build
cmake ../Step1
```

Then call that build system to compile/link the project:

``` bash
CMake --build .
```

Finally, try to use the newly built `1_3omp` with these commands:

``` bash
1_3omp
```

## Output

After running the project and whenever it is finished, there will be a `outputResult.txt` file that logs every approach and the final centroid of clusters and more info.

The result of execution on 4-core cpu with 3 threads in seconds.

| Type\Thread  | 1 | 2 | 3 |
|:----------|:----------|:----------|:----------|
| SPMDKMeans | 2.012492 | 1.503747 | 2.867556 |
| SerialKMeans | 0.701577 | **-** | **-** |
| CriticalKMeans | 1.020082 | 0.508196 | 0.754293 |
| PadKMeans | 1.750566 | 2.029637 | 1.578366 |
| ForKMeans | 0.667854 | 0.883256 | 1.481328 |



## Contribution

Feel free to share your ideas or any other problems. Pull requests are welcomed.

