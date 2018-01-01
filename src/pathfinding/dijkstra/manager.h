#ifndef DIJKSTRA_MANAGER_H
#define DIJKSTRA_MANAGER_H

#include <unordered_set>
#include <memory>

#include "../path.h"
#include "../path_manager.h"


class DijkstraManager: public PathManager
{
 private:
  const bool _evaluate_new_paths(PathSet&, const Path&);
  const bool _find_rec(const PathSet& current_paths, const uint32_t = 0);


 public:
  DijkstraManager(const uint32_t, const Position, const Position, const Grid&, const bool = true);
  ~DijkstraManager();
  const bool find();
};


#endif // DIJKSTRA_MANAGER_H
