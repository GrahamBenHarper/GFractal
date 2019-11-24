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

# Set it up to include files in the intended fashion
TARGET_INCLUDE_DIRECTORIES("${PROJECT_NAME}" PUBLIC ../../)
