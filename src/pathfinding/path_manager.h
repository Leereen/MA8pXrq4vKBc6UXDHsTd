#ifndef PATH_MANAGER_H
#define PATH_MANAGER_H

#include <unordered_set>
#include <memory>

#include "path.h"


typedef std::unordered_set<Path> PathSet;


class PathManager
{
 private:

  const uint32_t _max_size;
  const uint32_t _destination;
  std::unordered_set<uint32_t> _visited;
  std::shared_ptr<Path> _shortest_path;
  const bool _early_break;

  const bool _evaluate_new_paths(PathSet&, const Path&);

 public:

  PathManager(const uint32_t, const uint32_t, const uint32_t, const bool = true);
  const bool recc(const PathSet& current_paths, const uint32_t = 0);
  const bool register_solution(int *) const;
  const bool has_solution() const;
  const uint32_t solution_length() const;

};


#endif // PATH_MANAGER_H
