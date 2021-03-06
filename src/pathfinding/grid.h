#ifndef GRID_H
#define GRID_H

#include <forward_list>
#include <pathfinding/pathfinder.h>
#include "types.h"


typedef std::pair<uint32_t, uint32_t> Node;


class Grid
{

 private:
  const uint32_t _max_x;
  const uint32_t _max_y;
  const unsigned char* _grid;
  const bool _is_out_of_bounds(const Node&) const;
  const bool _is_traversable(const Position) const;
  const std::pair<int32_t, int32_t> _diff(const Position, const Position) const;

 public:
  Grid(const uint32_t, const uint32_t, const unsigned char*);
  Grid(const Grid&);

  const Position get_position(const uint32_t, const uint32_t) const;
  const bool get_value(const Position) const;
  const Node get_node(const Position) const;
  const uint32_t distance(const Position, const Position, const Algorithm = Algorithm::ASTAR_MANHATTAN) const;

  const std::forward_list<Position> get_valid_next_positions(const Position) const;


#ifdef DEBUG_MACRO
#include <string>
  const std::string print() const;
#endif

};


#endif // GRID_H
