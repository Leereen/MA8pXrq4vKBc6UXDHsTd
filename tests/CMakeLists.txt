set(GTEST_PATH "${CMAKE_CURRENT_SOURCE_DIR}/gtest/googletest/")
set(GTEST_INCLUDE "${GTEST_PATH}/include")
set(GTEST_LIB gtest)

set(TEST_TARGET tests)

enable_testing()
add_subdirectory(${GTEST_PATH})
include_directories(${GTEST_INCLUDE})

set(TEST_FILES
  pathfinding/test_pathfinder.cpp
  # pathfinding/test_path.cpp
  # pathfinding/test_grid.cpp
  )

add_executable(${TEST_TARGET} main.cpp ${TEST_FILES})
get_property(pathfinding_libraries GLOBAL PROPERTY PATHFINDING_LIBRARIES)
add_dependencies(${TEST_TARGET} ${pathfinding_libraries})

set(CMAKE_STATIC_LINKER_FLAGS "-fprofile-instr-generate ${CMAKE_STATIC_LINKER_FLAGS}")
# setting link flags for this target
if (ASAN)
  set_target_properties(${TEST_TARGET} PROPERTIES
    LINK_FLAGS    "-fsanitize=address -fno-omit-frame-pointer -fno-common")
endif()

target_link_libraries(${TEST_TARGET} ${GTEST_LIB} ${pathfinding_libraries})

include(FindGTest)
if (${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} GREATER 3.8)
  cmake_policy(SET CMP0054 NEW)
  gtest_add_tests(TARGET ${TEST_TARGET})
else()
  gtest_add_tests(${TEST_TARGET} "" AUTO)
endif()
