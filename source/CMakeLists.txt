#######################
# GFractal CMake file #
#######################

# Add the source files to the library
ADD_LIBRARY("${PROJECT_NAME}" STATIC
  complex_function.cpp
  color_map.cpp
  julia_fractal.cpp
  newton_fractal.cpp
  output_data.cpp
)
