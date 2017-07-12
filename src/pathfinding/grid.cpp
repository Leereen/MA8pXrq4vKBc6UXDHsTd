#include "grid.h"


Grid::Grid(const uint32_t x, const uint32_t y, const unsigned char* grid)
  // '-1' as indices starts at 0.
  : _max_x(x-1), _max_y(y-1), _grid(grid)
{}

Grid::Grid(const Grid& grid) : _max_x(grid._max_x), _max_y(grid._max_y), _grid(grid._grid)
{}

const bool Grid::is_out_of_bounds(const Node& node) const
{
  // Return a boolean expressing whether the node is out of gris bounds or not
  if ((node.first > _max_x) or (node.first == MAX_UINT32_T) or
      (node.second > _max_y) or (node.second == MAX_UINT32_T))
    {
      return true;
    }
  return false;
}


const bool Grid::is_traversable(const Node& node) const
{
  const uint32_t position = get_position(node);
  return (_grid[position] == 1);
}


const uint32_t Grid::get_position(const Node& node) const
{
  return node.first + (node.second * (_max_x+1));
}


#ifdef DEBUG_MACRO
const std::string Grid::print() const
{
  std::string array = "[ ";
  size_t i;
  const uint32_t width = _max_x + 1;
  const uint32_t total = width * (_max_y + 1);
  for (i = 0; i < total; i++)
    {
      if (i and not (i % (width))) {
        array += "\n  ";
      }
      array += std::to_string(_grid[i]) + " ";
    }
  array += "]";
  return array;
}
#endif
