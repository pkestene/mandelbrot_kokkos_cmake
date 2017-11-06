Mandelbrot_kokkos_cmake
=======================

This is a simple example to illustrate one possible way to use
[Kokkos](https://github.com/kokkos/kokkos) inside an application
built with [CMake](https://cmake.org/)

Download / clone sources
------------------------

Please note that in this application kokkos is used as a git submodule. As such kokkos
will be built by the top level cmake using the provided architecture information.


In order to download both mandelbrot_kokkos sources and kokkos itself, either use the following lines

```bash
git clone git@github.com:pkestene/mandelbrot_kokkos.git
cd mandelbrot_kokkos
git submodule init
git submodule update
```

or do the same in one step (clone mandelbrot_kokkos and kokkos):

```bash
git clone --recursive git@github.com:pkestene/mandelbrot_kokkos.git
```


How to build ?
--------------

1. Build with target device OpenMP


```bash
mkdir build_openmp
cd build_openmp
CXX=YOUR_COMPILER_HERE cmake ..
make
# then you can run the application
./src/mandelbrot_kokkos_openmp
```

Optionnally you can enable HWLOC by passing -DKOKKOS_ENABLE_HWLOC=ON on cmake's command line (or in ccmake curse gui).

2. Build with target device CUDA

You NEED to use nvcc_wrapper as the CXX compiler. nvcc_wrapper is located in kokkos sources, bin subdirectory. You can set the CXX env variable, like this

```bash
mkdir build_cuda
cd build_cuda
export CXX=/path/to/kokkos/bin/nvcc_wrapper
ccmake -DKOKKOS_ENABLE_CUDA=ON -DKOKKOS_GPU_ARCH=Maxwell50 ..
make
# then you can run the application as before
./src/mandelbrot_kokkos_cuda
```

Of course, you will need to adapt variable KOKKOS_GPU_ARCH to your actual GPU architecture (use cuda sample device_query to probe the architecture).
