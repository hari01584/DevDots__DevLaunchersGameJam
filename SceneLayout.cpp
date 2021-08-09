#ifndef SCENE_LAYOUT
#define SCENE_LAYOUT
#include "SCENE_.h"
class SceneLayout{
public:
  virtual void gameloop() = 0;
  virtual void mouseClick() = 0;

  SceneLayout(){};
  virtual ~SceneLayout() = 0;
};

#endif
