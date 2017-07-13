#ifndef PATHFINDER_H
#define PATHFINDER_H

/*
  CONSTRAINTS, LIMITATIONS AND/OR IMPLEMENTATION DETAILS:

    - 1 <= nMapWidth, nMapHeight

    - 0 <= nStartX, nTargetX < nMapWidth

    - 0 <= nStartY, nTargetY < nMapHeight

    - both Start and Target are empty locations,

    - nOutBufferSize >= 0

    - as most containers used do not sort data, the program can provide
      different solution for array with multiple valid paths.
      (the provided solutions seem however stable on a given computer)
*/
int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char* pMap,
             const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize,
             const bool early_break = true);

#endif
