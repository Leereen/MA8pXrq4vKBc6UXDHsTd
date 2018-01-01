#ifndef DIJKSTRA_MANAGER_H
#define DIJKSTRA_MANAGER_H

#include <unordered_set>
#include <memory>

#include "path.h"
#include "../path_manager.h"

typedef std::unordered_set<Path> PathSet;


class DijkstraManager: PathManager
{
 private:

  const bool _evaluate_new_paths(PathSet&, const Path&);

 public:

  DijkstraManager(const uint32_t, const uint32_t, const uint32_t, const bool = true);
  const bool recc(const PathSet& current_paths, const uint32_t = 0);
  const bool register_solution(int *) const;
  const bool has_solution() const;
  const uint32_t solution_length() const;

};


#endif // DIJKSTRA_MANAGER_H
