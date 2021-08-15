#ifndef GAMEOVER_CPP
#define GAMEOVER_CPP

#include "Text.cpp"
#include "GameOver.h"
#include <string>
#include "SoundBox.cpp"

Text gameover;
Text countTb;

SoundBox *dieEffect;

TTF_Font * fntxt;
std::string str;
int score;
float secs;
GameOver::GameOver(SDL_Window *window, SDL_Renderer *renderer):SceneLayout(window, renderer){
  dieEffect = new SoundBox(SOUND_SNAKE_DIE, false);
  dieEffect->play();

  secs = 5;
  fntxt = TTF_OpenFont(FONT_TEXT_PATH, 25);

  std::string go = "GO";
  SDL_Color textColor = {0, 0, 0};

  int tw = 30;
  int th = 30;
  int tx = (WIDTH - tw) / 2;
  int ty = (HEIGHT - th) / 2.5;
  SDL_Rect rect = {tx,ty,tw,th};
  gameover = Text(renderer, fntxt, go, textColor, rect);

  rect.x = 0;
  rect.y = HEIGHT - 60;
  countTb = Text(renderer, fntxt, go, textColor, rect);

  str = "Gameover! Your Score "+std::to_string(scoreAmt);
}

GameOver::~GameOver(){
  if(dieEffect) delete dieEffect;

  TTF_CloseFont(fntxt);
}

void GameOver::gameloop(float step){
  SDL_SetRenderDrawColor(renderer, 255,255,255,255);
  SDL_RenderClear(renderer);

  secs-=step;
  if(secs<0){
    setScreen(SCENE_::INGAME);
    return;
  }
  else{
    std::string coun = "Teleport in "+std::to_string((int)secs);
    countTb.dynamicRender(renderer, coun.c_str());
  }

  gameover.dynamicRender(renderer, str.c_str());
  SDL_RenderPresent(renderer);
}

void GameOver::eventHandler(const SDL_Event &event){


}

#endif
