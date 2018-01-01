#include "path_manager.h"


PathManager::PathManager(const uint32_t max, const Position start,
                         const Position end, const Grid& grid,
                         const bool early_break)
  : _max_size(max), _destination(end), _visited({start}), _shortest_path(nullptr),
    _grid(grid), _early_break(early_break)
{}


const bool PathManager::has_solution() const
{
  return not (_shortest_path == nullptr);
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
