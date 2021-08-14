#ifndef SNAKE_H
#define SNAKE_H
#include <queue>
#include "BeanObject.h"
#include "SnakeDatum.h"

class Snake{
  int _a, _b;
  SquareBoxGrid * _sqg;
  std::queue<SnakeDatum*> _tree;
  SnakeDirection *std;

public:
  Snake(SquareBoxGrid *sqg);
  ~Snake();

  void initSnakeDatum(int x, int y);
  void addSnakeDatumOnDirect();
  void shiftSnakeDirec(int *x, int *y);
  void removeLastSnakeDatum();
  void renderSnake(SDL_Renderer * renderer);
  void processEvent(const SDL_Event *e);
  void GameOver();
};

#endif
