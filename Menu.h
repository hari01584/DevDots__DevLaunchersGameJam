#ifndef MENU_H
#define MENU_H

#include <SDL.h>
class Menu: public SceneLayout{

public:
  Menu(SDL_Window *window, SDL_Renderer *renderer);
  void gameloop(float step);
  void eventHandler(const SDL_Event &event);
  ~Menu();
};

#endif
