#ifndef PATH_MANAGER_H
#define PATH_MANAGER_H

#include <unordered_set>
#include <memory>

#include "dijkstra/path.h"


typedef std::unordered_set<Path> PathSet;


class PathManager
{
 protected:
  const uint32_t _max_size;
  const uint32_t _destination;
  std::shared_ptr<Path> _shortest_path;
  std::unordered_set<uint32_t> _visited;
  const bool _early_break;

 public:

  PathManager(const uint32_t, const uint32_t, const uint32_t, const bool = true);
  virtual const bool recc(const PathSet& current_paths, const uint32_t = 0) = 0;
  virtual const bool register_solution(int *) const = 0;
  virtual const bool has_solution() const = 0;
  virtual const uint32_t solution_length() const = 0;

};


#endif // PATH_MANAGER_H
