#ifndef MENU_CPP
#define MENU_CPP

#include "Menu.h"
#include "utils.cpp"
#include "ColorPalette.h"

#include "consts.h"
#include "entry.h"

#include "ColorPalette.h"
#include <stdio.h>
#include "SceneLayout.cpp"
#include "Spritesheet.cpp"
#include "Button.cpp"
#include <vector>
#include "SCENE_.h"
#include "StarShape.cpp"

SDL_Texture* title;

std::vector<StarShape*> stars;
Spritesheet *play;
Spritesheet *howtop;
Spritesheet *creds;
Button b1;
Button b2;
Button b3;

void playGame(){
  printf("Change to play game\n");
  setScreen(SCENE_::INGAME);
}

void showHowToPlay(){
  printf("\nHow to play?\n");
  printf("You asked the right person, so basically this game is about a coding snake (or nerd snake) which eats devbeans or normal beans to get his coding energy! But there's a problem, everytime he consume it, he increase in size! and if accidentally he bit himself then he will die! *Your objective is to get maximum number of beans and devbeans to help our little companion in his coding journey!!*\n");
  printf("\nLong story short, this is classic snake-eat-stuff type of game where you have to get max points and somehow avoid the snake biting his own tail! Now you got it, enjoy playing! :D\n");
}

void selfCreds(){
  printf("\nSelf Credits :P!\n");
  printf("You dont have to tell me, yes im shameless to add my name in this work, even though it is just for a gamejam! but say all you want but this is what i like hehhehehe! Anyways, this game is made solely by Agent_Orange#9852(Discord Tag), be sure to friend them and drop a hello if you like it! My motive was to make a game not just for gamejam purposes, but also ingeneral, so my fellow discordians would enjoy it beyond the scope of being used as gamejam submission!\n");
}

Menu::Menu(SDL_Window *window, SDL_Renderer *renderer) : SceneLayout(window, renderer){
  printf("Menu Welcomes You!\n");

  int flags = IMG_INIT_PNG;
  int initted = IMG_Init(flags);
  if ((initted & flags) != flags) {
      printf("IMG_Init: Failed to init!\n");
      printf("IMG_Init: %s\n", IMG_GetError());
      // handle error
  }
  printf("M56!\n");

  SDL_Surface * sur = IMG_Load(TITLE_PATH);
  if(sur!=NULL){
    int tw = sur->w;
    int th = sur->h;
    float asp = th/tw;
    int tx = (WIDTH - tw) / 2;
    int ty = (HEIGHT - th) / 4;
    SDL_Rect titleRect = { tx, ty, tw ,th };

    SDL_Surface* tempSurface = SDL_CreateRGBSurface(0,WIDTH,HEIGHT, 32, 0xff, 0xff00, 0xff0000, 0xff000000);
    SDL_BlitScaled(sur, NULL, tempSurface, &titleRect);
    title = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    SDL_FreeSurface(sur);
  }
  else{
    SDL_Log("Error loading title image\n");
  }
  printf("M76!\n");

  play = new Spritesheet(IMAGE_PLAY, 2, 1);
  play->setNinePatch(IMAGE_PLAY_BG,20,20,20,20, true);

  creds = new Spritesheet(IMAGE_CREDS, 2, 1);
  creds->setNinePatch(IMAGE_CREDS_BG,20,20,20,20, true);

  howtop = new Spritesheet(IMAGE_HOWTOP, 2, 1);
  howtop->setNinePatch(IMAGE_HOWTOP_BG,20,20,20,20, true);
  printf("M86!\n");

  SDL_SetRenderDrawColor(renderer, 255,255,255,255);

  for(int i=0;i<100;i++){
    stars.push_back(new StarShape(utils::RandU(0,640),utils::RandU(0,480), utils::RandU(1,4), utils::RandU(10,40)));
  }
  printf("M87!\n");

  int w = 400;
  int h = 70;
  SDL_Rect dstrect = {(WIDTH - w)/2,int((HEIGHT - h)*0.56666),w,h};

  b1 = Button(play, dstrect, playGame);

  dstrect.y += h + 8;
  b2 = Button(howtop, dstrect, showHowToPlay);

  dstrect.y += h + 8;
  b3 = Button(creds, dstrect, selfCreds);
  printf("M88!\n");

}

void Menu::gameloop(float step){
  SDL_SetRenderDrawColor(renderer, 255,255,255,255);
  SDL_RenderClear(renderer);
  //
  // for(auto itr : stars){
  //   itr->increaseAndBuild(step);
  //   itr->drawStars(renderer);
  // }
  // SDL_RenderCopy(renderer, title, NULL, NULL);
printf("L119!\n");
  SDL_Surface* tempSurface = SDL_CreateRGBSurface(0,WIDTH,HEIGHT, 32, 0xff, 0xff00, 0xff0000, 0xff000000);
  b1.renderButton(tempSurface);
  // b2.renderButton(tempSurface);
  // b3.renderButton(tempSurface);
  printf("L124!\n");

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  printf("L128!\n");

  SDL_FreeSurface(tempSurface);
  SDL_DestroyTexture(texture);
  printf("L132!\n");

  SDL_RenderPresent(renderer);
}

void Menu::eventHandler(const SDL_Event &event){
  //playGame();
  printf("L139!\n");

  b1.processEvent(&event);
  // b2.processEvent(&event);
  // b3.processEvent(&event);
}

Menu::~Menu(){
  for(auto itr : stars){
    if(itr) delete itr;
  }
  stars.clear();

  if(title) SDL_DestroyTexture(title);
  if(play) delete play;
  if(howtop) delete howtop;
  if(creds) delete creds;
  // delete b1;
  IMG_Quit();
}

#endif
