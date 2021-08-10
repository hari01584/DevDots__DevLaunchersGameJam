#ifndef StarShape_H
#define StarShape_H

class StarShape{
int x, y, innerVerticeRad, outerVerticeRad, angleRotation;
int _sides;
Sint16 _xs[10];
Sint16 _ys[10];
public:
  StarShape(int x, int y, int innerVerticeRad, int outerVerticeRad=-1, int angleRotation = 0, int np = 5);
  ~StarShape();

  void drawStars(SDL_Renderer * renderer);
  void buildStar();

};

#endif
