#ifndef ASTAR_MANAGER_H
#define ASTAR_MANAGER_H

#include <unordered_set>
#include <memory>
#include <map>

#include "../path.h"
#include "../path_manager.h"
#include "pathfinding/pathfinder.h"


class AStarManager: public PathManager
{
 private:

  const Algorithm algo;
  std::map<Position, Position> _previous;
  std::map<Position, uint32_t> _distance_from_start;
  const Position _start;
  const bool _evaluate_new_paths(PathSet&, const Path&);
  const std::shared_ptr<Path> _build_path(const Position);
  const uint32_t _distance_through_position(const Position);

 public:

  AStarManager(const uint32_t, const Position, const Position, const Grid&,
               const bool = true, const Algorithm = Algorithm::ASTAR_MANHATTAN);
  ~AStarManager();
  const bool find();
  const bool register_solution(int *) const;
  const bool has_solution() const;
  const uint32_t solution_length() const;

};


#endif // ASTAR_MANAGER_H
