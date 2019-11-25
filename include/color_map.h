// ---------------------------------------------------------------------
// GFractal Project
// Graham Harper
// ---------------------------------------------------------------------

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

template <typename T>
class Color
{
public:

  /**
   * Default constructor. Initializes red, green, and blue to 0.
   */
  Color()
    : r(0),
      g(0),
      b(0) {}

  /**
   * Constructor for a color given red, green, and blue.
   * If any input is over 255, it is rounded down to 255.
   * @param red
   * @param green
   * @param blue
   */
  Color(const T red,
        const T green,
        const T blue)
    : r((red>255) ? 255 : red),
      g((green>255) ? 255 : green),
      b((blue>255) ? 255 : blue)
  {}

  /**
   * Getter for the color red.
   * @return
   */
  T red() const { return r; }

  /**
   * Getter for the color green.
   * @return
   */
  T green() const { return g; }

  /**
   * Getter for the color blue.
   * @return
   */
  T blue() const { return b; }


  /**
   * Add two colors. Anything that adds over 255 is rounded down.
   * @param rhs
   * @return
   */
  Color<T>& operator+=(const Color<T>& rhs)
  {
    r = (r+rhs.red()   < 255 ? r+rhs.red()   : 255);
    g = (g+rhs.green() < 255 ? g+rhs.green() : 255);
    b = (b+rhs.blue()  < 255 ? b+rhs.blue()  : 255);
    return *this;
  }

  /**
   * Add two colors componentwise.
   * @param lhs
   * @param rhs
   * @return
   */
  friend Color<T> operator+(Color<T> lhs,
                            const Color<T>& rhs)
  {
    lhs += rhs;
    return lhs;
  }

  /**
   * Multiply a color by a double.
   */
  friend Color<T> operator*(Color<T> lhs,
                            const double a)
  {
    lhs.r = (lhs.red()*a     < 255 ? lhs.red()*a : 255);
    lhs.g = (lhs.green()*a < 255 ? lhs.green()*a : 255);
    lhs.b = (lhs.blue()*a   < 255 ? lhs.blue()*a : 255);
    return lhs;
  }

  //std::ostream& operator<<(std::ostream& out);


private:
  /**
   * The value of red for this color.
   */
  unsigned int r;

  /**
   * The value of green for this color.
   */
  unsigned int g;

  /**
   * The value of blue for this color.
   */
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

template <typename T>
class ColorMap
{
public:
  /**
   * Default constructor. Uses a grayscale scheme and linear interpolation.
   */
  ColorMap()
    : colors({Color<T>(0,0,0), Color<T>(255,255,255)}),
      interpolation_type(InterpolationType::interpolation_linear) {}

  /**
   * Constructor given colors and interpolation type.
   * @param in_colors
   * @param in_interpolation_type
   */
  ColorMap(const std::vector<Color<T>> &in_colors,
           const InterpolationType in_interpolation_type)
    : colors(in_colors),
      interpolation_type(in_interpolation_type) {}

  /**
   * Add a color to the ColorMap.
   * @param color
   */
  void addColor(Color<T> &color) { colors.emplace_back(color); }

  /**
   * Returns the number of colors in the ColorMap.
   * @return
   */
  unsigned int size() const { return colors.size(); }

  /**
   * Given a list of iterations its and a maximum maxits, compute
   * colors r,g,b corresponding to the iterations.
   * @param its
   * @param maxits
   * @param r
   * @param g
   * @param b
   */
  void fillRGB(const std::vector<int> &its,
               const int maxits,
               std::vector<T> &r,
               std::vector<T> &g,
               std::vector<T> &b) const;
//  unsigned int red(unsigned int its, unsigned int maxits) const;
//  unsigned int green(unsigned int its, unsigned int maxits) const;
//  unsigned int blue(unsigned int its, unsigned int maxits) const;

private:
  /**
   * Stores the list of colors that define the ColorMap.
   */
  std::vector<Color<T>> colors;

  /**
   * Stores the location of each color in the map for interpolation purposes.
   * Each value should be between 0 and 1. (not yet implemented)
   */
  //std::vector<double> color_location;

  /**
   * Stores the interpolation type for the ColorMap.
   */
  InterpolationType interpolation_type;

  /**
   * Interpolate linearly on the interval [0,1].
   * @param a The height of the left endpoint.
   * @param b The height of the right endpoint.
   * @param t The position to interpolate at.
   * @return
   */
  static T
  interpolate_linear(T a, T b, T t);


  /**
   * Interpolate using the smoothstep on the interval [0,1].
   * @param a The height of the left endpoint.
   * @param b The height of the right endpoint.
   * @param t The position to interpolate at.
   * @return
   */
  static T
  interpolate_smoothstep(T a, T b, T t);
};

// Colors may be stored as unsigned ints or doubles.
// Doubles are easier for performing operations on colors.
// Unsigned ints are easier for outputting images.

template class Color<unsigned int>;
template class Color<double>;
template class ColorMap<unsigned int>;
template class ColorMap<double>;

#endif
