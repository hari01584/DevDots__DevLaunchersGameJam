#ifndef SNAKE_CPP
#define SNAKE_CPP
#include "Snake.h"
#include "SnakeDatum.h"
#include "SquareBoxGrid.h"
#include "utils.cpp"
#include "ColorPalette.h"
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"

void Snake::initSnakeDatum(int x, int y){
  std = new SnakeDirection(SnakeDirection::RIGHT);
  _tree.push(new SnakeDatum(x, y, *std));
}

void Snake::shiftSnakeDirec(int *x, int *y){
  if(*std==SnakeDirection::RIGHT){
    if(*x>=_a-1) *x=0;
    else *x += 1;
  }
  else if(*std==SnakeDirection::LEFT){
    if(*x<=0) *x=_a-1;
    else *x -= 1;
  }
  else if(*std==SnakeDirection::UP){
    if(*y<=0) *y=_b-1;
    else *y -= 1;
  }
  else if(*std==SnakeDirection::DOWN){
    if(*y>=_b-1) *y=0;
    else *y += 1;
  }
}

SnakeDatum* Snake::getSnakePointer(){
  return _tree.back();
}

void Snake::GameOver(){
  printf("Game over mf\n");
}

void Snake::addSnakeDatumOnDirect(){
  SnakeDatum *_head = _tree.back();
  int ix = _head->x;
  int iy = _head->y;
  shiftSnakeDirec(&ix, &iy);
  //delete _head;

  _tree.push(new SnakeDatum(ix, iy, *std));
  // this->removeLastSnakeDatum();
}

void Snake::removeLastSnakeDatum(){
  delete _tree.front();
  _tree.pop();
}

Snake::Snake(SquareBoxGrid *sqg){
  this->_sqg = sqg;

  int sx, sy;
  sqg->getBoxDimen(&sx, &sy);
  _a = sx;
  _b = sy;
  initSnakeDatum(sx/2, sy/2);

  snakeAtomic = new Spritesheet(IMAGE_SNAKE_BODY_ATOMIC, 1, 1);
  snakeAtomic->select_sprite(0, 0);
}

Snake::~Snake(){
  while (!_tree.empty()) {
      SnakeDatum* temp = _tree.front();
      if(temp) delete temp;
      _tree.pop();
  }
  if(snakeAtomic) delete snakeAtomic;
  // if(_sqg) delete _sqg; #Double Delete

  if(std) delete std;
}

void Snake::renderSnake(SDL_Renderer * renderer, SDL_Surface *sf){
  SnakeDatum* refHead = _tree.back();

  std::queue<SnakeDatum*> g = _tree;
  while (!g.empty()) {
      SnakeDatum* temp = g.front();
      if(temp->x == refHead->x && temp->y == refHead->y && temp!=refHead) GameOver();
      SDL_Rect sq = _sqg->getRect(temp->x, temp->y);
      // rectangleColor(renderer, sq.x, sq.y, sq.x+sq.w, sq.y+sq.h, ColorPalette::BLACK);
      snakeAtomic->draw_selected_sprite(sf, &sq);
      g.pop();
  }

  // Debag
  Square* sq = _sqg->getBox(_tree.front()->x, _tree.front()->y);
  boxColor(renderer, sq->x1, sq->y1, sq->x2, sq->y2, ColorPalette::RED);
  delete sq;

  sq = _sqg->getBox(refHead->x, refHead->y);
  boxColor(renderer, sq->x1, sq->y1, sq->x2, sq->y2, ColorPalette::BLUE);
  delete sq;
}

void Snake::processEvent(const SDL_Event *e){
  SnakeDirection prev = _tree.back()->direction;
  if(e->type == SDL_KEYDOWN){
      switch( e->key.keysym.sym )
      {
          case SDLK_w:
              if(prev!=SnakeDirection::DOWN) *std = SnakeDirection::UP;
              break;

          case SDLK_s:
              if(prev!=SnakeDirection::UP) *std = SnakeDirection::DOWN;
              break;

          case SDLK_a:
              if(prev!=SnakeDirection::RIGHT) *std = SnakeDirection::LEFT;
              break;

          case SDLK_d:
              if(prev!=SnakeDirection::LEFT) *std = SnakeDirection::RIGHT;
              break;
          default:
              break;
      }
  }
}


#endif
