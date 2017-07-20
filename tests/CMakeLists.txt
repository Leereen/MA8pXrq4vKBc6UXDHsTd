set(GTEST_PATH "${CMAKE_CURRENT_SOURCE_DIR}/gtest/googletest/")
set(GTEST_INCLUDE "${GTEST_PATH}/include")
set(GTEST_LIB gtest)

enable_testing()
add_subdirectory(${GTEST_PATH})
include_directories(${GTEST_INCLUDE})

set(TEST_FILES
  pathfinding/test_pathfinder.cpp
  pathfinding/test_path.cpp
  pathfinding/test_grid.cpp
  )

add_executable(tests main.cpp ${TEST_FILES})
get_property(pathfinding_libraries GLOBAL PROPERTY PATHFINDING_LIBRARIES)
add_dependencies(tests ${pathfinding_libraries})
target_link_libraries(tests ${GTEST_LIB} ${pathfinding_libraries})
