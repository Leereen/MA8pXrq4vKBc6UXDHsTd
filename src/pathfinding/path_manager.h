#ifndef PATH_MANAGER_H
#define PATH_MANAGER_H

#include <unordered_set>
#include <memory>

#include "path.h"
#include "grid.h"


typedef std::unordered_set<Path> PathSet;


class PathManager
{
 private:

  const uint32_t _max_size;
  const Grid _grid;
  const uint32_t _destination;
  PathSet _paths;
  std::shared_ptr<Path> _shortest_path;
  const bool _early_break;

  const bool _evaluate_new_paths(PathSet&, const Path&);

 public:

  PathManager(const Grid&, const uint32_t, const uint32_t, const uint32_t, const bool = true);
  const bool recc(const uint32_t = 0);
  const bool register_solution(int *) const;
  const bool has_solution() const;
  const uint32_t solution_length() const;

};


#endif // PATH_MANAGER_H
