#include <gtest/gtest.h>

#include "utils.h"
#include "dataset.h"


TEST_F(GridTest, get_node_get_position)
{
  const uint32_t position(RAND16);
  const Node node(position % x, position / x);
  const Node node2 = grid.get_node(position);
  const uint32_t position2 = grid.get_position(node);
  ASSERT_EQ(node, node2);
  ASSERT_EQ(position, position2);
}


TEST_F(GridTest, get_valid_next_positions)
{
  const Grid grid(test::a1_w, test::a1_h, test::a1);
  const uint32_t position(15);
  const std::forward_list<uint32_t> valids({27, 14, 16});
  const std::forward_list<uint32_t> empty ({});
  ASSERT_EQ(grid.get_valid_next_positions(position), valids);
  ASSERT_EQ(grid.get_valid_next_positions(109), empty);
}
