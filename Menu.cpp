#ifndef MENU_CPP
#define MENU_CPP

#include "Menu.h"
#include "utils.cpp"
#include "StarShape.cpp"

#include "ColorPalette.h"

StarShape * star;
StarShape * star2;
StarShape * star3;

Menu::Menu(SDL_Window *window, SDL_Renderer *renderer) : SceneLayout(window, renderer){
  printf("Menu Welcomes You! Click on the player to change color\n");
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

  star = new StarShape(100, 150, 10);
  star2 = new StarShape(100, 220, 10, -1, 0, 4);
  star3 = new StarShape(200, 150, 10, 50, 30);

}

void Menu::gameloop(){
  SDL_RenderClear(renderer);

  //SDL_RenderDrawPoint(renderer, 400, 300);
  // SDL_RenderSetScale(renderer, 2, 2);
  //aacircleColor(renderer, 100, 100, 40, ColorPalette::RED);
  //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  star->drawStars(renderer);
  star2->drawStars(renderer);
  star3->drawStars(renderer);

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
  printf("Menu Closed!!\n");
}

#endif
