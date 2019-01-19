#include <cstdio>
#include <cstdlib> // for atoi
#include <iostream>
#include <fstream>

#include <omp.h>

#include "constants.h"
#include "kokkos_shared.h"
#include "mandelbrot.h"

#ifdef KOKKOS_ENABLE_CUDA
#include "CudaTimer.h"
#else // OpenMP
#include "OpenMPTimer.h"
#endif

#include "write_screen.h"
#include "write_ppm.h"

#include <unistd.h>

using namespace std;

// ==================================================================
// ==================================================================
// ==================================================================
void compute_mandelbrot_set(int argc, char* argv[]) {

#ifdef KOKKOS_ENABLE_CUDA
  CudaTimer timer;
#else
  OpenMPTimer timer;
#endif
  
  int default_size = 8192;
  if (argc>1)
    default_size = std::atoi(argv[1]);

  printf("Compute Mandelbrot set of size %dx%d\n",default_size,default_size);
  
  Constants constants = Constants(default_size);

  // prepare data array for Mandelbrot set computation
  DataArray     image     = DataArray("image", constants.WIDTH,constants.HEIGHT);
  DataArrayHost imageHost = Kokkos::create_mirror_view(image);

  /*
   * Actual computation (GPU with CUDA or CPU with OpenMP)
   */
  timer.start();

  {
    //using namespace Kokkos::Experimental;
    MandelbrotFunctor functor(image, constants);
    using range2d_t =
      Kokkos::Experimental::MDRangePolicy< Kokkos::Experimental::Rank<2> ,
					   Kokkos::IndexType<int> >;
    range2d_t range( {0,0}, {constants.WIDTH,constants.HEIGHT} );
    //Kokkos::Experimental::md_parallel_for(range, functor);
    Kokkos::parallel_for(range, functor);
  }
  
  timer.stop();
  printf("end of mandelbrot loop reached ...\n");
  printf("Compute time: %lf seconds.\n", timer.elapsed());
  
  // copy back results from device to host
  Kokkos::deep_copy(imageHost,image);


  write_screen(imageHost, constants);

  // save color ppm file
  if (0) {
    std::string filename("mandelbrot.ppm");
    save_ppm(imageHost, filename, constants);
  }
  printf("Compute time: %lf seconds.\n", timer.elapsed());

} // compute_mandelbrot_set

//============================================================
//============================================================
int main(int argc, char* argv[]) {

  /*
   * Initialize kokkos (host + device)
   * 
   * If CUDA is enabled, Kokkos will try to use the default GPU, i.e. GPU #0 if you
   * have multiple GPUs.
   */
  Kokkos::initialize(argc, argv);

  {
    std::cout << "##########################\n";
    std::cout << "KOKKOS CONFIG             \n";
    std::cout << "##########################\n";
    
    std::ostringstream msg;
    std::cout << "Kokkos configuration" << std::endl;
    if ( Kokkos::hwloc::available() ) {
      msg << "  hwloc( NUMA[" << Kokkos::hwloc::get_available_numa_count()
          << "  ] x CORE["    << Kokkos::hwloc::get_available_cores_per_numa()
          << "  ] x HT["      << Kokkos::hwloc::get_available_threads_per_core()
          << "  ] )"
          << std::endl ;
    }
    Kokkos::print_configuration( std::cout );
    std::cout << msg.str();
    std::cout << "##########################\n";
  }

  compute_mandelbrot_set(argc,argv);  
     
  Kokkos::finalize();

  return 0;
}
