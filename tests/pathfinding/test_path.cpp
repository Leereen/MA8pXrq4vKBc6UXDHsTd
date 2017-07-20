#include <gtest/gtest.h>
#include <cstdlib>

#include "utils.h"
#include "dataset.h"


TEST_F(PathTest, instanciation)
{
  ASSERT_EQ(path.front(), path.back());
  ASSERT_EQ(path.front(), start);
  ASSERT_EQ(path.size(), 1);
}


TEST_F(PathTest, copy)
{
  const uint32_t next = rand();
  path.add_position(next);
  ASSERT_EQ(path.front(), start);
  ASSERT_EQ(path.back(), next);
  const Path new_path(path);
  ASSERT_EQ(path.front(), new_path.front());
  ASSERT_EQ(path.back(), new_path.back());
}


TEST_F(PathTest, size)
{
  ASSERT_EQ(path.size(), 1);
  const uint32_t new_size = RAND16;
  for (uint32_t i=1; i<new_size; i++)
    {
      path.add_position(rand());
    }
  ASSERT_EQ(path.size(), new_size);
}


TEST_F(PathTest, equal)
{
  Path new_path(path);
  uint32_t it = RAND12;
  ASSERT_EQ(path, new_path);
  // generating 'random' paths, will be different at the end
  while (it--)
    {
      path.add_position(rand());
      if (it%2)
        {
          new_path.add_position(rand());
        }
    }
  ASSERT_FALSE(path == new_path);
  const uint32_t final = rand();
  path.add_position(final);
  new_path.add_position(final);
  ASSERT_EQ(path, new_path);
  ASSERT_TRUE(path == new_path);
}


TEST_F(PathTest, new_positions)
{
  const uint32_t position = rand() % (test::a3_h * test::a3_w - 1);
  const Grid lgrid(test::a3_w, test::a3_h, test::a3);
  Path lpath(lgrid, position);
  ASSERT_EQ(lpath.back(), position);
  ASSERT_EQ(lpath.new_positions(), lgrid.get_valid_next_positions(position));
}


TEST_F(PathTest, is_shorter)
{
  ASSERT_FALSE(path.is_shorter(path));
  Path lpath(path);
  ASSERT_FALSE(path.is_shorter(lpath));
  lpath.add_position(RAND16);
  ASSERT_FALSE(lpath.is_shorter(path));
  ASSERT_TRUE(path.is_shorter(lpath));
}


TEST_F(PathTest, is_valid)
{
  ASSERT_TRUE(path.is_valid(path.back()));
  const uint32_t a = RAND16;
  const uint32_t b = a + 1;
  path.add_position(a);
  ASSERT_TRUE(path.is_valid(a));
  ASSERT_FALSE(path.is_valid(b));
}

TEST_F(PathTest, get_indices)
{
  std::deque<uint32_t> lpath = {path.back()};
  uint32_t it = RAND12;
  while (it--)
    {
      const uint32_t position = rand();
      path.add_position(position);
      lpath.push_back(position);
    }
  ASSERT_EQ(path.get_indices(), lpath);
}
