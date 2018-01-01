#include <algorithm>
#include <iostream>

#include "path.h"


Path::Path(const Path& other) : _path(other._path), _grid(other._grid)
{}


Path::Path(const Grid& grid, const Position starting_position)
  : _path({starting_position}), _grid(grid)
{}


const uint32_t Path::front() const
{
  // NB: _path can't be empty by construction
  return _path.front();
}


const uint32_t Path::back() const
{
  // NB: _path can't be empty by construction
  return _path.back();
}


const uint32_t Path::size() const
{
  return _path.size();
}


const bool Path::operator==(const Path& other) const
{
  return (back() == other.back() and front() == other.front());
}


const bool Path::add_position(const Position new_position)
{
  _path.push_back(new_position);
  return true;
}


const bool Path::is_shorter(const Path& other_path) const
{
  return (size() < other_path.size());
}


const bool Path::is_valid(const Position end_position) const
{
  return (back() == end_position);
}


# ifdef DEBUG_MACRO
const std::string Path::print() const
{
  std::string message("[ ");
  for (const Position position : _path)
    {
      const Node node = _grid.get_node(position);
      message += "(" + std::to_string(node.first) + ", " +
        std::to_string(node.second) + ")[" +
        std::to_string(position) + "] ";
    }
  message += "]";
  return message;
}
#endif


const std::deque<uint32_t> Path::get_indices() const
{
  return _path;
}
