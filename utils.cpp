#ifndef UTILS_CPP
#define UTILS_CPP

#include <stdlib.h>

namespace utils{
  int RandU(int nMin, int nMax)
  {
    int x = nMin + ( rand() % ( nMax - nMin + 1 ) );
    return x;
  }

  int RandE(int nMin, int nMax)
  {
    //int x = nMin + ( emscripten_random() % ( nMax - nMin + 1 ) );
    int x = emscripten_random() * (nMax - nMin);
    return x;
  }

  int gcd(int a, int b)
  {
      if (a == 0)
          return b;
      return gcd(b % a, a);
  }
}

#endif
