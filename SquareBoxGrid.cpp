#ifndef SQUAREGRID_CPP
#define SQUAREGRID_CPP

#include "SquareBoxGrid.h"
#include "utils.cpp"
#include "ColorPalette.h"

Square::Square(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2){
  this->x1 = x1;
  this->y1 = y1;
  this->x2 = x2;
  this->y2 = y2;
}

SquareBoxGrid::SquareBoxGrid(int cwidth, int cheight, int boxSize){
  this->cwidth = cwidth;
  this->cheight = cheight;

  int x = utils::gcd(cwidth, cheight);
  if(x%boxSize!=0){
    printf("Error, Invalid unit box size setting it to %d\n", x);
    this->boxSize = x;
  }
  else{
    this->boxSize = boxSize;
  }

  _a = this->cwidth / this->boxSize;
  _b = this->cheight / this->boxSize;
}

void SquareBoxGrid::renderHelperRects(SDL_Renderer * renderer){
  Square *b;
  for(int ix=0;ix<_a;ix++){
    for(int iy=0;iy<_b;iy++){
      b = getBox(ix,iy);
      rectangleColor(renderer, b->x1, b->y1, b->x2, b->y2, ColorPalette::RED);
      delete b;
    }
  }
}

void SquareBoxGrid::getBoxDimen(int *a, int *b){
  *a = _a;
  *b = _b;
}

Square* SquareBoxGrid::getBox(int x, int y){
  if(x>_a || y>_b){
    printf("Invalid box, outside bounds\n");
    return NULL;
  }
  int x1 = x*boxSize;
  int y1 = y*boxSize;

  return new Square(x1, y1, x1+boxSize, y1+boxSize);
}

SquareBoxGrid::~SquareBoxGrid(){

}

#endif
