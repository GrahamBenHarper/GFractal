// ---------------------------------------------------------------------
// GFractal Project
// Graham Harper
// ---------------------------------------------------------------------
#include "gfractal/include/color_map.h"

template <typename T>
std::ostream& operator<<(std::ostream& out, const Color<T>& c)
{
   return out << "(" << c.red() << "," << c.green() << "," << c.blue() << ")" ;
}



template <typename T>
void
ColorMap<T>::fillRGB(const std::vector<int> &its,
                  const int maxits,
                  std::vector<T> &r,
                  std::vector<T> &g,
                  std::vector<T> &b) const
{
  int len = its.size();
  r.resize(len);
  g.resize(len);
  b.resize(len);

  // loop over pixels
  for(unsigned int ip=0; ip<len; ++ip)
  {
    // the two colors from the colormap to be used are colors(ic) and colors(ic+1)
    unsigned int ic;
    for(unsigned int i=0; i<size()-1; ++i)
      if( i*maxits <= its[ic]*size() && (i+1)*maxits >= its[ic]*size() )
        ic = i;

    // interpolate based on the location of its[ic] relative to where the colors change
    double interval_size = (double) maxits / (size()-1);
    double t = ((double) its[ic]-ic*interval_size) / interval_size;
    switch(interpolation_type)
    {
    case interpolation_linear:
      r[ip] = interpolate_linear(colors[ic].red(),  colors[ic+1].red(),  t);
      g[ip] = interpolate_linear(colors[ic].green(),colors[ic+1].green(),t);
      b[ip] = interpolate_linear(colors[ic].blue(), colors[ic+1].blue(), t);
      break;
    case interpolation_smoothstep:
      r[ip] = interpolate_smoothstep(colors[ic].red(),  colors[ic+1].red(),  t);
      g[ip] = interpolate_smoothstep(colors[ic].green(),colors[ic+1].green(),t);
      b[ip] = interpolate_smoothstep(colors[ic].blue(), colors[ic+1].blue(), t);
    }

  }
  return;
}



template <typename T>
T
ColorMap<T>::interpolate_linear(T a, T b, T t)
{
  return (a + (b-a)*t);
}



template <typename T>
T
ColorMap<T>::interpolate_smoothstep(T a, T b, T t)
{
  return (a + (b-a)*(6.*t*t*t*t*t - 15.*t*t*t*t + 10.*t*t*t));
}
