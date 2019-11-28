// ---------------------------------------------------------------------
// GFractal Project
// Graham Harper
// ---------------------------------------------------------------------

#include <iostream>
#include <ctime>
#include "gfractal/include/color_map.h"
#include "gfractal/include/output_data.h"
#include "gfractal/include/newton_fractal.h"
#include "gfractal/include/julia_fractal.h"
#include "gfractal/include/complex_function.h"

// This code will compute 8 bitmap images of size 1024x768 from a Julia
// set fractal sampled from points around the unit circle starting at 1+0i
// and moving counter-clockwise. It also times the program using ctime,
// although another option may be to use time in the command line.

int run_julia_fractal_loop()
{
  // avoid making this larger than 100 unless there is sufficient room
  const unsigned int num_fractals = 150;

  // start the clock
  clock_t totalStart = clock();

  for(unsigned int i=0; i<num_fractals; ++i)
  {
    // Set up the fractal
    std::cout << "Defining the JuliaFractal" << std::endl;

    // Sample points from the unit circle
    const double pi = std::acos(-1);
    const double x = std::cos(i*2.*pi/num_fractals);
    const double y = std::sin(i*2.*pi/num_fractals);

    std::complex<double> c(x,y);
    JuliaFractal frac(c);
    std::vector<int> dimensions(2); dimensions[0]=1024; dimensions[1]=768;
    frac.set_dimensions(dimensions);

    // Compute the fractal
    std::cout << "Iterating the JuliaFractal" << std::endl;
    frac.compute_fractal();

    // Output the fractal
    std::cout << "Outputting the JuliaFractal" << std::endl;
    char filename[64] = "image000.bmp";
    filename[7] = i%10        + '0';
    filename[6] = (i%100)/10  + '0';
    filename[5] = i/100       + '0';
    OutputData::write_bitmap(frac,filename);

    std::cout << "Done!" << std::endl;
  }

  // Show total computation time
  clock_t totalEnd = clock();
  std::cout << "Total time = "
            << static_cast<double>(totalEnd-totalStart)/CLOCKS_PER_SEC
            << " seconds" << std::endl;
  return 0;
}



int main()
{
  run_julia_fractal_loop();

  return 0;
}
