// ---------------------------------------------------------------------
// GFractal Project
// Graham Harper
// ---------------------------------------------------------------------

#ifndef FRAC_CFunction_h
#define FRAC_CFunction_h

#include <vector>
#include <complex>

/**
 * This virtual class defines the structure for the implementations.
 * Newton fractals must have a function to evaluate at a point as
 * well as a function to evaluate the derivative at a point. It is
 * beneficial to store the roots of the function if possible.
 *
 * @author Graham Harper
 * @date 2019
 */
class CFunction
{
public: 
  /**
   * Constructor that takes roots and number of roots as arguments
   */
  CFunction(std::vector< std::complex<double> > &f_roots,
            int nroots);
  /**
   * Returns the value of the <tt>CFunction</tt>
   * evaluated at the complex-valued point @z
   */
  virtual std::complex<double> value(std::complex<double> &z) const { return std::complex<double>(0,0); }
  /**
   * Returns the value of the <tt>CFunction</tt>'s
   * derivative evaluated at the complex-valued point @z
   */
  virtual std::complex<double> deriv(std::complex<double> &z) const { return std::complex<double>(0,0); }
  /**
   * Returns the value of the <tt>CFunction</tt>'s
   * second derivative evaluated at the complex-valued point @z
   */
  virtual std::complex<double> second_deriv(std::complex<double> &z) const { return std::complex<double>(0,0); }
  /**
   * Returns the distance between a complex point @p z and root i
   */
  double distance_to_root(std::complex<double> &z, int idx) const;  
  /**
   * The list of expected 0s for this particular function.
   */
  const std::vector< std::complex<double> > roots;
  /**
   * The number of roots for this particular function
   */
  const int num_roots;
private:
};

////////////////////
// CPolynomial
////////////////////
/**
 * This class implements the CFunction class for the case
 * where the function is a polynomial of 1 complex variable
 */
class CPolynomial : public CFunction
{
public:
  CPolynomial(std::vector< std::complex<double> > &poly_coeffs,
              std::vector< std::complex<double> > &poly_roots);

  /**
   * Returns the value of the <tt>CFunction</tt>
   * evaluated at the complex-valued point @z
   */
  virtual std::complex<double> value(std::complex<double> &z) const;
  /**
   * Returns the value of the <tt>CFunction</tt>'s
   * derivative evaluated at the complex-valued point @z
   */
  virtual std::complex<double> deriv(std::complex<double> &z) const;
  /**
   * Returns the value of the <tt>CFunction</tt>'s
   * second derivative evaluated at the complex-valued point @z
   */
  virtual std::complex<double> second_deriv(std::complex<double> &z) const;

  const std::vector< std::complex<double> > coeffs;

//private:
};

#endif
