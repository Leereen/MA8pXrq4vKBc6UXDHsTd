#ifndef PATH_MANAGER_H
#define PATH_MANAGER_H

#include <list>
#include <memory>

#include "path.h"
#include "grid.h"


typedef std::list<std::shared_ptr<Path>> PathSet;


class PathManager
{
 private:

  const uint32_t _max_size;
  const Grid _grid;
  const Node& _destination;
  PathSet _paths;
  std::shared_ptr<Path> _shortest_path;

  const bool _evaluate_new_paths(PathSet&, Path&);

 public:

  PathManager(const Grid&, const uint32_t, const Node&, const Node&);
  void recc(const uint32_t = 0);
  const bool register_solution(int *) const;
  const bool has_solution() const;
  const uint32_t solution_length() const;

};


#endif // PATH_MANAGER_H
