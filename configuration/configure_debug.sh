#!/bin/bash

echo "Invoking gfractal debug configuration from configure_debug.sh..."
GFRACTAL_SRC='../gfractal'

cmake \
-D CMAKE_BUILD_TYPE=Debug \
${GFRACTAL_SRC}
