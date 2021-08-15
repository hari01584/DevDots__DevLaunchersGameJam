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
#include "Text.cpp"

Spritesheet *backsp;
Button backbutton;
SquareBoxGrid * helpergrid;
Snake *snake;
float counter;
int a, b;
BeanObject *beans;
TTF_Font * font;
Text scores;
static int scoreAmt;

SoundBox *bgMusic;
SoundBox *eatEffect;

Game::Game(SDL_Window *window, SDL_Renderer *renderer):SceneLayout(window, renderer){
  SDL_SetRenderDrawColor(renderer, 255,255,255,255);

  backsp = new Spritesheet(IMAGE_BACK_BTN, 2, 1);
  SDL_Rect dstrect = {0,0,25,25};

  backbutton = Button(backsp, dstrect, NULL);
  helpergrid = new SquareBoxGrid(WIDTH, HEIGHT, 40);
  helpergrid->getBoxDimen(&a, &b);

  snake = new Snake(helpergrid, renderer);
  snake->addSnakeDatumOnDirect();
  snake->addSnakeDatumOnDirect();
  counter = 0;

  beans = new BeanObject(helpergrid);

  font = TTF_OpenFont(FONT_TEXT_PATH, 25);
  dstrect.x += dstrect.w + 8;
  dstrect.w = 50;
  SDL_Color color = {0, 0, 0};
  std::string scoreStr = "0";
  scoreAmt = 0;
  scores = Text(renderer, font, scoreStr, color, dstrect);

  bgMusic = new SoundBox(SOUND_GAME_HYPE);
  bgMusic->play();
  eatEffect = new SoundBox(SOUND_BITE, false);
}

void Game::gameloop(float step){
  counter+=step;
  if(counter>0.25){
    snake->addSnakeDatumOnDirect();
    BType b;
    if((b = beans->beansBuilderGetCollison(snake->getSnakePointer()))==BType::NONE){
      snake->removeLastSnakeDatum();
    }
    else if(b == BType::NORMAL){
      eatEffect->play();
      scoreAmt += 1;
    }
    else if(b == BType::GOLDEN){
      eatEffect->play();
      scoreAmt += 2;
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
  scores.dynamicRender(renderer, std::to_string(scoreAmt).c_str());

  if(snake->renderSnake(renderer)){
    return;
  }

  SDL_RenderPresent(renderer);
}

void Game::eventHandler(const SDL_Event &event){
  snake->processEvent(&event);

  //backbutton.processEvent(&event);
  if(backbutton.processEventGetClicked(&event)){
    setScreen(SCENE_::MAIN);
  }

}

Game::~Game(){
  bgMusic->stop();
  if(backsp) delete backsp;
  if(snake) delete snake;
  if(helpergrid) delete helpergrid;
  if(bgMusic) delete bgMusic;
  if(eatEffect) delete eatEffect;
  if(beans) delete beans;
  TTF_CloseFont(font);
}

#endif
