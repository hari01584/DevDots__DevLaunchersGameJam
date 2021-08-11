#ifndef GAME_CPP
#define GAME_CPP

#include "Game.h"
#include "SCENE_.h"
#include "entry.h"

Spritesheet *backsp;
Button backbutton;

void changeToMenu(){
  setScreen(SCENE_::MAIN);
}

Game::Game(SDL_Window *window, SDL_Renderer *renderer):SceneLayout(window, renderer){
  SDL_SetRenderDrawColor(renderer, 255,255,255,255);

  backsp = new Spritesheet(IMAGE_BACK_BTN, 2, 1);
  SDL_Rect dstrect = {0,0,25,25};

  backbutton = Button(backsp, dstrect, changeToMenu);
}

void Game::gameloop(float step){
  SDL_SetRenderDrawColor(renderer, 255,255,255,255);
  SDL_RenderClear(renderer);

  SDL_Surface* tempSurface = SDL_CreateRGBSurface(0,WIDTH,HEIGHT, 32, 0xff, 0xff00, 0xff0000, 0xff000000);
  backbutton.renderButton(tempSurface);

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_FreeSurface(tempSurface);
  SDL_DestroyTexture(texture);

  SDL_RenderPresent(renderer);
}

void Game::eventHandler(const SDL_Event &event){
  backbutton.processEvent(&event);

}

Game::~Game(){

}

#endif
