#include "grid.h"
#include "types.h"
#include "path_manager.h"

#include <memory>
#include <list>

#include <iostream>


int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize)
{
  const Node start(nStartX, nStartY);
  const Node end(nTargetX, nTargetY);
  const Grid grid(nMapWidth, nMapHeight, pMap);

  PathManager manager (grid, nOutBufferSize, start, end);
  manager.recc();
  const bool result = manager.register_solution(pOutBuffer);
  if (result)
    {
      return manager.solution_length();
    }
  return -1;
}
