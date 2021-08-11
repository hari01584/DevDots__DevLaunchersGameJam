#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <stdio.h>
#include "SceneLayout.cpp"

class Game: public SceneLayout{
public:
  Game(SDL_Window *window, SDL_Renderer *renderer);
  void gameloop(float step);
  void eventHandler(const SDL_Event &event);
  ~Game();
};

#endif
