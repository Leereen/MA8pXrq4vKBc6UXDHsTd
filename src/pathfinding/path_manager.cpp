#include "path_manager.h"

#include <iostream>


PathManager::PathManager(const Grid& grid, const uint32_t max,
                         const uint32_t start, const uint32_t end,
                         const bool early_break)
  : _grid(grid), _max_size(max), _destination(end),
    _paths({Path(grid, start)}),
    _shortest_path(), _early_break(early_break)
{}


const bool PathManager::_evaluate_new_paths(PathSet& new_paths, const Path& entry_path)
{
  /*
    Given an entry path, we build and check every possible path from it.

    Return true if the final path is detected, else false.
   */
  for (const uint32_t test_position : entry_path.new_positions())
    {
      std::shared_ptr<Path> new_path(new Path(entry_path));
      new_path->add_position(test_position);
      DEBUG_PRINT(new_path->print());
      if (test_position == _destination)
        {
          // solution!
          DEBUG_PRINT("Solution found! >> " + new_path->print());
          _shortest_path = new_path;
          return true;
        }
      bool is_valid = true;
      /*
        New path is evaluated against the current new_paths set in order to
        prevent repetition.
      */
      if (new_paths.count(*new_path))
        {
          continue;
        }
      /*
        New path is evaluated against old paths in order to prevent loops.
      */
      for (const Path& old_path: _paths)
        {
          if (old_path == (*new_path) and not new_path->is_shorter(old_path))
            {
              // the same path already exists in paths, and is equal or longer
              is_valid = false;
              break;
            }
        }
      if (is_valid)
        {
          new_paths.insert(*new_path);
        }
    }
  return false;
}


const bool PathManager::recc(const uint32_t current_size)
{
  /*
    Each call of recc builds all the possible paths of N positions (N being the
    number of recc calls), generated and evaluated from the paths generated
    at N-1 rec call.
    As EVERY old path is used to generate new paths, the generated new_paths
    will contain every possible new paths, with no need to copy old paths from
    _paths. If new_paths is empty, it means there is no paths to _destination.
  */
  if (current_size == _max_size and _early_break)
    {
      // _max_size (nOutBufferSize) reached. Aborting if _early_break activated
      return false;
    }
  PathSet new_paths;
  for (const Path& entry_path : _paths)
    {
      if (_evaluate_new_paths(new_paths, entry_path))
        {
          return true;
        }
    }
  _paths = new_paths;
  if (new_paths.size())
    {
      DEBUG_PRINT("Iteration: " + std::to_string(current_size) +
                  " (nb paths: " + std::to_string(new_paths.size())
                  + ")");
      return recc(current_size+1);
    }
  return false;
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
  const std::deque<uint32_t> indices = _shortest_path->get_indices();
  for (int i = 0; i < _max_size; i++)
    {
      // path.get_indices() returns the complete path, WITH the starting node
      // which shall not be registered.
      if ((i+1) < indices.size())
        {
          pOutBuffer[i] = (int)indices[i+1];
        }
      else
        {
          pOutBuffer[i] = -1;
        }
    }
  return true;
}
