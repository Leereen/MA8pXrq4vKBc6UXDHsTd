#include "grid.h"


#define WIDTH (_max_x + 1)


Grid::Grid(const uint32_t x, const uint32_t y, const unsigned char* grid)
  // '-1' as indices starts at 0.
  : _max_x(x-1), _max_y(y-1), _grid(grid)
{}


Grid::Grid(const Grid& grid) : _max_x(grid._max_x), _max_y(grid._max_y), _grid(grid._grid)
{}


const bool Grid::_is_out_of_bounds(const Node& node) const
{
  // Return a boolean expressing whether the node is out of gris bounds or not
  // 'var == MAX_UINT32_T' means 'uint32_t var = (0 - 1);'
  if ((node.first > _max_x) or (node.first == MAX_UINT32_T) or
      (node.second > _max_y) or (node.second == MAX_UINT32_T))
    {
      return true;
    }
  return false;
}


const bool Grid::_is_traversable(const Position position) const
{
  return (_grid[position] == 1);
}


const Node Grid::_get_node(const Position position) const
{
  return Node(position % WIDTH, position / WIDTH);
}


const Position Grid::get_position(const uint32_t x, const uint32_t y) const
{
  return x + (y * WIDTH);
}


const std::forward_list<Position> Grid::get_valid_next_positions(const Position position) const
{
  std::forward_list<Position> valid_positions;
  const Node node = _get_node(position);
  for (const Node& potential_node : {Node(node.first + 1, node.second),
                                     Node(node.first - 1, node.second),
                                     Node(node.first, node.second + 1),
                                     Node(node.first, node.second - 1)})
    {
      if (_is_out_of_bounds(potential_node) or
          not _is_traversable(get_position(potential_node.first, potential_node.second)))
        {
          continue;
        }
      valid_positions.push_front(get_position(potential_node.first, potential_node.second));
    }
  return valid_positions;
}


const bool Grid::get_value(const Position position) const
{
  return (bool)_grid[position];
}


#ifdef DEBUG_MACRO
const std::string Grid::print() const
{
  std::string array = "[ ";
  size_t i;
  const uint32_t width = WIDTH;
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
