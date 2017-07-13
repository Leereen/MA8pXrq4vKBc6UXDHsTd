#include "grid.h"
#include "types.h"
#include "path_manager.h"

#include <memory>
#include <list>

#include <iostream>


int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char* pMap,
             const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize,
             const bool early_break)
{
  const Grid grid(nMapWidth, nMapHeight, pMap);
  const uint32_t start = grid.get_position(Node(nStartX, nStartY));
  const uint32_t end = grid.get_position(Node(nTargetX, nTargetY));
  DEBUG_PRINT(grid.print());
  PathManager manager (grid, nOutBufferSize, start, end, early_break);
  if (not manager.recc() and early_break)
    {
      // - no final result found (manager.recc returned false)
      // - early_break required (no further research beyond limit reached)
      return -1;
    }
  // else manager.recc may be false but the early_break was not activated,
  // meaning if manager.recc was true, we can fill the nOutBufferSize firsts
  // node of the valid path in the pOutBuffer.
  const bool result = manager.register_solution(pOutBuffer);
  if (result)
    {
      return manager.solution_length();
    }
  return -1;
}
