#ifndef PATHFINDER_H
#define PATHFINDER_H

/*
  CONSTRAINTS, LIMITATIONS AND/OR IMPLEMENTATION DETAILS:

    - 1 <= nMapWidth, nMapHeight

    - 0 <= nStartX, nTargetX < nMapWidth

    - 0 <= nStartY, nTargetY < nMapHeight

    - both Start and Target are empty locations,

    - nOutBufferSize >= 0

    - max table width or height is capped to 0xfffffffe, as indices are
      converted to uint32_t, and border control checks if a Node does not cross
      the uint32_t(-1) position.
*/
int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char* pMap,
             const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize);

#endif
