#include "write_ppm.h"

void save_ppm(DataArrayHost      imageHost,
	      const std::string& filename,
	      const Constants&   constants)
{

  FILE* myfile = fopen(filename.c_str(),"w");
  
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
  
} // save_ppm
