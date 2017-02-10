# include header for main application
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#
# mandelbrot_kokkos executable
#
if (KOKKOS_INTERNAL_USE_CUDA MATCHES "1")
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

set_target_properties(${EXE_NAME} PROPERTIES
  LINK_FLAGS "${KOKKOS_LDFLAGS}")
target_link_libraries(${EXE_NAME} kokkos hwloc dl)
