#include <iostream>
#include <set>
#include "manager.h"



AStarManager::AStarManager(const uint32_t max, const Position start,
                           const Position end, const Grid& grid,
                           const bool early_break, const Algorithm algo)
  : PathManager(max, start, end, grid, early_break), algo(algo),
    _previous(), _distance_from_start({{start, 0}}), _start(start)
{}


AStarManager::~AStarManager()
{}


const uint32_t AStarManager::_distance_through_position(const Position current)
{
  return _distance_from_start[current] + _grid.distance(current, _destination);
}


const std::shared_ptr<Path> AStarManager::_build_path(const Position position)
{
  std::deque<Position> reverse_path({position});
  Position current = position;
  while (_previous.count(current) == 1)
    {
      current = _previous[current];
      reverse_path.push_back(current);
    }
  return std::shared_ptr<Path>(new Path(_grid, reverse_path.rbegin(), reverse_path.rend()));
}


const bool AStarManager::find()
{
  // TODO: clean this mess
  std::set<Position> positions({_start});

  while (!positions.empty())
    {
      Position current_position = *positions.begin();
      uint32_t min_distance = _distance_through_position(current_position);

      // TODO: custom 'positions' set compare function in order to sort at insert
      //       then only get first element, rather than calculating min each time
      // getting the next position of the (likely) shortest path
      for (auto it = positions.begin(); it != positions.end(); it++)
        {
          const uint32_t distance = _distance_through_position(*it);
          if (distance < min_distance)
            {
              min_distance = distance;
              current_position = *it;
            }
        }

      if (current_position == _destination)
        {
          // solution!
          _shortest_path = _build_path(current_position);
          DEBUG_PRINT("Solution found! >> " + _shortest_path->print());
          return true;
        }

      positions.erase(current_position);
      _visited.insert(current_position);

      for (const Position test_position : _grid.get_valid_next_positions(current_position))
        {
          if (_visited.count(test_position))
            {
              continue;
            }
          if (_early_break and _distance_from_start[current_position] >= _max_size)
            {
              // ignoring this position: path already max length and still not finished
              continue;
            }

          if (!positions.count(test_position))
            {
              positions.insert(test_position);
            }
          _previous[test_position] = current_position;
          _distance_from_start[test_position] = _distance_from_start[current_position] + 1;
        }
    }
  return false;
}
