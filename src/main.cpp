#include <cstdio>
#include <cstdlib> // for atoi
#include <iostream>
#include <fstream>

#include <omp.h>

#include "constants.h"
#include "kokkos_shared.h"
#include "mandelbrot.h"

#ifdef CUDA
#include "CudaTimer.h"
#else // OpenMP
#include "OpenMPTimer.h"
#endif

#include <unistd.h>

using namespace std;

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
#if defined( CUDA )
    Kokkos::Cuda::print_configuration( msg );
#else
    Kokkos::OpenMP::print_configuration( msg );
#endif
    std::cout << msg.str();
    std::cout << "##########################\n";
  }

#ifdef CUDA
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
    Kokkos::Experimental::md_parallel_for(range, functor);
  }
  
  timer.stop();
  printf("end of mandelbrot loop reached ...\n");
  printf("Compute time: %lf seconds.\n", timer.elapsed());
  
  // copy back results from device to host
  Kokkos::deep_copy(imageHost,image);
  
  // print aesthetically, dont read this part
  int xmax=80;
  int ymax=60;
  for(int y=0;y<ymax;y++) {
    printf("\n");
    for(int x=0;x<xmax;x++) {

      int val = imageHost(y*constants.HEIGHT/ymax,x*constants.WIDTH/xmax);
      
      if (val==200) printf("&");
      else if (val==42) printf("X");
      else if(val>64) printf("#");
      else if(val>32) printf(":");
      else if(val>8) printf(".");
      else printf(" ");
    }
  }
  
  printf("\n");

  // save color ppm file
  if (0) {
    FILE* myfile = fopen("mandelbrot.ppm","w");
    
    fprintf(myfile, "P6 %d %d 255\n", constants.WIDTH , constants.HEIGHT);
    for(unsigned int i=0; i<constants.WIDTH; ++i) {
      for(unsigned int j=0; j<constants.HEIGHT; ++j) {
	
	unsigned char data;
	// create an arbitrary RBG code mapping values taken by imageHost
	data = imageHost(i,j) % 4 * 64;
	fwrite(&data,1,1,myfile);
	data = imageHost(i,j) % 8 * 32;
	fwrite(&data,1,1,myfile);
	data = imageHost(i,j) % 16 * 16;
	fwrite(&data,1,1,myfile);
      }
    }

    fclose(myfile);
  }
  printf("Compute time: %lf seconds.\n", timer.elapsed());
     
  Kokkos::finalize();

  return 0;
}
