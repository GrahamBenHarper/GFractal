// ---------------------------------------------------------------------
// GFractal Project
// Graham Harper
// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// http://www.stack.nl/~dimitri/doxygen/manual/docblocks.html
//
// ---------------------------------------------------------------------

#include "gfractal/newton_fractal.h"

////////////////////
// NewtonFractal
////////////////////
NewtonFractal::NewtonFractal(CPolynomial &poly)
 :
 f(poly),
 xmin(-1),
 xmax(1),
 ymin(-1),
 ymax(1),
 max_its(20),
 tol(1e-6),
 image_dims(2,100),
 its(),
 root()
{ }

void
NewtonFractal::compute_fractal()
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
  
  // Initialize its and root
  its.resize(0);
  root.resize(0);
  
  // NEWTON'S METHOD
  for(int i=1; i<=height; ++i)
  {
    std::vector<int> tmp_its(width);
    std::vector<int> tmp_root(width);

    for(int j=1; j<=width; ++j)
    {
      std::complex<double> a(x[j-1],y[i-1]);
      for(int k=0; k<max_its; ++k)
      {
        bool conv = false;
        std::vector<double> errors(f.num_roots);
        //std::cout << "a = " << a.real() << " + " << a.imag() << "i" << std::endl;
	//std::cout << "f(a) = " << (f.value(a)).real() << " + " << (f.value(a)).imag() << "i" << std::endl;
	//std::cout << "f'(a) = " << (f.deriv(a)).real() << " + " << (f.deriv(a)).imag() << "i" << std::endl;
        //std::cout << "(i,j) = (" << i << "," << j << ")" << std::endl;
        
        a = a - f.value(a)/f.deriv(a);

        for(int ir=0; ir<f.num_roots; ++ir)
        {
          if(f.distance_to_root(a,ir) < tol)
          {
            tmp_root[j-1] = ir;
            tmp_its[j-1] = k;
            conv = true;
          } 
        }
        
        if(conv)
          break;
        
        if(k==max_its-1) // this can only be reached if convergence fails
        {
          tmp_root[j-1] = -1;     // assign a fake root but
          tmp_its[j-1] = max_its; // color it black anyway
        }
      }
    }
    its.push_back(tmp_its);
    root.push_back(tmp_root);
  }
}
