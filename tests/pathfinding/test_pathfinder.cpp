#include <gtest/gtest.h>
#include <cstring>

#include <pathfinding/pathfinder.h>


TEST(FindPath, easy1)
{
  unsigned char pMap[] = {1, 1, 1, 1,
                          0, 1, 0, 1,
                          0, 1, 1, 1};
  int pOutBuffer[12];
  int expected[] = {1, 5, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1};
  const int result = FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, 12);
  ASSERT_EQ(result, 3);
  ASSERT_TRUE(0 == std::memcmp(pOutBuffer, expected, sizeof(pOutBuffer)));
}


TEST(FindPath, easy2)
{
  unsigned char pMap[] = {1, 1, 0, 1, 1,
                          0, 1, 0, 0, 0,
                          0, 1, 1, 0, 0,
                          0, 0, 1, 1, 1,
                          1, 1, 1, 0, 1,
                          1, 0, 0, 1, 1};
  int pOutBuffer[12];
  int expected[] = {11, 12, 17, 18, 19, 24, 29, 28, -1, -1, -1, -1};
  const int result = FindPath(1, 1, 3, 5, pMap, 5, 6, pOutBuffer, 12);
  ASSERT_EQ(result, 8);
  ASSERT_TRUE(0 == std::memcmp(pOutBuffer, expected, sizeof(pOutBuffer)));
}


TEST(FindPath, fail1)
{
  unsigned char pMap[] = {0, 0, 1, 0, 1, 1, 1, 0, 1};
  int pOutBuffer[7];
  const int result = FindPath(2, 0, 0, 2, pMap, 3, 3, pOutBuffer, 7);
  ASSERT_EQ(result, -1);
}
