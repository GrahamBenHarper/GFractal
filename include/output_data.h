// ---------------------------------------------------------------------
// GFractal Project
// Graham Harper
// ---------------------------------------------------------------------

#ifndef GFRACTAL_output_data_h
#define GFRACTAL_output_data_h
#include "macros.h"
#include "newton_fractal.h"
#include "julia_fractal.h"

class OutputData
{
public:
  static void write_bitmap(NewtonFractal &frac, char* filename);
  static void write_bitmap(JuliaFractal &frac, char* filename);

  //static int save_bmp(int width, int height, char* filename,
  //           int *r, int *g, int *b);
};


#endif
