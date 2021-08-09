#ifndef SCENE_LAYOUT
#define SCENE_LAYOUT
#include <SDL.h>

class SceneLayout{
protected:
  SDL_Window *window;
  SDL_Renderer *renderer;
public:
  virtual void gameloop() = 0;
  virtual void eventHandler(const SDL_Event &event) = 0;

  SceneLayout(SDL_Window *window, SDL_Renderer *renderer){
    this->window = window;
    this->renderer = renderer;
  };
  virtual ~SceneLayout(){};
};

#endif
