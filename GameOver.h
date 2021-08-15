#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <SDL.h>
#include <stdio.h>
#include "SceneLayout.cpp"

class GameOver: public SceneLayout{
public:
  GameOver(SDL_Window *window, SDL_Renderer *renderer);
  void gameloop(float step);
  void eventHandler(const SDL_Event &event);
  friend void changeToGame();
  ~GameOver();
};

#endif
