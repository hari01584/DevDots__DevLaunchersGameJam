#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <stdio.h>
#include "SceneLayout.cpp"

class Menu: public SceneLayout{
public:
  Menu(SDL_Window *window, SDL_Renderer *renderer);
  void gameloop();
  void eventHandler(const SDL_Event &event);
  ~Menu();
};

#endif
