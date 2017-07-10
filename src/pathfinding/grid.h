#ifndef GRID_H
#define GRID_H

#include "types.h"


class Grid
{

 private:
  const uint32_t _max_x;
  const uint32_t _max_y;
  const unsigned char* _grid;

 public:

  Grid(const uint32_t, const uint32_t, const unsigned char*);
  Grid(const Grid&);

  const bool is_out_of_bounds(const Node&) const;
  const bool is_traversable(const Node&) const;
  const uint32_t get_position(const Node&) const;

};


#endif // GRID_H
