#ifndef BEANOBJECT_H
#define BEANOBJECT_H

#include "SDL.h"
#include <queue>
#include "SnakeDatum.h"
//
// enum class BType {
//   NORMAL,
//   GOLDEN,
// };

// class BeanCoords{
// public:
//     int x, y;
//     BType beanType;
//     BeanCoords(){}
//     BeanCoords(int a, int b, BType bt):x(a), y(b), beanType(bt){}
// };

class BeanObject{
  int _a, _b;
  Spritesheet *beanSheet;
  const SquareBoxGrid *_sqg;
  std::vector<BeanCoords> beans;
  float gBeansProbabilityPerc = 20;
  uint8_t MAX_NORMAL_BEANS_PLACED = 7;
//
public:
  BeanObject(SquareBoxGrid *_sqg);
  ~BeanObject();

//   void beansRender(SDL_Renderer *renderer);
//   void beansBuilderGetCollison();
//   void randomizeBeanPlacement();
};

#endif
