// ---------------------------------------------------------------------
// GFractal Project
// Graham Harper
// ---------------------------------------------------------------------

#ifndef GFRACTAL_macros_h
#define GFRACTAL_macros_h

#include <iostream>
#include <vector>

#ifdef GFRACTAL_DEBUG_MODE
  #define Assert(cond) if(!(cond)) \
  { \
    std::cout << "Assert failed on line " << __LINE__ \
      << " of file " << __FILE__ << std::endl; \
    std::cout << "The violated condition is " \
      << #cond << std::endl; \
    std::cout << "Aborting..." << std::endl; \
    std::abort(); \
  }
#endif

// check if we're using Kokkos, which is defined by 
// the GFRACTAL_WITH_KOKKOS command
#ifdef GFRACTAL_WITH_KOKKOS
  #include "Kokkos_Core.hpp"
  using GFractalMatrix = Kokkos::View<int**,Kokkos::Serial>;
//  #define GFractal_for(ARG) parallel_for(N, KOKKOS_LAMBDA {ARG   })
//  #include "something"
#else
  using GFractalMatrix = std::vector<std::vector<int>>;
//  #define GFractal_for(ARG) for(ARG)
//  #include "nothing"
#endif





#endif
