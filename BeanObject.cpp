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
  // for(int i=0; i<MAX_NORMAL_BEANS_PLACED; i++){
  //   BeanCoords bc;
  //   bool isGB = utils::RandE(0, 100);
  //   if(isGB<gBeansProbabilityPerc) bc.beanType = BType::GOLDEN;
  //   else bc.beanType = BType::NORMAL;
  //   bc.x = utils::RandE(0, _a);
  //   bc.y = utils::RandE(0, _b);
  //   beans.push_back(bc);
  // }
}
//
BeanObject::~BeanObject(){
  delete beanSheet;
  beans.clear();
}

#endif
