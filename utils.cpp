#ifndef UTILS_CPP
#define UTILS_CPP

#include <stdlib.h>

namespace utils{
  int RandU(int nMin, int nMax)
  {
    int x = nMin + ( rand() % ( nMax - nMin + 1 ) );
    return x;
  }
}

#endif
