#ifndef StarShape_H
#define StarShape_H
#include "utils.cpp"

class StarShape{
float x, y;
int innerVerticeRad, outerVerticeRad, angleRotation;
int _sides;
float velocity;
Sint16 _xs[10];
Sint16 _ys[10];
public:
  StarShape(int x, int y, int innerVerticeRad, float velocity, int outerVerticeRad=-1, int angleRotation = 0, int np = 5);
  ~StarShape();

  void drawStars(SDL_Renderer * renderer);
  void increaseAndBuild(float timeStep);
  void buildStar();

};

#endif
