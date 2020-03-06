// ---------------------------------------------------------------------
// GFractal Project
// Graham Harper
// ---------------------------------------------------------------------

#ifndef GFRACTAL_newton_fractal_h
#define GFRACTAL_newton_fractal_h

#include <complex>
#include "macros.h"
#include "complex_function.h"

/**
 * 
 *
 * @author Graham Harper
 * @date 2018
 */
class NewtonFractal
{
public: 
  NewtonFractal(CPolynomial &poly);
  
  void set_max_its(int mits) { max_its = mits; }
  void set_dimensions(std::vector<int> &dims) { image_dims[0]=dims[0]; image_dims[1]=dims[1]; }
  void set_window_centered(double xc, double yc, double w, double h) { xmin=xc-w/2.; xmax=xc+w/2.; ymin=yc-h/2.; ymax=yc+h/2.; }
  void set_window(double xa, double xb, double ya, double yb) { xmin=xa; xmax=xb; ymin=ya; ymax=yb; }
  void set_tolerance(double t) { tol=t; }
  
  void compute_fractal();
  
//private:
  
  /**
   * Polynomial that contains the function to be iterated on
   * Its derivative is computed manually using the coefficients
   */
  const CPolynomial f;
  /**
   * Minimum x-coordinate of the fractal
   */
  double xmin;
  /**
   * Maximum x-coordinate of the fractal
   */
  double xmax;
  /**
   * Minimum y-coordinate of the fractal
   */
  double ymin;
  /**
   * Maximum y-coordinate of the fractal
   */
  double ymax;
  /**
   * Maximum number of iterations to convergence
   */
  int max_its;
  /**
   * Precision to determine when convergence is achieved
   */
  double tol;
  /**
   * Dimensions of the image that will be generated.
   * Used to generate the xy mesh of the window.
   */
  std::vector<int> image_dims;
  /**
   * Data corresponding to the number of iterations to
   * convergence after applying Newton's method
   */
  std::vector< std::vector<int> > its;
  /**
   * Data corresponding to the root that each point
   * converges to.
   */
  std::vector< std::vector<int> > root;
};
#endif
