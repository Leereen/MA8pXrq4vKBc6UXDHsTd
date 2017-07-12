#include <gtest/gtest.h>
#include <cstring>

#include <pathfinding/pathfinder.h>
#include "dataset.h"


TEST(FindPath, easy1)
{
  unsigned char pMap[] = {1, 1, 1, 1,
                          0, 1, 0, 1,
                          0, 1, 1, 1};
  int buffer[12];
  int expected[] = {1, 5, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1};
  const int result = FindPath(0, 0, 1, 2, pMap, 4, 3, buffer, 12);
  ASSERT_EQ(result, 3);
  ASSERT_TRUE(0 == std::memcmp(buffer, expected, sizeof(buffer)));
}


TEST(FindPath, easy2)
{
  unsigned char pMap[] = {1, 1, 0, 1, 1,
                          0, 1, 0, 0, 0,
                          0, 1, 1, 0, 0,
                          0, 0, 1, 1, 1,
                          1, 1, 1, 0, 1,
                          1, 0, 0, 1, 1};
  const int size = 12;
  int buffer[size];
  int expected[] = {11, 12, 17, 18, 19, 24, 29, 28, -1, -1, -1, -1};
  const int result = FindPath(1, 1, 3, 5, pMap, 5, 6, buffer, size);
  ASSERT_EQ(result, 8);
  ASSERT_TRUE(0 == std::memcmp(buffer, expected, size));
}


TEST(FindPath, fail1)
{
  unsigned char pMap[] = {0, 0, 1, 0, 1, 1, 1, 0, 1};
  int buffer[7];
  const int result = FindPath(2, 0, 0, 2, pMap, 3, 3, buffer, 7);
  ASSERT_EQ(result, -1);
}


TEST(FindPath, a1_success)
{
  const int size = 20;
  int buffer[20];
  const int result = FindPath(test::a1_sx, test::a1_sy, test::a1_dx, test::a1_dy,
                              test::a1, test::a1_w, test::a1_h, buffer, size,
                              false); // _early_break deactivated
  ASSERT_EQ(result, sizeof(test::a1_real)/sizeof(int));
  ASSERT_TRUE(0 == std::memcmp(buffer, test::a1_expected, size));
}


TEST(FindPath, a1_fail)
{
  const int size = 20;
  int buffer[20];
  const int result = FindPath(test::a1_sx, test::a1_sy, test::a1_dx, test::a1_dy,
                              test::a1, test::a1_w, test::a1_h, buffer, size);
  ASSERT_EQ(result, -1);
  ASSERT_FALSE(0 == std::memcmp(buffer, test::a1_expected, size));
}
