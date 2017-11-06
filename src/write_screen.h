#ifndef WRITE_SCREEN_H_
#define WRITE_SCREEN_H_

#include <string>

#include "kokkos_shared.h" 
#include "constants.h"

void write_screen(DataArrayHost      imageHost,
		  const Constants&   constants);

#endif // WRITE_SCREEN_H_
