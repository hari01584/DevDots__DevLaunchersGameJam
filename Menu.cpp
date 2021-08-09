#ifndef MENU_CPP
#define MENU_CPP

#include <SDL.h>
#include <stdio.h>
#include "SceneLayout.cpp"

class Menu: public SceneLayout{
public:
  Menu(SDL_Window *window, SDL_Renderer *renderer) : SceneLayout(window, renderer){
    printf("Menu Welcomes You!\n");
  }
  void gameloop(){
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
  }
  void eventHandler(const SDL_Event &event){
    printf("Yey\n");
    SDL_SetRenderDrawColor(renderer, 255,0,0,255);
  }
  ~Menu(){
    printf("Menu Closed!!\n");
  }
};

#endif
