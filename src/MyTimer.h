#ifndef MANDELBROT_KOKKOS_TIMER_H_
#define MANDELBROT_KOKKOS_TIMER_H_

#include "kokkos_shared.h"

#if defined(KOKKOS_ENABLE_OPENMP) || defined(KOKKOS_ENABLE_SERIAL)
#  include "OpenMPTimer.h"
#endif

#ifdef KOKKOS_ENABLE_CUDA
#  include "CudaTimer.h"
#endif

namespace
{

/**
 * \tparam ExecutionSpace is supposed to be a Kokkos execution space (e.g. Kokkos::OpenMP)
 */
template <typename ExecutionSpace>
struct MyTimer;

#ifdef KOKKOS_ENABLE_SERIAL
template <>
struct MyTimer<Kokkos::Serial>
{
  using Timer = OpenMPTimer;
};
#endif // KOKKOS_ENABLE_SERIAL

#ifdef KOKKOS_ENABLE_OPENMP
template <>
struct MyTimer<Kokkos::OpenMP>
{
  using Timer = OpenMPTimer;
};
#endif // KOKKOS_ENABLE_OPENMP

#ifdef KOKKOS_ENABLE_CUDA
template <>
struct MyTimer<Kokkos::Cuda>
{
  using Timer = CudaTimer;
};
#endif // KOKKOS_ENABLE_CUDA

} // namespace

#endif // MANDELBROT_KOKKOS_TIMER_H_
