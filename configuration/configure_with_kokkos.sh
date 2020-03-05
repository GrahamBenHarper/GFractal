#!/bin/bash

echo "Invoking gfractal Kokkos release configuration from configure_with_kokkos.sh..."
GFRACTAL_SRC='../gfractal'
KOKKOS_DIR='../../Kokkos/kokkos-source'

cmake \
-D CMAKE_BUILD_TYPE=Release \
-D GFRACTAL_KOKKOS_DIR=${KOKKOS_DIR} \
${GFRACTAL_SRC}
