#ifndef BEANOBJECT_CPP
#define BEANOBJECT_CPP

#include "BeanObject.h"
#include "Spritesheet.h"
#include "consts.h"
#include "Snake.h"
#include "utils.cpp"
//
BeanObject::BeanObject(SquareBoxGrid *_sqg){
  beanSheet = new Spritesheet(IMAGE_BEANS, 2, 1);
  //
  this->_sqg = _sqg;
  _sqg->getBoxDimen(&_a, &_b);
  for(int i=0; i<MAX_NORMAL_BEANS_PLACED; i++){
    BeanCoords bc;
    int isGB = utils::RandE(0, 100);
    if(isGB<gBeansProbabilityPerc) bc.beanType = BType::GOLDEN;
    else bc.beanType = BType::NORMAL;
    bc.x = utils::RandE(0, _a);
    bc.y = utils::RandE(0, _b);
    beans.push_back(bc);
  }
}
//
BeanObject::~BeanObject(){
  delete beanSheet;
  beans.clear();
}

void BeanObject::_replaceBean(BeanCoords *toReplace){
  int isGB = utils::RandE(0, 100);
  if(isGB<gBeansProbabilityPerc) toReplace->beanType = BType::GOLDEN;
  else toReplace->beanType = BType::NORMAL;
  toReplace->x = utils::RandE(0, _a);
  toReplace->y = utils::RandE(0, _b);
}


BType BeanObject::beansBuilderGetCollison(SnakeDatum *head){
  for(auto &itm: beans){
    int sx = itm.x;
    int sy = itm.y;
    if(sx == head->x && sy == head->y){
      _replaceBean(&itm);
      return itm.beanType;
    }
  }
  return BType::NONE;
}


void BeanObject::beansRender(SDL_Surface *window_surface){
  for(auto &itm: beans){
    int sx = itm.x;
    int sy = itm.y;
    if(itm.beanType == BType::NORMAL)  beanSheet->select_sprite(0,0);
    else beanSheet->select_sprite(0,1);

    SDL_Rect box = _sqg->getRect(sx, sy);
    beanSheet->draw_selected_sprite(window_surface, &box);
  }
}


#endif
