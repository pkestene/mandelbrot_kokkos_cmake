cmake_minimum_required(VERSION 3.18)

project(mandelbrot_kokkos_cmake CXX)

# always export compile commands database
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# C++17 is for Kokkos (version >= 4.0.00)
set(CMAKE_CXX_STANDARD 17)
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
include(cmake/preventBuildInSource.cmake)

#
# Init build type: Release, Debug, ...
#
include(cmake/initBuildType.cmake)

#
# common flags
#
if (USE_DOUBLE)
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUSE_DOUBLE" )
endif()

#
# dependencies : kokkos
#
include(cmake/build_or_find_kokkos.cmake)

#
# sources
#
add_subdirectory(src)

##################### PRINT CONFIGURE STATUS ######################
message("//===================================================")
message("// ${PROJECT_NAME} build configuration:")
message("//===================================================")
message("")
message("  CMake version          : ${CMAKE_VERSION}")
if (NOT CMAKE_BUILD_TYPE)
  message("  CMake build type       : NOT SET !")
else()
  message("  CMake build type       : ${CMAKE_BUILD_TYPE}")
endif()
message("  CMake install prefix   : ${CMAKE_INSTALL_PREFIX}")
message("  CMake system processor : ${CMAKE_SYSTEM_PROCESSOR}")
message("  CMake system name (OS) : ${CMAKE_SYSTEM_NAME}")
message("")
message("  C++ Compiler : ${CMAKE_CXX_COMPILER_ID} "
                         "${CMAKE_CXX_COMPILER_VERSION} "
                         "${CMAKE_CXX_COMPILER_WRAPPER}")
message("                 ${CMAKE_CXX_COMPILER}")
message("")
if(Kokkos_ENABLE_OPENMP)
  message("  Kokkos_ENABLE_OPENMP         = ${Kokkos_ENABLE_OPENMP}")
endif()

if(Kokkos_ENABLE_CUDA)
  message("  Kokkos_ENABLE_CUDA           = ${Kokkos_ENABLE_CUDA}")

  if( (${Kokkos_CUDA_LAMBDA_ENABLED}) OR (${Kokkos_ENABLE_CUDA_LAMBDA}))
    message("  Kokkos_ENABLE_CUDA_LAMBDA    = ON")
  else()
    message("  Kokkos_ENABLE_CUDA_LAMBDA    = OFF")
  endif()

  if( (${Kokkos_CUDA_CONSTEXPR_ENABLED}) OR (${Kokkos_ENABLE_CUDA_CONSTEXPR}))
    message("  Kokkos_ENABLE_CUDA_CONSTEXPR = ON")
  else()
    message("  Kokkos_ENABLE_CUDA_CONSTEXPR = OFF")
  endif()

  if( (${Kokkos_CUDA_UVM_ENABLED}) OR (${Kokkos_ENABLE_CUDA_UVM}))
    message("  Kokkos_ENABLE_CUDA_UVM       = ON")
  else()
    message("  Kokkos_ENABLE_CUDA_UVM       = OFF")
  endif()

  message("  Kokkos CUDA   flags          = ${KOKKOS_CUDA_OPTIONS}")
  #message("  CUDA Compiler      : ${CMAKE_CUDA_COMPILER}")
  #message("  CUDA Compiler exec : ${CUDA_NVCC_EXECUTABLE}")
  #message("  CUDA Compile flags : ${CUDA_NVCC_FLAGS}")
endif(Kokkos_ENABLE_CUDA)

if(Kokkos_ENABLE_HIP)
  message("  Kokkos_ENABLE_HIP            = ${Kokkos_ENABLE_HIP}")
endif(Kokkos_ENABLE_HIP)

if ( (${Kokkos_TPLS_HWLOC_ENABLED}) OR (${Kokkos_ENABLE_HWLOC}) )
  message("  Kokkos_ENABLE_HWLOC          = ON")
else()
  message("  Kokkos_ENABLE_HWLOC          = OFF")
endif()

message("  Kokkos architecture          = ${Kokkos_ARCH}")
