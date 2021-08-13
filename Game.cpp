#ifndef GAME_CPP
#define GAME_CPP

#include "Game.h"
#include "SCENE_.h"
#include "entry.h"
#include "SquareBoxGrid.cpp"
#include "Snake.cpp"

Spritesheet *backsp;
Button backbutton;
SquareBoxGrid * helpergrid;
Snake *snake;
float counter;
int a, b;

void changeToMenu(){
  printf("Change to main menu\n");
  setScreen(SCENE_::MAIN);
}

Game::Game(SDL_Window *window, SDL_Renderer *renderer):SceneLayout(window, renderer){
  SDL_SetRenderDrawColor(renderer, 255,255,255,255);

  int flags = IMG_INIT_PNG;
  int initted = IMG_Init(flags);
  if ((initted & flags) != flags) {
      printf("IMG_Init: Failed to init!\n");
      printf("IMG_Init: %s\n", IMG_GetError());
      // handle error
  }

  backsp = new Spritesheet(IMAGE_BACK_BTN, 2, 1);

  SDL_Rect dstrect = {0,0,25,25};

  backbutton = Button(backsp, dstrect, changeToMenu);
  helpergrid = new SquareBoxGrid(WIDTH, HEIGHT, 40);
  helpergrid->getBoxDimen(&a, &b);

  snake = new Snake(helpergrid);

  snake->addSnakeDatumOnDirect();

  snake->addSnakeDatumOnDirect();

  counter = 0;
}

void Game::gameloop(float step){
  counter+=step;
  if(counter>0.5){
    snake->addSnakeDatumOnDirect();
    //snake->removeLastSnakeDatum();

    printf("Half sec\n");
    counter = 0;
  }
  SDL_SetRenderDrawColor(renderer, 255,255,255,255);
  SDL_RenderClear(renderer);

  SDL_Surface* tempSurface = SDL_CreateRGBSurface(0,WIDTH,HEIGHT, 32, 0xff, 0xff00, 0xff0000, 0xff000000);
  backbutton.renderButton(tempSurface);

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_FreeSurface(tempSurface);
  SDL_DestroyTexture(texture);

  //helpergrid->renderHelperRects(renderer);
  snake->renderSnake(renderer);


  SDL_RenderPresent(renderer);
}

void Game::eventHandler(const SDL_Event &event){
  backbutton.processEvent(&event);
  snake->processEvent(&event);
  // changeToMenu();
}

Game::~Game(){
  if(backsp) delete backsp;
  if(snake) delete snake;
  if(helpergrid) delete helpergrid;

  IMG_Quit();
}

#endif
