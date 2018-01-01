set(LIBRARY pathfinding)

add_library(${LIBRARY} SHARED
  pathfinding/pathfinder.cpp
  pathfinding/grid.cpp
  pathfinding/path_manager.cpp
  pathfinding/path.cpp
  pathfinding/dijkstra/manager.cpp
  pathfinding/A*/manager.cpp
  )

if (ASAN)
  MESSAGE(STATUS "${Yellow}[OPTION] ASAN compilation flags activated${Reset}")
  set_target_properties(${LIBRARY} PROPERTIES
    COMPILE_FLAGS "-fsanitize=address -fno-omit-frame-pointer -fno-common -fPIC -lasan")
endif()

if (GTEST)
  target_include_directories(${LIBRARY} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}) # CMAKE >= 2.8.11
endif()

add_in_list(PATHFINDING_LIBRARIES ${LIBRARY})
