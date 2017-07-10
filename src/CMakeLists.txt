set(LIBRARY pathfinding)

add_library(${LIBRARY}
  pathfinding/pathfinder.cpp
  pathfinding/path.cpp
  pathfinding/grid.cpp
  pathfinding/path_manager.cpp
  )

if (GTEST)
  target_include_directories(${LIBRARY} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}) # CMAKE >= 2.8.11
endif()

add_in_list(PATHFINDING_LIBRARIES ${LIBRARY})
