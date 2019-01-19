cmake_minimum_required(VERSION 3.1)

project(mandelbrot_kokkos_cmake CXX)

# C++11 is for Kokkos
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)

#
# default local cmake macro repository
#
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

#
# Prevent from build in source tree
# The recommended way of building this app is one build directory per hardware config
# e.g. mkdir build_openmp for openmp build
#  or  mkdir build_cuda for cuda build
#
include(${PROJECT_SOURCE_DIR}/cmake/preventBuildInSource.cmake)

#
# Init build type: Release, Debug, ...
#
include(${PROJECT_SOURCE_DIR}/cmake/initBuildType.cmake)

#
# common flags
#
if (USE_DOUBLE)
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUSE_DOUBLE" )
endif()

#
# sources
#

# first buid kokkos
add_subdirectory(external/kokkos)

# pass Kokkos include directories to our target application
include_directories(${Kokkos_INCLUDE_DIRS_RET})

add_subdirectory(src)
