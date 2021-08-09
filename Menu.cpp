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
  printf("Yey\n");
  SDL_SetRenderDrawColor(renderer, utils::RandU(0,255),utils::RandU(0,255),utils::RandU(0,255), 255);
}

Menu::~Menu(){
  printf("Menu Closed!!\n");
}

#endif
