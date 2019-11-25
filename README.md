# GFractal
A C++ library for computing simple fractals with no outside dependencies. 

## Features
  1. Export fractal images as `.bmp`
  2. Compute fractals for Julia sets and Newton iterations
  3. Color maps for fractal images

## Building the library
This project is configured with CMake to build a static library. To accomplish this, suppose you navigate to the project folder `GFractal`. From the terminal in the folder `GFractal`, enter the following commands

```Shell
cd ../
mkdir build
cd build
cmake ../GFractal/
make all
```

Supposing that configuring and compiling goes well, you should now be able to find `libGFractal.a` in the `build/source/` directory to use with your own projects.

## Linking the compiled library
Now suppose you'd like to write a file `main.cpp` which depends on this library. There are a couple ways to do this. The simplest way is to set up a bash script and tell it where to include headers from and where the library is. For example, the script might look like this:


```
#!/bin/bash

g++ -o main main.cpp -I ../../ -L ../../build/source -l GFractal
if [[ $? -ne 0 ]] ; then
  echo "Compilation failed! Aborting..."
  exit 1
fi

./main
```

This assumes that the folder containing GFractal is located at `../../`, and the build directory is `../../build`. Another way to do so is with CMake. To automate this with CMake, in the folder containing `main.cpp`, create a `CMakeLists.txt` containing the following

```
SET(TARGET "main")

# Build only main.cpp
SET(TARGET_SRC
  ${TARGET}.cpp
  )

# Give a path to the folder GFractal/
SET(PATH_TO_GFRACTAL
  ../../
)

CMAKE_MINIMUM_REQUIRED(VERSION 3.1.0)

PROJECT(${TARGET})

# Set the working directory to the GFractal/ directory so the headers and library can be found in a consistent fashion without changing the source code.
ADD_CUSTOM_TARGET(run
    COMMAND g++ -o ${TARGET} ${TARGET_SRC} -I ${PATH_TO_GFRACTAL} -L ${PATH_TO_GFRACTAL}/build/source -l GFractal
    COMMAND ./${TARGET}
)
```

where the `PATH_TO_GFRACTAL` variable should take you to a folder that contains the `GFractal/` folder. In this case, the folder containing `GFractal/` is two levels up. Then type `cmake .` in the command line, and then type `make run` in the command line, and everything should compile and run automatically.

## Questions?
Feel free to open an issue or a pull request if you have any questions or recommendations.
