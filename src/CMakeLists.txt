# include header for main application
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#
# mandelbrot_kokkos executable
#
if (Kokkos_ENABLE_CUDA)
  set(EXE_NAME "mandelbrot_kokkos_cuda")
else()
  set(EXE_NAME "mandelbrot_kokkos_openmp")
endif()

set (EXE_NAME_SRC
  main.cpp
  constants.h
  CudaTimer.h
  write_ppm.h
  write_ppm.cpp
  write_screen.h
  write_screen.cpp
  kokkos_shared.h
  mandelbrot.h
  )

if (Kokkos_ENABLE_OPENMP)
  set (EXE_NAME_SRC
    ${EXE_NAME_SRC}
    OpenMPTimer.cpp
    OpenMPTimer.h)
endif()

add_executable(${EXE_NAME}
  ${EXE_NAME_SRC})

target_link_libraries(${EXE_NAME} kokkos)
if (Kokkos_ENABLE_HWLOC)
  target_link_libraries(${EXE_NAME} hwloc)
endif()
  
