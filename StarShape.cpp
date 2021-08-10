#ifndef StarShape_C
#define StarShape_C
#define radian2degree(a) (a * 57.295779513082)
#define degree2radian(a) (a * 0.017453292519)

#include "StarShape.h"
#include "SDL2_gfxPrimitives.h"

// Utility function, not part of StarShape class
void transform(int x, int y, int len, double angle, int *tx, int *ty){
  *tx = x + len * cos(degree2radian(angle));
  *ty = y + len * sin(degree2radian(angle));
}

StarShape::StarShape(int x, int y, int innerVerticeRad,float velocity, int outerVerticeRad, int angleRotation, int np){
  StarShape::x = x;
  StarShape::y = y;
  StarShape::innerVerticeRad = innerVerticeRad;
  StarShape::velocity = velocity;
  if(outerVerticeRad != -1) StarShape::outerVerticeRad = outerVerticeRad;
  else StarShape::outerVerticeRad = 3*innerVerticeRad;
  StarShape::_sides = np; // 5 Pointed default

  int _unitAngle = 360 / StarShape::_sides;
  StarShape::angleRotation = 2 * _unitAngle - 90;
  StarShape::angleRotation += angleRotation;

  StarShape::buildStar();
}

void StarShape::increaseAndBuild(float timeStep) {
  if(y>=480){
    velocity = utils::RandU(10,40);
    y=0;
  }

  y += timeStep*velocity;
  angleRotation += 1;
  buildStar();
}

void StarShape::buildStar() {
  int _unitAngle = 360 / StarShape::_sides; // 72 degrees

  int f = StarShape::angleRotation + 360;
  int in = StarShape::innerVerticeRad;
  int o = StarShape::outerVerticeRad;
  size_t size = 0;

  for(int a=StarShape::angleRotation; a<f; a+=_unitAngle){
    // Add outer point
    int tx, ty;
    transform(x, y, o, a, &tx, &ty);
    StarShape::_xs[size] = tx;
    StarShape::_ys[size++] = ty;

    // Add inner point
    transform(x, y, in, a + (_unitAngle/2), &tx, &ty);
    StarShape::_xs[size] = tx;
    StarShape::_ys[size++] = ty;
  }
}

void StarShape::drawStars(SDL_Renderer * renderer){
  filledPolygonColor(renderer, StarShape::_xs, StarShape::_ys, StarShape::_sides * 2, 0xFFFFFFFF);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

StarShape::~StarShape(){

}

#endif
