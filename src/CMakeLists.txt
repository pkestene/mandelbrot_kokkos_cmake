# include header for main application
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#
# mandelbrot_kokkos executable
#
if (KOKKOS_ENABLE_CUDA)
  set(EXE_NAME "mandelbrot_kokkos_cuda")
else()
  set(EXE_NAME "mandelbrot_kokkos_openmp")
endif()

add_executable(${EXE_NAME}
  main.cpp
  OpenMPTimer.cpp
  OpenMPTimer.h
  constants.h
  CudaTimer.h
  kokkos_shared.h
  mandelbrot.h
  )

target_link_libraries(${EXE_NAME} kokkos)
if (KOKKOS_ENABLE_HWLOC)
  target_link_libraries(${EXE_NAME} hwloc)
endif()
  
