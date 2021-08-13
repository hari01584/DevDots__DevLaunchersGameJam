#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <stdio.h>
#include "SceneLayout.cpp"
#include <functional>
#include <functional>


class Game: public SceneLayout{
  bool stop = false;
public:
  void changeToMenu(int x);

  Game(SDL_Window *window, SDL_Renderer *renderer);
  void gameloop(float step);
  void eventHandler(const SDL_Event &event);
  ~Game();
};

#endif
