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
  template <typename Iterator> Path(const Grid& grid, Iterator start, Iterator end)
    : _grid(grid)
    {
      for (auto it = start; it != end; it++)
        {
          _path.push_back(*it);
        }
    };
  Path(const Grid&, const Position);

  const Position front() const;
  const Position back() const;
  const Position size() const;

  const bool operator==(const Path&) const;
  const bool is_shorter(const Path&) const;
  const bool is_valid(const uint32_t) const;

  const bool add_position(const Position);
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
    return std::hash<Position>()(path.back());
  }
};


#endif // PATH_H
