ADD_LIBRARY("${PROJECT_NAME}" OBJECT
  complex_function.cpp
  color_map.cpp
  julia_fractal.cpp
  newton_fractal.cpp
  output_data.cpp
)

TARGET_INCLUDE_DIRECTORIES("${PROJECT_NAME}" PUBLIC ../../)
