#!/bin/bash

echo "Invoking gfractal release configuration from configure_release.sh..."
GFRACTAL_SRC='../gfractal'

cmake \
-D CMAKE_BUILD_TYPE=Release \
${GFRACTAL_SRC}
