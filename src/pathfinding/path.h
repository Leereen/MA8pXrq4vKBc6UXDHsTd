#ifndef PATH_H
#define PATH_H

#include <deque>
#include <forward_list>
#include <vector>

#include "types.h"
#include "grid.h"


class Path
{

 private:
  std::deque<Node> _path;
  const Grid& _grid;

 public:
  Path(const Grid&, const Node&);
  Path(const Path&);

  const Node& front() const;
  const Node& back() const;
  const uint32_t size() const;

  const bool is_same(const Path&) const;
  const bool is_shorter(const Path&) const;
  const bool is_valid(const Node&) const;
  const bool contains(const Node&) const;
  const std::forward_list<Node> new_nodes() const;

  const bool add_node(const Node&);

#ifdef DEBUG_MACRO
#include <string>
  const std::string print() const;
#endif
  const std::vector<int> get_indices() const;

};

#endif // PATH_H
