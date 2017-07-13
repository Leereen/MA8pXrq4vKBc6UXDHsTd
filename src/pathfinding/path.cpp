#include <algorithm>
#include <iostream>

#include "path.h"


Path::Path(const Grid& grid): _path(), _grid(grid)
{}


Path::Path(const Path& other) : _path(other._path), _grid(other._grid)
{}


Path::Path(const Grid& grid, const uint32_t starting_position)
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


const bool Path::contains(const uint32_t new_position) const
{
  if (std::find(_path.begin(), _path.end(), new_position) != _path.end())
    {
      // this is not very efficient as a new element requires the whole _path to
      // be scrolled.
      // keeping a std::set of positions would ease this, but would consume more
      // space.
      // TODO: maybe as an option?
      return true;
    }
  return false;
}


const bool Path::add_position(const uint32_t new_position)
{
  // Check if new_position is not in already in path, then insert it at back and
  // return true, else return false
  if (contains(new_position))
    {
      return false;
    }
  _path.push_back(new_position);
  return true;
}


const std::forward_list<uint32_t> Path::new_positions() const
{
  // Return every possible new positions:
  //  - not out of bounds
  //  - not already in _path
  //  - not blocked on the grid
  const uint32_t current_position = _path.back();
  std::forward_list<uint32_t> new_positions;
  for (const uint32_t potential_position : _grid.get_valid_next_positions(current_position))
    {
      if (contains(potential_position))
        {
          continue;
        }
      new_positions.push_front(potential_position);
    }
  return new_positions;
}


const bool Path::is_shorter(const Path& other_path) const
{
  return (size() < other_path.size());
}


const bool Path::is_valid(const uint32_t end_position) const
{
  return (back() == end_position);
}

# ifdef DEBUG_MACRO
const std::string Path::print() const
{
  std::string message("[ ");
  for (const uint32_t position : _path)
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
