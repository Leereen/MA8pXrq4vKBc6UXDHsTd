#ifndef PATH_MANAGER_H
#define PATH_MANAGER_H

#include <unordered_set>
#include <memory>

#include "path.h"

// TODO: move in dijkstra?
typedef std::unordered_set<Path> PathSet;


class PathManager
{
 protected:
  const uint32_t _max_size;
  const uint32_t _destination;
  std::shared_ptr<Path> _shortest_path;
  std::unordered_set<uint32_t> _visited;
  const Grid& _grid;
  const bool _early_break;

 public:
  PathManager(const uint32_t, const Position, const Position, const Grid&, const bool = true);
  virtual ~PathManager() {};
  const bool register_solution(int *) const;
  const bool has_solution() const;
  const uint32_t solution_length() const;

  virtual const bool find() = 0;
};


#endif // PATH_MANAGER_H
