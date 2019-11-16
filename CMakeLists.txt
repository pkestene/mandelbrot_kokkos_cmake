cmake_minimum_required(VERSION 3.10)

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

# first build kokkos
add_subdirectory(external/kokkos)

# pass Kokkos include directories to our target application
include_directories(${Kokkos_INCLUDE_DIRS_RET})

add_subdirectory(src)

##################### PRINT CONFIGURE STATUS ######################
message("//===================================================")
message("  ${PROJECT_NAME} build configuration:")
message("//===================================================")
message("  C++ Compiler : ${CMAKE_CXX_COMPILER_ID} "
                         "${CMAKE_CXX_COMPILER_VERSION} " 
                         "${CMAKE_CXX_COMPILER_WRAPPER}")
message("                 ${CMAKE_CXX_COMPILER}")
message("  Kokkos OpenMP enabled : ${Kokkos_ENABLE_OPENMP}")
message("  Kokkos CUDA   enabled : ${Kokkos_ENABLE_CUDA}")
if (Kokkos_ENABLE_CUDA)
  message("  Kokkos CUDA   Lambda  : ${Kokkos_ENABLE_CUDA_LAMBDA}")
  message("  Kokkos CUDA   flags   : ${KOKKOS_CUDA_OPTIONS}")
endif(Kokkos_ENABLE_CUDA)
message("  Kokkos HWLOC  enabled : ${Kokkos_ENABLE_HWLOC}")

