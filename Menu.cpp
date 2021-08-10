#ifndef MENU_CPP
#define MENU_CPP

#include "Menu.h"
#include "utils.cpp"
#include "StarShape.cpp"
#include "ColorPalette.h"
#include <vector>
#include "Spritesheet.cpp"
#include "Button.cpp"

#include "ColorPalette.h"

std::vector<StarShape*> stars;

Menu::Menu(SDL_Window *window, SDL_Renderer *renderer) : SceneLayout(window, renderer){
  printf("Menu Welcomes You! Click on the player to change color\n");
  SDL_SetRenderDrawColor(renderer, 255,255,255,255);

  for(int i=0;i<100;i++){
    stars.push_back(new StarShape(utils::RandU(0,640),utils::RandU(0,480), utils::RandU(1,4), utils::RandU(10,40)));
  }
}

void Menu::gameloop(float step){
  SDL_SetRenderDrawColor(renderer, 255,255,255,255);

  SDL_RenderClear(renderer);

  for(auto itr : stars){
    itr->increaseAndBuild(step);
    itr->drawStars(renderer);
  }

  SDL_RenderPresent(renderer);
}

void Menu::eventHandler(const SDL_Event &event){
  int r = utils::RandU(0,255);
  int g = utils::RandU(0,255);
  int b = utils::RandU(0,255);
  //SDL_SetRenderDrawColor(renderer, r, g, b, 255);
  printf("Color %d %d %d\n", r, g, b);
}

Menu::~Menu(){
  for(auto itr : stars){
    delete itr;
  }
  printf("Menu Closed!!\n");
}

#endif
