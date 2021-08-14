#ifndef GAME_CPP
#define GAME_CPP

#include "Game.h"
#include "SCENE_.h"
#include "entry.h"
#include "SquareBoxGrid.cpp"
#include "Snake.cpp"
#include "SDL_Mixer.h"
#include "SoundBox.cpp"
#include "BeanObject.cpp"

Spritesheet *backsp;
Button backbutton;
SquareBoxGrid * helpergrid;
Snake *snake;
float counter;
int a, b;
BeanObject *beans;

Game::Game(SDL_Window *window, SDL_Renderer *renderer):SceneLayout(window, renderer){
  SDL_SetRenderDrawColor(renderer, 255,255,255,255);

  backsp = new Spritesheet(IMAGE_BACK_BTN, 2, 1);
  SDL_Rect dstrect = {0,0,25,25};

  backbutton = Button(backsp, dstrect, NULL);
  helpergrid = new SquareBoxGrid(WIDTH, HEIGHT, 40);
  helpergrid->getBoxDimen(&a, &b);

  snake = new Snake(helpergrid);
  snake->addSnakeDatumOnDirect();
  snake->addSnakeDatumOnDirect();
  counter = 0;

  beans = new BeanObject(helpergrid);

}

void Game::gameloop(float step){
  counter+=step;
  if(counter>0.5){
    snake->addSnakeDatumOnDirect();
    BType b;
    if((b = beans->beansBuilderGetCollison(snake->getSnakePointer()))==BType::NONE){
      snake->removeLastSnakeDatum();
    }
    counter = 0;
  }
  SDL_SetRenderDrawColor(renderer, 255,255,255,255);
  SDL_RenderClear(renderer);

  SDL_Surface* tempSurface = SDL_CreateRGBSurface(0,WIDTH,HEIGHT, 32, 0xff, 0xff00, 0xff0000, 0xff000000);
  beans->beansRender(tempSurface);
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
  snake->processEvent(&event);

  //backbutton.processEvent(&event);
  if(backbutton.processEventGetClicked(&event)){
    printf("Cleeecked\n");
    setScreen(SCENE_::MAIN);
  }

}

Game::~Game(){
  if(backsp) delete backsp;
  if(snake) delete snake;
  if(helpergrid) delete helpergrid;

}

#endif
