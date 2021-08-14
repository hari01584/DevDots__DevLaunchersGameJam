#ifndef SNAKEBOXGRID_H
#define SNAKEBOXGRID_H

#include "SDL.h"

struct Square{
public:
  uint16_t x1, y1, x2, y2;
  Square(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
};

class SquareBoxGrid{
  int cwidth, cheight, boxSize;
  int _a, _b;
public:
  SquareBoxGrid(int cwidth, int cheight, int boxSize);
  void renderHelperRects(SDL_Renderer * renderer);
  void getBoxDimen(int *a, int *b) const;

  Square* getBox(int x, int y);
  ~SquareBoxGrid();

  void renderBox(SDL_Renderer * renderer);
};


#endif
