#######################
# GFractal CMake file #
#######################
MESSAGE(STATUS "Setting up GFractal library :)")

MESSAGE(STATUS "This is CMake ${CMAKE_VERSION}")
MESSAGE(STATUS "")
CMAKE_MINIMUM_REQUIRED(VERSION "3.7.0")

PROJECT("GFractal" CXX)

# May require c++14 because I will likely start using c++14 features in later updates.
# For now it will stay commented out.
#SET(CMAKE_CXX_STANDARD 14)
#SET(CMAKE_CXX_STANDARD_REQUIRED ON)
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# Tell it where to look for the source code
ADD_SUBDIRECTORY("source")

SET_TARGET_PROPERTIES("${PROJECT_NAME}" PROPERTIES LINKER_LANGUAGE CXX)

MESSAGE(STATUS "Setting up GFractal library... done!")



# Old CMake commands that I'm saving at the moment.

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
