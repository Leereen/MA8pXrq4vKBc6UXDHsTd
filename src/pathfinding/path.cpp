#include <algorithm>
#include <iostream>

#include "path.h"


Path::Path(const Grid& grid, const Node& starting_node)
  : _path({starting_node}), _grid(grid)
{}


Path::Path(const Path& other) : _path(other._path), _grid(other._grid)
{}


const Node& Path::front() const
{
  // NB: _path can't be empty by construction
  return _path.front();
}


const Node& Path::back() const
{
  // NB: _path can't be empty by construction
  return _path.back();
}


const uint32_t Path::size() const
{
  return _path.size();
}


const bool Path::contains(const Node& new_node) const
{
  if (std::find(_path.begin(), _path.end(), new_node) != _path.end())
    {
      // this is not very efficient as a new element requires the whole _path to
      // be scrolled.
      // keeping a std::set of nodes would ease this, but would consume more
      // space.
      // TODO: maybe as an option?
      return true;
    }
  return false;
}


const bool Path::add_node(const Node& new_node)
{
  // Check if new_node is not in already in path, then insert it at back and
  // return true, else return false
  if (contains(new_node))
    {
      return false;
    }
  _path.push_back(new_node);
  return true;
}


const std::forward_list<Node> Path::new_nodes() const
{
  // Return every possible new nodes:
  //  - not out of bounds
  //  - not already in _path
  //  - not blocked on the grid
  const Node& current_node = _path.back();
  std::forward_list<Node> new_nodes;
  for (const Node potential_node : {
        Node(current_node.first + 1, current_node.second),
        Node(current_node.first - 1, current_node.second),
        Node(current_node.first, current_node.second + 1),
        Node(current_node.first, current_node.second - 1)
      })
    {
      if (_grid.is_out_of_bounds(potential_node) or
          contains(potential_node) or
          not _grid.is_traversable(potential_node))
        {
          // if node is out of bounds, or already exists in path, or is
          // unpassable, then don't bother testing path from it.
          continue;
        }
      new_nodes.push_front(potential_node);
    }
  return new_nodes;
}


const bool Path::is_same(const Path& other_path) const
{
  // Returns if same_path is the same as _path, i.e if both their starting node
  // and last node are the same.
  return ((front() == other_path.front()) and (back() == other_path.back()));
}


const bool Path::is_shorter(const Path& other_path) const
{
  return (size() < other_path.size());
}


const bool Path::is_valid(const Node& end_node) const
{
  return (back() == end_node);
}

# ifdef DEBUG_MACRO
const std::string Path::print() const
{
  std::string message("[ ");
  for (const Node& node : _path)
    {
      message += "(" + std::to_string(node.first) + ", " + \
        std::to_string(node.second) + ")[" + \
        std::to_string(_grid.get_position(node)) + "] ";
    }
  message += "]";
  return message;
}
#endif

const std::vector<int> Path::get_indices() const
{
  // _path keeps the starting node to trigger reccursivity
  // no longer needed in final solution
  std::vector<int> indices(size()-1);
  int i = 0;
  for (auto it = ++_path.begin(); it != _path.end(); it++)
    {
      indices[i] = _grid.get_position(*it);
      i++;
    }
  return indices;
}
