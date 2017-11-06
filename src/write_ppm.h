#ifndef WRITE_PPM_H_
#define WRITE_PPM_H_

#include <string>

#include "kokkos_shared.h" 
#include "constants.h"

void save_ppm(DataArrayHost      imageHost,
	      const std::string& filename,
	      const Constants&   constants);

#endif // WRITE_PPM_H_
