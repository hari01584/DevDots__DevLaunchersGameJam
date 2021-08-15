#ifndef UTILS_CPP
#define UTILS_CPP

#include <stdlib.h>
#include <string>
#include "SDL_Image.h"


using namespace std;

namespace utils{
  void replaceAll( string &s, const string &search, const string &replace ) {
    for( size_t pos = 0; ; pos += replace.length() ) {
        // Locate the substring to replace
        pos = s.find( search, pos );
        if( pos == string::npos ) break;
        // Replace by erasing and inserting
        s.erase( pos, search.length() );
        s.insert( pos, replace );
    }
}

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

  void alert(std::string message){
    std::string s1 = "alert(\"";
    std::string s3 = "\")";
    std::string sc = s1 + message + s3;
    replaceAll(sc, "\n", "\\n");
    replaceAll(sc, "'", "\'");

    emscripten_run_script(sc.c_str());
  }

  SDL_Surface* loadSurface(std::string path){
      SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
      if( loadedSurface == NULL )
      {
          printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
      }

      return loadedSurface;
  }
}

#endif
