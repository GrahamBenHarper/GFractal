// ---------------------------------------------------------------------
// GFractal Project
// Graham Harper
// ---------------------------------------------------------------------

#ifndef FRAC_julia_fractal_h
#define FRAC_julia_fractal_h

#include <vector>
#include <complex>
#include <iostream>

/**
 *
 *
 * @author Graham Harper
 * @date 2018
 */
class JuliaFractal
{
public:
  JuliaFractal(std::complex<double> c);

  void set_max_its(int mits) { max_its = mits; }
  void set_dimensions(std::vector<int> &dims) { image_dims[0]=dims[0]; image_dims[1]=dims[1]; }
  void set_window(double xa, double xb, double ya, double yb) { xmin=xa; xmax=xb; ymin=ya; ymax=yb; }
  void set_tolerance(double t) { tol=t; }

  void compute_fractal();

//private:

  /**
   * The value c for the Julia fractal
   */
  std::complex<double> frac_c;
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
};
#endif
