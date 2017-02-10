#ifndef CONSTANTS_H_
#define CONSTANTS_H_

struct Constants {

  unsigned int WIDTH;
  unsigned int HEIGHT;
  unsigned int MAX_ITERS;
  unsigned int MAX_COLOR;
  double xmin;
  double xmax;
  double ymin;
  double ymax;
  double dx;
  double dy;
  
  Constants() : 
    WIDTH(8192), HEIGHT(8192),
    MAX_ITERS(4000), MAX_COLOR(255),
    xmin(-1.7), xmax(.5), ymin(-1.2), ymax(1.2),
    dx(0.0), dy(0.0)
  {
    dx=(xmax-xmin)/WIDTH;
    dy=(ymax-ymin)/HEIGHT;
  }
};

#endif

