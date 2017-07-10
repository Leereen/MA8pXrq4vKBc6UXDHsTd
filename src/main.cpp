#include <iostream>
#include <pathfinding/pathfinder.h>


int main()
{
  // unsigned char pMap[] = {1, 1, 1, 1,
  //                         0, 1, 0, 1,
  //                         0, 1, 1, 1};
  unsigned char pMap[] = {1, 1, 0, 1, 1,
                          0, 1, 0, 0, 0,
                          0, 1, 1, 0, 0,
                          0, 0, 1, 1, 1,
                          1, 1, 1, 0, 1,
                          1, 0, 0, 1, 1};
  int pOutBuffer[12];
  std::cout << "Starting path finding..." << std::endl;
  // FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, 12);
  FindPath(1, 1, 3, 5, pMap, 5, 6, pOutBuffer, 12);
  std::cout << "Ended." << std::endl;
  return true;
}
