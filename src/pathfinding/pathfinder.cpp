#include <memory>
#include <list>
#include <iostream>

#include "grid.h"
#include "types.h"
#include "path_manager.h"
#include "dijkstra/manager.h"
#include "A*/manager.h"

#include "pathfinding/pathfinder.h"


extern "C" int FindPath(const int nStartX, const int nStartY,
                        const int nTargetX, const int nTargetY,
                        const unsigned char* pMap,
                        const int nMapWidth, const int nMapHeight,
                        int* pOutBuffer, const int nOutBufferSize,
                        const bool early_break, const Algorithm algo)
{
  const Grid grid(nMapWidth, nMapHeight, pMap);
  const Position start = grid.get_position(nStartX, nStartY);
  const Position end = grid.get_position(nTargetX, nTargetY);
  DEBUG_PRINT("Early break:\t" + std::to_string(early_break));
  DEBUG_PRINT(grid.print());

  std::unique_ptr<PathManager> manager;
  if (algo == Algorithm::DIJKSTRA)
  {
    manager.reset(new DijkstraManager(nOutBufferSize, start, end, grid, early_break));
  }
  else if (Algorithm::DIJKSTRA < algo && algo <= Algorithm::ASTAR_MANHATTAN)
  {
    manager.reset(new AStarManager(nOutBufferSize, start, end, grid, early_break, algo));
  }
  else
  {
    DEBUG_PRINT("Invalid algorithm specified. Exiting.");
    return -1;
  }

  if (not manager->find() and early_break)
    {
      // - no final result found (manager->find returned false)
      // - early_break required (no further research beyond limit reached)
      DEBUG_PRINT("No solution was found... Early break.");
      return -1;
    }
  // else manager->find may be false but the early_break was not activated,
  // meaning if manager->find was true, we can fill the nOutBufferSize firsts
  // node of the valid path in the pOutBuffer.
  const bool result = manager->register_solution(pOutBuffer);
  if (result)
    {
      return manager->solution_length();
    }
  return -1;
}
