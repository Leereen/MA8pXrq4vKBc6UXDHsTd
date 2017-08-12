#include "grid.h"
#include "types.h"
#include "path_manager.h"

#include <memory>
#include <list>

#include <iostream>


extern "C" int FindPath(const int nStartX, const int nStartY,
                        const int nTargetX, const int nTargetY,
                        const unsigned char* pMap,
                        const int nMapWidth, const int nMapHeight,
                        int* pOutBuffer, const int nOutBufferSize,
                        const bool early_break)
{
  const Grid grid(nMapWidth, nMapHeight, pMap);
  const uint32_t start = grid.get_position(nStartX, nStartY);
  const uint32_t end = grid.get_position(nTargetX, nTargetY);
  DEBUG_PRINT("Early break:\t" + std::to_string(early_break));
  DEBUG_PRINT(grid.print());
  PathManager manager (nOutBufferSize, start, end, early_break);
  if (not manager.recc({Path(grid, start)}) and early_break)
    {
      // - no final result found (manager.recc returned false)
      // - early_break required (no further research beyond limit reached)
      DEBUG_PRINT("No solution was found... Early break.");
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
