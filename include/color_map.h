// ---------------------------------------------------------------------------
//
//
// ---------------------------------------------------------------------------

#ifndef FRAC_colormap_h
#define FRAC_colormap_h
#include <vector>
#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>

/**
 * The interpolation type used by the ColorMap class. These will help ColorMap
 * determine which colors are drawn for intermediate values of iterations.
 *
 * The functions described are normally defined on the interval [0,1]x[0,1]
 * passing from the point (0,0) to (1,1), and then they are mapped via
 * translation and scaling so the endpoints match the corresponding color
 * values.
 *
 * interpolation_cubic and interpolation_cubic spline both rely on the values
 * of the neighboring colors in order to map correctly
 *
 * @ingroup colormap
 */
enum InterpolationType
{
  /**
   * Interpolate between colors using linear combinations.
   *
   * $f(t) = t$
   */
  interpolation_linear,
  /**
   * Interpolate between colors using cubic interpolation from the four
   * adjacent colors.
   */
  interpolation_cubic,
  /**
   * Interpolate between colors using cubic splines, which yield a continuous
   * color function with continuous first derivatives.
   */
  interpolation_cubicspline,
  /**
   * Interpolate between colors using the smoothstep, which is defined to have
   * zero derivatives at the endpoints. This yields a continuous color
   * function with continuous first derivatives.
   *
   * $f(t) = 3t^2 - 2t^3$
   */
  interpolation_smoothstep,
  /**
   * Interpolate between colors using the smootherstep, which is defined to
   * have zero first and second derivatives at the endpoints. This yields a
   * continuous color function with continuous first and second derivatives.
   *
   * $f(t) = 6t^5 - 15t^4 + 10t^3$
   */
  interpolation_smootherstep,
  /**
   * Interpolate between colors using the smootheststep function, which is
   * defined to have zero first, second, and third derivatives at the
   * endpoints. This yields a continuous color function with continuous first,
   * second, and third derivatives.
   *
   * $f(t) = -20t^7 + 70t^6 - 84t^5 + 35t^4$
   */
  interpolation_smootheststep
};

/**
 * The Color class stores RGB information and offers an interface for
 */

class Color
{
public:
  Color()
    : r(0),
      g(0),
      b(0) {}

  Color(const unsigned int red,
        const unsigned int green,
        const unsigned int blue)
    : r(red),
      g(green),
      b(blue) {}

  unsigned int red() const { return r; }
  unsigned int green() const { return g; }
  unsigned int blue() const { return b; }



  Color& operator+=(const Color& rhs)
  {
    r = (r+rhs.red()   < 255 ? r+rhs.red()   : 255);
    g = (g+rhs.green() < 255 ? g+rhs.green() : 255);
    b = (b+rhs.blue()  < 255 ? b+rhs.blue()  : 255);
    return *this;
  }

  friend Color operator+(Color lhs,
                         const Color& rhs)
  {
    lhs += rhs;
    return lhs;
  }

  friend Color operator*(Color lhs,
                         const double a)
  {
    lhs.r = (lhs.red()*a     < 255 ? lhs.red()*a : 255);
    lhs.g = (lhs.green()*a < 255 ? lhs.green()*a : 255);
    lhs.b = (lhs.blue()*a   < 255 ? lhs.blue()*a : 255);
    return lhs;
  }

  std::ostream& operator<<(std::ostream& out);


private:
  unsigned int r;
  unsigned int g;
  unsigned int b;
};

//Color C_RED(0,0,255);


/**
 * The ColorMap class is a class to store an array of colors. It is used with
 * fractals that color based on iteration numbers, including the Mandelbrot
 * and Julia sets. It will interpolate based on the specified
 * interpolation_type, which will default to interpolation_linear if none is
 * provided. It requires at least two colors in order to operate correctly.
 */

class ColorMap
{
public:
  ColorMap()
    : colors(),
      interpolation_type(InterpolationType::interpolation_linear) {}
  ColorMap(const std::vector<Color> &in_colors,
           const InterpolationType in_interpolation_type)
    : colors(in_colors),
      interpolation_type(in_interpolation_type) {}

  void addColor(Color &color) { colors.emplace_back(color); }
  unsigned int size() const { return colors.size(); }
  void fillRGB(const std::vector<int> &its,
               const int maxits,
               std::vector<int> &r,
               std::vector<int> &g,
               std::vector<int> &b) const;
//  unsigned int red(unsigned int its, unsigned int maxits) const;
//  unsigned int green(unsigned int its, unsigned int maxits) const;
//  unsigned int blue(unsigned int its, unsigned int maxits) const;

private:
  std::vector<Color> colors;
  InterpolationType interpolation_type;

  static double
  interpolate_linear(double a, double b, double t);

  static double
  interpolate_smoothstep(double a, double b, double t);
};


#endif
