Mandelbrot_kokkos_cmake
=======================

This is a simple example to illustrate one possible way to use
[Kokkos](https://github.com/kokkos/kokkos) inside an application
built with [CMake](https://cmake.org/)

How to use it ?
---------------

The top-level CMakeLists.txt defines an option: BUILD_KOKKOS

1. If BUILD_KOKKOS is ON, it will first clone kokkos using git (branch develop_cmake from https://github.com/pkestene/kokkos, a small variant of kokkos which generates kokkos.cmake in install dir), build kokkos and then CMakeLists.txt re-invoke itself to build the user application.

```bash
mkdir build_with_kokkos_from_git
cd build_with_kokkos_from_git
CXX=YOUR_COMPILER_HERE ccmake -DBUILD_KOKKOS=ON -DKOKKOS_CONFIGURE_LINE="--with-cuda --arch=Maxwell50" ..
make
# then you can run the application
./src/mandelbrot_kokkos_cuda
```

Variable KOKKOS_CONFIGURE_LINE will be passed as argument to Kokkos's generate_makefile.sh script.
Of course, you need to adapt this variable to your architecture. See kokkos documentation to know more about that.

2. If BUILD_KOKKOS is OFF, it assumes that kokkos is already installed, and that environment variable KOKKOS_PATH is set, and also assuming KOKKOS_PATH contains file kokkos.cmake that the top level CMakeLists.txt will include to build the application.

```bash
mkdir build_with_kokkos_installed
cd build_with_kokkos_installed
CXX=YOUR_COMPILER_HERE ccmake -DBUILD_KOKKOS=OFF ..
make
# then you can run the application as before
./src/mandelbrot_kokkos_cuda
```


