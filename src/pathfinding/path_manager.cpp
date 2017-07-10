#include "path_manager.h"

#include <iostream>


PathManager::PathManager(const Grid& grid, const uint32_t max,
                         const Node& start, const Node& end)
  : _grid(grid), _max_size(max), _destination(end),
    _paths({std::shared_ptr<Path>(new Path(grid, start))}),
    _shortest_path()
{}


const bool PathManager::_evaluate_new_paths(PathSet& new_paths, Path& entry_path)
{
  /*
    Given an entry path, we build and check every possible path from it.
   */
  for (const Node& test_node : entry_path.new_nodes())
    {
      std::shared_ptr<Path> new_path(new Path(entry_path));
      new_path->add_node(test_node);
      DEBUG_PRINT(new_path->print());
      if (test_node == _destination)
        {
          // first node is starting node used to trigger the reccursion.
          // not needed in final solution
          _shortest_path = new_path;
          return true;
        }
      bool is_valid = true;
      /*
        New paths are evaluated against old paths in order to prevent loops.
      */
      for (const std::shared_ptr<Path>& old_path: _paths)
        {
          if (new_path->is_same(*old_path) and not new_path->is_shorter(*old_path))
            {
              // the same path already exists in paths, and is equal or longer
              is_valid = false;
              break;
            }
        }
      if (is_valid)
        {
          new_paths.push_back(new_path);
        }
      else
        {
          new_path.reset();
        }
    }
  return false;
 }


void PathManager::recc(const uint32_t current_size)
{
  /*
    Each call of recc builds all the possible paths of N nodes (N being the
    number of recc calls), generated and evaluated from the paths generated
    at N-1 rec call.
    As EVERY old path is used to generate new paths, the generated new_paths
    will contain every possible new paths, with no need to copy old paths from
    _paths. If new_paths is empty, it means there is no paths to _destination.
  */
  std::list<std::shared_ptr<Path>> new_paths;
  for (std::shared_ptr<Path>& entry_path : _paths)
    {
      if (_evaluate_new_paths(new_paths, *entry_path))
        {
          return;
        }
    }
  _paths = new_paths;
  if (new_paths.size())
    {
      recc(current_size+1);
    }
}

const bool PathManager::has_solution() const
{
  if (_shortest_path)
    {
      return true;
    }
  return false;
}


const uint32_t PathManager::solution_length() const
{
  if (has_solution())
    {
      return (_shortest_path->size() - 1);
    }
  return 0;
}


const bool PathManager::register_solution(int* pOutBuffer) const
{
  if (not _shortest_path)
    {
      return false;
    }
  if (_shortest_path->size() > _max_size)
    {
      return false;
    }
  const std::vector<int> indices = _shortest_path->get_indices();
  for (int i = 0; i < _max_size; i++)
    {
      if (i < indices.size())
        {
          pOutBuffer[i] = indices[i];
        }
      else
        {
          pOutBuffer[i] = -1;
        }
    }
  return true;
}
