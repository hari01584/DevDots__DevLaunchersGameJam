#ifndef GAME_CPP
#define GAME_CPP

#include "Game.h"
#include "SCENE_.h"
#include "entry.h"
#include "SquareBoxGrid.cpp"
#include "Snake.cpp"
<<<<<<< Updated upstream
=======
#include "SDL_Mixer.h"
#include "SoundBox.cpp"
#include "BeanObject.cpp"
>>>>>>> Stashed changes

Spritesheet *backsp;
Button backbutton;
SquareBoxGrid * helpergrid;
// BeanObject *beans;
Snake *snake;
float counter;
int a, b;

void Game::changeToMenu(int x){
  //delete this;
  stop = true;
  printf("Change to main menu\n");
  setScreen(SCENE_::MAIN);
  printf("Return\n");
  //delete this;
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
  backbutton = Button(backsp, dstrect, NULL);

  using namespace std::placeholders;
  backbutton.addHandler(std::bind(&Game::changeToMenu, this, _1));


  helpergrid = new SquareBoxGrid(WIDTH, HEIGHT, 40);
  helpergrid->getBoxDimen(&a, &b);

  snake = new Snake(helpergrid);

  snake->addSnakeDatumOnDirect();
  snake->addSnakeDatumOnDirect();
  counter = 0;

  // beans = new BeanObject();
}

void Game::gameloop(float step){
  if(stop) return;
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
<<<<<<< Updated upstream
  //changeToMenu();
=======

  //backbutton.processEvent(&event);
  if(backbutton.processEventGetClicked(&event)){
    printf("Cleeecked\n");
    setScreen(SCENE_::MAIN);
  }
  setScreen(SCENE_::MAIN);

>>>>>>> Stashed changes
}

Game::~Game(){
  if(backsp) delete backsp;
  if(snake) delete snake;
  if(helpergrid) delete helpergrid;
<<<<<<< Updated upstream

  IMG_Quit();
=======
  // if(beans) delete beans;
>>>>>>> Stashed changes
}

#endif
