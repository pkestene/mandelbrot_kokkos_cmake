# Mandelbrot_kokkos_cmake

This is a simple example to illustrate one possible way to use
[Kokkos](https://github.com/kokkos/kokkos) inside an application
built with [CMake](https://cmake.org/)

## Download / clone sources

Please note that, in this application, kokkos library is required.
- if kokkos is already available, you just need to set `CMAKE_PREFIX_PATH` to point to its installation path
- if kokkos is not availalble on your system, you can build by using cmake flag `-DMANDELBROT_KOKKOS_BUILD=ON`

In order to download `mandelbrot_kokkos_cmake` sources, use the following lines

```bash
git clone git@github.com:pkestene/mandelbrot_kokkos_cmake.git
```


## How to build ?

### Build with target device OpenMP

```bash
mkdir -p _build/openmp; cd _build/openmp
cmake -DMANDELBROT_KOKKOS_BUILD=ON -DMANDELBROT_KOKKOS_BACKEND=OpenMP ../..
make
# then you can run the application
./src/mandelbrot_kokkos_openmp
```

Optionnally you can enable HWLOC by passing `-DKokkos_ENABLE_HWLOC=ON` on cmake's command line (or in ccmake curse gui).

### Build with target device CUDA

Of course you NEED to have `nvcc` compiler available on your system. Just a few notices:

- if you do not have already kokkos library available, it be compiled for your.
- if you're compiling on a platform equipped with an Nvidia GPU, the GPU architecture version will be detected by kokkos cmake build system.
- if you don't have a GPU, you can still build the code (but not run); you can specify the target architecture using flag `-DKokkos_ARCH`.

```bash
mkdir _build/cuda; cd _build/cuda
cmake -DMANDELBROT_KOKKOS_BUILD=ON -DMANDELBROT_KOKKOS_BACKEND=Cuda -DKokkos_ENABLE_CUDA_LAMBDA=ON -DKokkos_ENABLE_HWLOC=ON ../..
make
# then you can run the application as before
./src/mandelbrot_kokkos_cuda
```
