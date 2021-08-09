#ifndef MENU_CPP
#define MENU_CPP

#import "Menu.h"
#import "utils.cpp"

Menu::Menu(SDL_Window *window, SDL_Renderer *renderer) : SceneLayout(window, renderer){
  printf("Menu Welcomes You! Click on the player to change color\n");
}

void Menu::gameloop(){


  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
}

void Menu::eventHandler(const SDL_Event &event){
  int r = utils::RandU(0,255);
  int g = utils::RandU(0,255);
  int b = utils::RandU(0,255);
  SDL_SetRenderDrawColor(renderer, r, g, b, 255);
  printf("Color %d %d %d\n", r, g, b);
}

Menu::~Menu(){
  printf("Menu Closed!!\n");
}

#endif
