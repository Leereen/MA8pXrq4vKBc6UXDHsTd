#ifndef PATH_H
#define PATH_H

#include <deque>

#include "types.h"
#include "grid.h"


class Path;
template <> class std::hash<Path>;

class Path
{
  friend class std::hash<Path>;

 private:
  std::deque<uint32_t> _path;
  const Grid& _grid;

 public:
  Path(const Path&);
  Path(const Grid&, const uint32_t);

  const uint32_t front() const;
  const uint32_t back() const;
  const uint32_t size() const;

  const bool operator==(const Path&) const;
  const bool is_shorter(const Path&) const;
  const bool is_valid(const uint32_t) const;
  const std::forward_list<uint32_t> new_positions() const;

  const bool add_position(const uint32_t);
  const std::deque<uint32_t> get_indices() const;

#ifdef DEBUG_MACRO
#include <string>
  const std::string print() const;
#endif

};


template <> class std::hash<Path>
{
 public:
  size_t operator()(const Path& path) const
  {
    return std::hash<uint32_t>()(path.back());
  }
};


#endif // PATH_H
