#ifndef TYPES_H
#define TYPES_H

#include <utility>
#include <cstdint>

#define MAX_UINT32_T (0xffffffff)

#ifdef DEBUG_MACRO
#include <iostream>
#define DEBUG_PRINT(x) { std::cerr << x << std::endl; }
#else
#define DEBUG_PRINT(x) {}
#endif

typedef uint32_t Position;

#endif // TYPES_H
