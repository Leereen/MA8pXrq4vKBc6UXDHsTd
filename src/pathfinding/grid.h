#ifndef GRID_H
#define GRID_H

#include <forward_list>

#include "types.h"


class Grid
{

 private:
  const uint32_t _max_x;
  const uint32_t _max_y;
  const unsigned char* _grid;
  const bool _is_out_of_bounds(const Node&) const;
  const bool _is_traversable(const Node&) const;

 public:

  Grid(const uint32_t, const uint32_t, const unsigned char*);
  Grid(const Grid&);

  const uint32_t get_position(const Node&) const;
  const Node get_node(const uint32_t) const;
  const bool get_value(const uint32_t) const;
  const bool get_value(const Node&) const;

  const std::forward_list<uint32_t> get_valid_next_positions(const uint32_t) const;


#ifdef DEBUG_MACRO
#include <string>
  const std::string print() const;
#endif

};


#endif // GRID_H
