#include <gtest/gtest.h>
#include <cstring>

#include <pathfinding/pathfinder.h>
#include "dataset.h"


TEST(FindPath, dijkstra_easy1)
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


TEST(FindPath, astar_easy1)
{
  unsigned char pMap[] = {1, 1, 1, 1,
                          0, 1, 0, 1,
                          0, 1, 1, 1};
  int buffer[12];
  int expected[] = {1, 5, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1};
  const int result = FindPath(0, 0, 1, 2, pMap, 4, 3, buffer, 12,
                              true, Algorithm::ASTAR_MANHATTAN);
  ASSERT_EQ(result, 3);
  ASSERT_TRUE(0 == std::memcmp(buffer, expected, sizeof(buffer)));
}


TEST(FindPath, dijkstra_easy2)
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


TEST(FindPath, astar_easy2)
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
  const int result = FindPath(1, 1, 3, 5, pMap, 5, 6, buffer, size,
                              true, Algorithm::ASTAR_MANHATTAN);
  ASSERT_EQ(result, 8);
  ASSERT_TRUE(0 == std::memcmp(buffer, expected, size));
}


TEST(FindPath, dijkstra_fail1)
{
  unsigned char pMap[] = {0, 0, 1,
                          0, 1, 1,
                          1, 0, 1};
  int buffer[7];
  const int result = FindPath(2, 0, 0, 2, pMap, 3, 3, buffer, 7);
  ASSERT_EQ(result, -1);
}


TEST(FindPath, astar_fail1)
{
  unsigned char pMap[] = {0, 0, 1,
                          0, 1, 1,
                          1, 0, 1};
  int buffer[7];
  const int result = FindPath(2, 0, 0, 2, pMap, 3, 3, buffer, 7,
                              true, Algorithm::ASTAR_MANHATTAN);
  ASSERT_EQ(result, -1);
}


TEST(FindPath, dijkstra_a1_success)
{
  int buffer[test::a1_path_length];
  const int result = FindPath(test::a1_sx, test::a1_sy, test::a1_dx, test::a1_dy,
                              test::a1, test::a1_w, test::a1_h, buffer,
                              test::a1_path_length);
  ASSERT_EQ(result, test::a1_path_length);
  ASSERT_TRUE(0 == std::memcmp(buffer, test::a1_real, test::a1_path_length));
}


TEST(FindPath, astar_a1_success)
{
  int buffer[test::a1_path_length];
  const int result = FindPath(test::a1_sx, test::a1_sy, test::a1_dx, test::a1_dy,
                              test::a1, test::a1_w, test::a1_h, buffer,
                              test::a1_path_length,
                              true, Algorithm::ASTAR_MANHATTAN);
  ASSERT_EQ(result, test::a1_path_length);
  ASSERT_TRUE(0 == std::memcmp(buffer, test::a1_real, test::a1_path_length));
}


TEST(FindPath, dijkstra_a1_no_early_break_success)
{
  // expected behavior: input buffer size is only 20, so only the 20 first nodes
  // are saved, but the final path is calculated anyway (no _early_break), and
  // its length returned
  const int size = 20;
  int buffer[20];
  const int result = FindPath(test::a1_sx, test::a1_sy, test::a1_dx, test::a1_dy,
                              test::a1, test::a1_w, test::a1_h, buffer, size,
                              false); // _early_break deactivated
  ASSERT_EQ(result, test::a1_path_length);
  ASSERT_TRUE(0 == std::memcmp(buffer, test::a1_real, size));
}


TEST(FindPath, astar_a1_no_early_break_success)
{
  // expected behavior: input buffer size is only 20, so only the 20 first nodes
  // are saved, but the final path is calculated anyway (no _early_break), and
  // its length returned
  const int size = 20;
  int buffer[size];
  const int result = FindPath(test::a1_sx, test::a1_sy, test::a1_dx, test::a1_dy,
                              test::a1, test::a1_w, test::a1_h, buffer, size,
                              false, Algorithm::ASTAR_MANHATTAN); // _early_break deactivated
  ASSERT_EQ(result, test::a1_path_length);
  ASSERT_TRUE(0 == std::memcmp(buffer, test::a1_real, size));
}


TEST(FindPath, dijkstra_a1_early_break_fail)
{
  const int size = 20;
  int buffer[size];
  const int result = FindPath(test::a1_sx, test::a1_sy, test::a1_dx, test::a1_dy,
                              test::a1, test::a1_w, test::a1_h, buffer, size);
  ASSERT_EQ(result, -1);
  ASSERT_FALSE(0 == std::memcmp(buffer, test::a1_real, size));
}


