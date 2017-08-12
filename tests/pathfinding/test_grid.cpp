#include <gtest/gtest.h>

#include "utils.h"
#include "dataset.h"


TEST_F(GridTest, get_valid_next_positions)
{
  const Grid grid(test::a1_w, test::a1_h, test::a1);
  const uint32_t position(15);
  const std::forward_list<uint32_t> valids({27, 14, 16});
  const std::forward_list<uint32_t> empty;
  ASSERT_EQ(grid.get_valid_next_positions(position), valids);
  ASSERT_EQ(grid.get_valid_next_positions(109), empty);
}
