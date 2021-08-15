#ifndef SNAKE_H
#define SNAKE_H
#include <queue>
#include "SnakeDatum.h"
#include "SnakeDirection.h"
#include "TextureSheet.cpp"

class Snake{
  int _a, _b;
  SquareBoxGrid * _sqg;
  std::queue<SnakeDatum*> _tree;
  SnakeDirection *std;
  Spritesheet* snakeAtomic = NULL;
  TextureSheet *bodyTexture = NULL;
  SDL_Rect bodySimple;

public:
  Snake(SquareBoxGrid *sqg, SDL_Renderer * renderer);
  ~Snake();

  void initSnakeDatum(int x, int y);
  void addSnakeDatumOnDirect();
  void shiftSnakeDirec(int *x, int *y);
  void removeLastSnakeDatum();
  bool renderSnake(SDL_Renderer * renderer);
  void processEvent(const SDL_Event *e);

  void _tertiarySnakeSelector(SnakeDirection next, SnakeDirection now);
  int _primarySnakeSelector(SnakeDirection now);

  SnakeDatum* getSnakePointer();

  void GameOver();
};

#endif
