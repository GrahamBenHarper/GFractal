// ---------------------------------------------------------------------
// GFractal Project
// Graham Harper
// ---------------------------------------------------------------------

#ifndef FRAC_output_data_h
#define FRAC_output_data_h
#include "newton_fractal.h"
#include "julia_fractal.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class OutputData
{
public:
  static void write_bitmap(NewtonFractal &frac, char* filename);
  static void write_bitmap(JuliaFractal &frac, char* filename);

  //static int save_bmp(int width, int height, char* filename,
  //           int *r, int *g, int *b);
};


#endif
