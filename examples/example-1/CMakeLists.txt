SET(TARGET "example-1")

# Build only main.cpp
SET(TARGET_SRC
  ${TARGET}.cpp
  )

# Give a path to the folder GFractal/
SET(PATH_TO_GFRACTAL
  ../../../
)

CMAKE_MINIMUM_REQUIRED(VERSION 3.1.0)

PROJECT(${TARGET})

# Set the working directory to the GFractal/ directory so the headers and library can be found in a consistent fashion without changing the source code.
ADD_CUSTOM_TARGET(run
    COMMAND g++ -o ${TARGET} ${TARGET_SRC} -I ${PATH_TO_GFRACTAL} -L ${PATH_TO_GFRACTAL}/build/source -l GFractal
    COMMAND ./${TARGET}
)
