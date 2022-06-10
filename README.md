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
- [License](#license)


## Requirements

| Platform | Minimum g++ Version | Minimum CMake Version | Status |
| --- | --- | --- | --- |
| Linux | 5.0 | 3.21 | Tested |

## Features

- [x] Used 4 Approaches To Use OMP + 1 Serial Approach.
- [x] Structured Implementation.
- [x] Support Multi Dimension DataSets.
- [x] Support Generic DataSets.
- [x] Plotting Final Cluster. 

## Implementation

We Used 4 Approaches to use omp constructs 1 Serial and a simple one. Each of them is a class that implements an algorithm and specific constructs: 

- **SerialKMeans**
- **CriticalKMeans**
- **SPMDKMeans**
- **ForKmeans**
- **D3PadKmeans**

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

The result of execution on 4-core cpu with 12 threads in seconds.

| Type\Thread  | 1 | 2 | 3 |	4	| 5 |	6 |	7 |	8 |	9 |	10 | 11 |	12 |
|:----------|:----------|:----------|:----------|:----------|:----------|:----------|:----------|:----------|:----------|:----------|:----------|:----------|
| SPMD	    | 1.311	| 1.54 | 1.92 | 2.71 | 2.61	| 2.77 | 4.07	| 7.18 | 7.02| **3.38** | 6.46 | 5.88 |
| Serial	  | 1.07 | - | -	| -	| - | -	| -	| -	| -	| -	| -	| - |
| Critical	| 0.75 | 0.63 | 0.33	| 0.29 | 0.32	| 0.46 | 0.3 | 0.29	| 0.3	| 0.43 | 0.4 | **0.21** |
| Pad	      | **1.21** | 1.56 | 1.97	| 3.21 | 2.83	| 4.37 | 4.61 | 3.81 | 4.39	| 3.90 | 4.89 | 4.50 |
| For	      | 0.57 | 0.70 | 1.29	| 0.75 | 0.93	| 0.85 | **0.55**	| 0.70 | 1.29	| 0.75 | 0.93	| 0.85 |


## Contribution

Feel free to share your ideas or any other problems. Pull requests are welcomed.

## License

OMPKMeans was released under an MIT license. See [LICENSE](https://github.com/kiarashvosough1999/OMPKMeans/blob/master/LICENSE) for more information.
