#ifndef TESTS_UTILS_H
#define TESTS_UTILS_H

#include "pathfinding/dijkstra/path.h"
#include "pathfinding/grid.h"


#define RAND16 (rand() % (2^16-1))
#define RAND12 (rand() % (2^12-1))
#define RAND8  (rand() % (2^8-1))


class PathTest: public ::testing::Test
{
 public:
  const uint32_t x;
  const uint32_t y;
  const uint32_t start;
  const Grid grid;
  Path path;

  PathTest()
    : x(RAND16), y(RAND16), start(RAND16), grid(x, y, nullptr), path(grid, start)
    {}

};


class GridTest: public ::testing::Test
{

 public:
  const uint32_t x;
  const uint32_t y;
  const unsigned char* array;
  Grid grid;

  GridTest()
    : x(RAND16), y(RAND16), array(nullptr), grid(x, y, array)
    {}

};


#endif // TESTS_UTILS_H
