cmake_minimum_required(VERSION 3.5.0)
project(pathfinding CXX)

# constants
if(NOT WIN32)
  string(ASCII 27 Esc)
  set(Reset       "${Esc}[m")
  set(Red         "${Esc}[31m")
  set(Green       "${Esc}[32m")
  set(Yellow      "${Esc}[33m")
  set(Blue        "${Esc}[34m")
  set(Magenta     "${Esc}[35m")
  set(Cyan        "${Esc}[36m")
  set(White       "${Esc}[37m")
  set(Bold        "${Esc}[1m")
endif()

# pathfinding constants
set(pathfinding_VERSION_MAJOR 0)
set(pathfinding_VERSION_MINOR 1)
set(pathfinding_VERSION_PATCH 0)
set(pathfinding_VERSION ${pathfinding_VERSION_MAJOR}.${pathfinding_VERSION_MINOR}.${pathfinding_VERSION_PATCH})
set(PATHFINDING_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")

# pathfinding variables & functions
define_property(GLOBAL PROPERTY PATHFINDING_LIBRARIES
  BRIEF_DOCS "List of pathfinding libraries"
  FULL_DOCS "List of pathfinding libraries"
  )
set_property(GLOBAL PROPERTY PATHFINDING_LIBRARIES "")
function (add_in_list list value_or_list)
  set_property(GLOBAL APPEND PROPERTY ${list} ${value_or_list})
endfunction(add_in_list)


# compilation options
set(CMAKE_CXX_STANDARD 11)

option(ASAN OFF)
option(GTEST OFF) # TODO: add 'friend' declarations in order to test inner functions?
option(DEBUG_MODE OFF)

# includes
include_directories(${PATHFINDING_INCLUDE})

if (DEBUG_MODE)
  MESSAGE(STATUS "${Yellow}[OPTION] DEBUG mode activated${Reset}")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG_MACRO=1")
endif()

# project sources
add_subdirectory(src)

# testing
if (GTEST)
  MESSAGE(STATUS "${Yellow}[OPTION] GTESTING compilation activated${Reset}")
  add_subdirectory(tests)
endif()

# end
MESSAGE(STATUS "${Green}Preparing compilation for pathfinding version ${Bold}${pathfinding_VERSION}${Reset}")
