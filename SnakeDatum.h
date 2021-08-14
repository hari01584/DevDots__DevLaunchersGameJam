#ifndef SNAKEDATUM_H
#define SNAKEDATUM_H

#include "SnakeDirection.h"

struct SnakeDatum{
  uint16_t x, y;
  SnakeDirection direction;
  SnakeDatum(int x, int y, SnakeDirection direction){
    this->x=x;
    this->y=y;
    this->direction=direction;
  }
};

#endif
