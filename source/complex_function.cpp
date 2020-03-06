// ---------------------------------------------------------------------
// GFractal Project
// Graham Harper
// ---------------------------------------------------------------------

#include "gfractal/complex_function.h"

///////////////
// CFunction 
///////////////
CFunction::CFunction(std::vector< std::complex<double> > &f_roots,
                     int nroots)
 :
 roots(f_roots),
 num_roots(nroots)
{ }

double
CFunction::distance_to_root(std::complex<double> &z, int idx) const
{
  // Assert idx < num_roots
  return norm(z - roots[idx]);
}

/////////////////
// CPolynomial
/////////////////
CPolynomial::CPolynomial(std::vector< std::complex<double> > &poly_coeffs,
                         std::vector< std::complex<double> > &poly_roots)
 :
 CFunction(poly_roots,poly_roots.size()),
 coeffs(poly_coeffs)
{ }

std::complex<double>
CPolynomial::value(std::complex<double> &z) const
{
  // Order is lowest to highest coefficient
  std::complex<double> val(0,0);
  
  // Loop over coefficients
  for(unsigned int i=0; i<coeffs.size(); ++i)
  {
    std::complex<double> tmp(coeffs[i]);
    // Loop over multiplying by z (avoid pow)
    for(unsigned int j=0; j<i; ++j)
      tmp = tmp*z;
    val = val + tmp;
  }
  return val;
}

std::complex<double>
CPolynomial::deriv(std::complex<double> &z) const
{
  // Order is lowest to highest coefficient
  std::complex<double> val(0,0);
  
  // Loop over coefficients
  for(unsigned int i=1; i<coeffs.size(); ++i)
  {
    std::complex<double> tmp(coeffs[i]);
    tmp = ((double) i)*tmp;
    // Loop over multiplying by z (avoid pow)
    for(unsigned int j=1; j<i; ++j)
      tmp = tmp*z;
    val = val + tmp;
  }
  return val;
}

std::complex<double>
CPolynomial::second_deriv(std::complex<double> &z) const
{
  // Order is lowest to highest coefficient
  std::complex<double> val(0,0);
  
  // Loop over coefficients
  for(unsigned int i=2; i<coeffs.size(); ++i)
  {
    std::complex<double> tmp(coeffs[i]);
    tmp = ((double) i*(i-1))*tmp;
    // Loop over multiplying by z (avoid pow)
    for(unsigned int j=2; j<i; ++j)
      tmp = tmp*z;
    val = val + tmp;
  }
  return val;
}
