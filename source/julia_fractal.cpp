// ---------------------------------------------------------------------
// GFractal Project
// Graham Harper
// ---------------------------------------------------------------------

#include "gfractal/julia_fractal.h"

////////////////////
// JuliaFractal
////////////////////
JuliaFractal::JuliaFractal(std::complex<double> c)
 :
 frac_c(c),
 xmin(-1),
 xmax(1),
 ymin(-1),
 ymax(1),
 max_its(20),
 tol(1e-6),
 image_dims(2,100),
 its()
{ }

void
JuliaFractal::compute_fractal()
{
  int width = image_dims[0];
  int height = image_dims[1];
  std::vector<double> x(width);
  std::vector<double> y(height);

  // Compute the grid of x-values
  double dx = (xmax-xmin)/((double)width);
  for(int i=0; i<width-1; ++i)
    x[i] = xmin+i*dx;
  x[width-1] = xmax;

  // Compute the grid of y-values
  double dy = (ymax-ymin)/((double)height);
  for(int i=0; i<height-1; ++i)
    y[i] = ymin+i*dy;
  y[height-1] = ymax;

  // Initialize its
  its.resize(0);

  // NEWTON'S METHOD
  for(int i=1; i<=height; ++i)
  {
    std::vector<int> tmp_its(width);

    for(int j=1; j<=width; ++j)
    {
      std::complex<double> a(x[j-1],y[i-1]);
      for(int k=0; k<max_its; ++k)
      {
        a = a*a + frac_c;
        if(norm(a)>2)
        {
          tmp_its[j-1]=k;
          break;
        }
        if(k==max_its-1)
        {
          tmp_its[j-1]=max_its-1;
        }
      }
    }
    its.push_back(tmp_its);
  }
}
