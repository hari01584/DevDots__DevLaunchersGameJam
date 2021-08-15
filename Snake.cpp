#ifndef SNAKE_CPP
#define SNAKE_CPP
#include "Snake.h"
#include "SnakeDatum.h"
#include "SquareBoxGrid.h"
#include "utils.cpp"
#include "ColorPalette.h"
#include "SDL.h"
#include "SDL_Image.h"
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

  SnakeDirection d = _head->direction;
  if(d != *std){
    _head->extraPrev = *std;
  }
  _tree.push(new SnakeDatum(ix, iy, *std));
  // this->removeLastSnakeDatum();
}

void Snake::removeLastSnakeDatum(){
  delete _tree.front();
  _tree.pop();
}

Snake::Snake(SquareBoxGrid *sqg, SDL_Renderer * renderer){
  this->_sqg = sqg;

  int sx, sy;
  sqg->getBoxDimen(&sx, &sy);
  _a = sx;
  _b = sy;
  initSnakeDatum(sx/2, sy/2);
  //
  // snakeAtomic = new Spritesheet(IMAGE_SN_BODY, 1, 1);
  // snakeAtomic->select_sprite(0, 0);
  // SDL_Surface* loadedSurface = IMG_Load(IMAGE_SN_FULL);
  // bodyTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
  //
  // if(loadedSurface) SDL_FreeSurface(loadedSurface);
  bodyTexture = new TextureSheet(IMAGE_SN_FULL, renderer, 3, 3);
  // Init Boundaries
  // bodySimple = {95, 85, };
}

Snake::~Snake(){
  while (!_tree.empty()) {
      SnakeDatum* temp = _tree.front();
      if(temp) delete temp;
      _tree.pop();
  }
  if(snakeAtomic) delete snakeAtomic;
  // if(_sqg) delete _sqg; #Double Delete
  if(bodyTexture) delete bodyTexture;
  if(std) delete std;
}

void Snake::_tertiarySnakeSelector(SnakeDirection next, SnakeDirection now){
  if(next==SnakeDirection::RIGHT){
    if(now==SnakeDirection::UP){
      bodyTexture->select(1,2);
    } else if(now==SnakeDirection::DOWN){
      bodyTexture->select(2,2);
    }
  }
  else if(next==SnakeDirection::LEFT){
    if(now==SnakeDirection::UP){
      bodyTexture->select(1,3);
    } else if(now==SnakeDirection::DOWN){
      bodyTexture->select(2,3);
    }
  }
  else if(next==SnakeDirection::UP){
    if(now==SnakeDirection::LEFT){
      bodyTexture->select(2,2);
    } else if(now==SnakeDirection::RIGHT){
      bodyTexture->select(2,3);
    }
  }
  else if(next==SnakeDirection::DOWN){
    if(now==SnakeDirection::LEFT){
      bodyTexture->select(1,2);
    } else if(now==SnakeDirection::RIGHT){
      bodyTexture->select(1,3);
    }
  }
}

int Snake::_primarySnakeSelector(SnakeDirection now){
  if(now == SnakeDirection::UP) return 180;
  if(now == SnakeDirection::DOWN) return 0;
  if(now == SnakeDirection::LEFT) return 90;
  if(now == SnakeDirection::RIGHT) return 270;
  return 0;
}

void Snake::renderSnake(SDL_Renderer * renderer){
  SnakeDatum* refHead = _tree.back();

  std::queue<SnakeDatum*> g = _tree;
  int r = _sqg->boxSize / 2 - 1;
  while (!g.empty()) {
      SnakeDatum* temp = g.front();
      if(temp == refHead){
        g.pop();
        continue;
      }

      if(temp->x == refHead->x && temp->y == refHead->y && temp!=refHead) GameOver();
      SDL_Rect sq = _sqg->getRect(temp->x, temp->y);
      // rectangleColor(renderer, sq.x, sq.y, sq.x+sq.w, sq.y+sq.h, ColorPalette::BLACK);
      // filledCircleColor(renderer, sq.x + sq.w/2, sq.y + sq.w/2, r,ColorPalette::BLUE);
      // snakeAtomic->draw_selected_sprite(sf, &sq);
      SnakeDirection ps = temp->extraPrev;
      SnakeDirection s = temp->direction;
      int angle = 90;

      if(ps == SnakeDirection::NONE){
        if(s == SnakeDirection::UP || s == SnakeDirection::DOWN) angle += 90;

        bodyTexture->select(3,3);
        bodyTexture->renderTextureEx(renderer, &sq, angle, NULL, SDL_FLIP_NONE);
      }
      else{
        _tertiarySnakeSelector(ps, s);
        bodyTexture->renderTexture(renderer, &sq);
      }
      g.pop();
  }

  SnakeDatum * tail = _tree.front();

  // Square* sq2 = _sqg->getBox(tail->x, tail->y);
  // boxColor(renderer, sq2->x1, sq2->y1, sq2->x2, sq2->y2, ColorPalette::WHITE);
  // delete sq2;
  // SnakeDirection sd2 = tail->direction;
  // SDL_Rect sqz2 = _sqg->getRect(tail->x, tail->y);
  // bodyTexture->select(3,2);
  // bodyTexture->renderTextureEx(renderer, &sqz2, _primarySnakeSelector(sd2) + 180, NULL, SDL_FLIP_NONE);


  // Square* sq = _sqg->getBox(refHead->x, refHead->y);
  // boxColor(renderer, sq->x1, sq->y1, sq->x2, sq->y2, ColorPalette::WHITE);
  // delete sq;
  SDL_Rect sqz = _sqg->getRect(refHead->x, refHead->y);
  SnakeDirection sd = refHead->direction;
  bodyTexture->select(3,1);
  bodyTexture->renderTextureEx(renderer, &sqz, _primarySnakeSelector(sd), NULL, SDL_FLIP_NONE);
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
