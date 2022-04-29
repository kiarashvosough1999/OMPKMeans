# OMPKMeans

![Swift](https://img.shields.io/badge/C++-14-orange?style=flat-square)
![Platforms](https://img.shields.io/badge/Platforms-Linux-yellowgreen?style=flat-square)

Implemented KMeans with opm library in order to parallelize and decrease clustering time consuming. 


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

I Used 4 Approaches to use omp constructs and 1 Serial and simple one. Each of them is a class that implements algorithm and spicific constructs: 

- SerialKMeans
- CriticalKMeans
- SPMDKMeans
- ForKmeans
- D3PadKmeans

## Serial KMeans

This is the simple serial implementation of KMeans and uses no parallelisim.

## Critical KMeans

On this approach I used `omp parallel` construction and to avoid data-race, 'omp critical' was used in order to modify clusters.

## SPMD KMeans

In computing, SPMD (single program, multiple data) is a technique employed to achieve parallelism; it is a subcategory of MIMD. Tasks are split up and run simultaneously on multiple processors with different input in order to obtain results faster. SPMD is the most common style of parallel programming.

So to acheive this approach I used a 2D Array to store Clusters for each thread and modify each of them on its own runnig thread, this way we splited up our tasks and avoided data-races, but at the end we should merge the results of each thread's cluster together.

## Installation

To see if GCC is already installed on your system, open a Terminal window and enter the following command:

``` bash
gcc -v
```

If GCC isn't installed, run the following command from the Terminal window to update the Ubuntu package lists. An out-of-date Linux distribution can interfere with getting the latest packages.

``` bash
sudo apt-get update
```

Next, install the GNU compiler, make, and the GDB debugger with this command:

``` bash
sudo apt-get install build-essential gdb
```


### CMake

Use Following command to use gui cmake for building project:

``` bash
cmake-gui
```

Or use command-line:

For example, from the command line we could navigate to the main root of project's directory of the CMake source code tree and create a build directory:

``` bash
mkdir Step1_build
```

Next, navigate to the build directory and run CMake to configure the project and generate a native build system:

``` bash
cd Step1_build
cmake ../Step1
```

Then call that build system to actually compile/link the project:

``` bash
cmake --build .
```

Finally, try to use the newly built `1_3omp` with these commands:

``` bash
1_3omp
```

## Output

After running project and whenever it finished, there will be a `outputResult.txt` file that logged every approach and the final centroid of clusters and more info.


## Contribution

Feel free to share your ideas or any other problems. Pull requests are welcomed.