TEST(FindPath, astar_astar_a1_early_break_fail)
{
  const int size = 20;
  int buffer[size];
  const int result = FindPath(test::a1_sx, test::a1_sy, test::a1_dx, test::a1_dy,
                              test::a1, test::a1_w, test::a1_h, buffer, size,
                              true, Algorithm::ASTAR_MANHATTAN);
  ASSERT_EQ(result, -1);
  ASSERT_FALSE(0 == std::memcmp(buffer, test::a1_real, size));
}


TEST(FindPath, dijkstra_a2_success)
{
  int buffer[test::a2_path_length];
  const int result = FindPath(test::a2_sx, test::a2_sy, test::a2_dx, test::a2_dy,
                              test::a2, test::a2_w, test::a2_h, buffer,
                              test::a2_path_length, false);
  ASSERT_EQ(result, test::a2_path_length);
  // deactivated as multi-solution array can make the program to provide several
  // different solutions
  // ASSERT_TRUE(0 == std::memcmp(buffer, test::a2_real, test::a2_path_length));
}


TEST(FindPath, astar_a2_success)
{
  int buffer[test::a2_path_length];
  const int result = FindPath(test::a2_sx, test::a2_sy, test::a2_dx, test::a2_dy,
                              test::a2, test::a2_w, test::a2_h, buffer,
                              test::a2_path_length, false,
                              Algorithm::ASTAR_MANHATTAN);
  ASSERT_EQ(result, test::a2_path_length);
  // deactivated as multi-solution array can make the program to provide several
  // different solutions
  // ASSERT_TRUE(0 == std::memcmp(buffer, test::a2_real, test::a2_path_length));
}


TEST(FindPath, dijkstra_a3_success)
{
  int buffer[test::a3_path_length];
  const int result = FindPath(test::a3_sx, test::a3_sy, test::a3_dx, test::a3_dy,
                              test::a3, test::a3_w, test::a3_h, buffer,
                              test::a3_path_length, false);
  ASSERT_EQ(result, test::a3_path_length);
  // deactivated as multi-solution array can make the program to provide several
  // different solutions
  // ASSERT_TRUE(0 == std::memcmp(buffer, test::a3_real, test::a3_path_length));
}


TEST(FindPath, astar_a3_success)
{
  int buffer[test::a3_path_length];
  const int result = FindPath(test::a3_sx, test::a3_sy, test::a3_dx, test::a3_dy,
                              test::a3, test::a3_w, test::a3_h, buffer,
                              test::a3_path_length, false,
                              Algorithm::ASTAR_MANHATTAN);
  ASSERT_EQ(result, test::a3_path_length);
  // deactivated as multi-solution array can make the program to provide several
  // different solutions
  // ASSERT_TRUE(0 == std::memcmp(buffer, test::a3_real, test::a3_path_length));
}


TEST(FindPath, dijkstra_a4_no_early_break_fail)
{
  int buffer[test::a4_path_length];
  const int result = FindPath(test::a4_sx-1, test::a4_sy+1, test::a4_dx, test::a4_dy,
                              test::a4, test::a4_w, test::a4_h, buffer,
                              test::a4_path_length, false);
  ASSERT_EQ(result, -1);
}


TEST(FindPath, astar_a4_no_early_break_fail)
{
  int buffer[test::a4_path_length];
  const int result = FindPath(test::a4_sx-1, test::a4_sy+1, test::a4_dx, test::a4_dy,
                              test::a4, test::a4_w, test::a4_h, buffer,
                              test::a4_path_length, false,
                              Algorithm::ASTAR_MANHATTAN);
  ASSERT_EQ(result, -1);
}


TEST(FindPath, dijkstra_a4_no_early_break_success)
{
  int buffer[test::a4_path_length];
  const int result = FindPath(test::a4_sx, test::a4_sy, test::a4_dx, test::a4_dy,
                              test::a4, test::a4_w, test::a4_h, buffer,
                              test::a4_path_length, false);
  ASSERT_EQ(result, test::a4_path_length);
}


TEST(FindPath, astar_a4_no_early_break_success)
{
  int buffer[test::a4_path_length];
  const int result = FindPath(test::a4_sx, test::a4_sy, test::a4_dx, test::a4_dy,
                              test::a4, test::a4_w, test::a4_h, buffer,
                              test::a4_path_length, false,
                              Algorithm::ASTAR_MANHATTAN);
  ASSERT_EQ(result, test::a4_path_length);
}
