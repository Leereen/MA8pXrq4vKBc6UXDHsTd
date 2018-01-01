#include <iostream>
#include "manager.h"


DijkstraManager::DijkstraManager(const uint32_t max, const Position start,
                                 const Position end, const Grid& grid,
                                 const bool early_break)
  : PathManager(max, start, end, grid, early_break)
{}


DijkstraManager::~DijkstraManager()
{}


const bool DijkstraManager::_evaluate_new_paths(PathSet& new_paths, const Path& entry_path)
{
  /*
    Given an entry path, we build and check every possible path from it.

    Return true if the final path is detected, else false.
   */
  for (const Position test_position : _grid.get_valid_next_positions(entry_path.back()))
    {
      // new positions no more evaluated against old paths, but against a pool
      // of already visited positions. If a paths get a new position already
      // visited, it means it is longer or at least as long as another (already)
      // registered path.
      if (_visited.count(test_position))
        {
          continue;
        }
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
      /*
        New path is evaluated against the current new_paths set in order to
        prevent repetition.
      */
      if (new_paths.count(*new_path))
        {
          continue;
        }
      _visited.insert(test_position);
      new_paths.insert(*new_path);
    }
  return false;
}


const bool DijkstraManager::_find_rec(const PathSet& current_paths, const uint32_t current_size)
{
  /*
    Each call of find builds all the possible paths of N positions (N being the
    number of find calls), generated and evaluated from the paths generated
    at N-1 rec call.
    As EVERY current path is used to generate new paths, the generated new_paths
    will contain every possible new paths. If new_paths is empty, it means there
    is no paths to _destination.
  */
  if (_early_break and current_size >= _max_size)
    {
      // _max_size (nOutBufferSize) reached. Aborting if _early_break activated
      return false;
    }
  PathSet new_paths;
  for (const Path& entry_path : current_paths)
    {
      if (_evaluate_new_paths(new_paths, entry_path))
        {
          return true;
        }
    }
  if (new_paths.size())
    {
      DEBUG_PRINT("Iteration: " + std::to_string(current_size) +
                  " (nb paths: " + std::to_string(new_paths.size())
                  + ")");
      return _find_rec(new_paths, current_size+1);
    }
  return false;
}


const bool DijkstraManager::find()
{
  // when called, _visited is still only populated with the start position
  // (see PathManager constructor)
  return _find_rec({Path(_grid, *_visited.begin())});
}
