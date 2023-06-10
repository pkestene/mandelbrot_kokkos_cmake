#ifndef WRITE_SCREEN_H_
#define WRITE_SCREEN_H_

#include "kokkos_shared.h"
#include "constants.h"

#include <string>
#include <cstdio>

template <typename HostView>
void
write_screen(HostView imageHost, const Constants & constants)
{

  // print aesthetically, dont read this part
  int xmax = 80;
  int ymax = 60;
  for (int y = 0; y < ymax; y++)
  {
    printf("\n");
    for (int x = 0; x < xmax; x++)
    {

      int val = imageHost(y * constants.HEIGHT / ymax, x * constants.WIDTH / xmax);

      if (val == 200)
        printf("&");
      else if (val == 42)
        printf("X");
      else if (val > 64)
        printf("#");
      else if (val > 32)
        printf(":");
      else if (val > 8)
        printf(".");
      else
        printf(" ");
    }
  }

  printf("\n");

} // write_screen

#endif // WRITE_SCREEN_H_
