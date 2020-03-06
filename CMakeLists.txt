#######################
# GFractal CMake file #
#######################
# TODO: Figure out how to get the 
MESSAGE(STATUS "Setting up GFractal library :)")


# check CMake version; require 3.10 since Kokkos requires it
MESSAGE(STATUS "This is CMake ${CMAKE_VERSION}")
MESSAGE(STATUS "")
CMAKE_MINIMUM_REQUIRED(VERSION "3.10" FATAL_ERROR)


# lambdas and using are actually c++11, so we require at least c++11,
# therefore we just assume the c++11 standard
SET(CMAKE_CXX_STANDARD 11)
MESSAGE(STATUS "Setting c++ standard: c++11")


# look for Kokkos if the user gives a directory for it
# and then do an inline build for full customization
IF(DEFINED GFRACTAL_KOKKOS_DIR)
  MESSAGE(STATUS "Adding user-specified Kokkos directory: " ${GFRACTAL_KOKKOS_DIR})
  ADD_SUBDIRECTORY(${GFRACTAL_KOKKOS_DIR} Kokkos)
  INCLUDE_DIRECTORIES("${GFRACTAL_KOKKOS_DIR}")
  ADD_DEFINITIONS(-DGFRACTAL_WITH_KOKKOS)
  MESSAGE(STATUS "Found Kokkos! Enabling GFRACTAL_WITH_KOKKOS...")
ENDIF()


# setup the project and its flags based on build type
PROJECT("GFractal" CXX)
IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
  MESSAGE(STATUS "Setting the project to debug mode...")
  ADD_DEFINITIONS(-DGFRACTAL_DEBUG_MODE)
ELSEIF(CMAKE_BUILD_TYPE STREQUAL "Release")
  MESSAGE(STATUS "Setting the project to release mode...")
  ADD_DEFINITIONS(-DGFRACTAL_RELEASE_MODE)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
ELSE()
  MESSAGE(STATUS "No build type specified; setting the project to debug mode...")
  ADD_DEFINITIONS(-DGFRACTAL_DEBUG_MODE)
ENDIF()


# Set it up to include files in the intended fashion
INCLUDE_DIRECTORIES("include")


# Tell it where to look for the source code
ADD_SUBDIRECTORY("source")
SET_TARGET_PROPERTIES("${PROJECT_NAME}" PROPERTIES LINKER_LANGUAGE CXX)
MESSAGE(STATUS "Setting up GFractal library... done!")





# Old commands that I'm saving at the moment.

# May require c++14 because I will likely start using c++14 features in later updates.
# For now it will stay commented out.
#SET(CMAKE_CXX_STANDARD 14)
#SET(CMAKE_CXX_STANDARD_REQUIRED ON)
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

#ADD_LIBRARY(GFractal)
#INSTALL(DIRECTORY GFractal
#  DESTINATION "include"
#  COMPONENT library
#  FILES_MATCHING PATTERN "*.h"
#  )
#TARGET_LINK_LIBRARIES(GFractal 
#  source
#  )
#ADD_EXECUTABLE(gfractal )
