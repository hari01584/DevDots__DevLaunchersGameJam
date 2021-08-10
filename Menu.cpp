#ifndef MENU_CPP
#define MENU_CPP

#include "Menu.h"
#include "utils.cpp"
#include "StarShape.cpp"
#include "ColorPalette.h"
#include <vector>
#include "Spritesheet.cpp"
#include "Button.cpp"
#include "consts.h"

#include "ColorPalette.h"

SDL_Surface* title;
SDL_Rect titleRect;

std::vector<StarShape*> stars;
Spritesheet *play;
Spritesheet *howtop;
Spritesheet *creds;
Button b1;
Button b2;
Button b3;

Menu::Menu(SDL_Window *window, SDL_Renderer *renderer) : SceneLayout(window, renderer){
  printf("Menu Welcomes You!\n");

  title = IMG_Load(TITLE_PATH);
  int tw = title->w;
  int th = title->h;
  float asp = th/tw;

  int tx = (WIDTH - tw) / 2;
  int ty = (HEIGHT - th) / 4;
  titleRect = { tx, ty, tw ,th };

  play = new Spritesheet(IMAGE_PLAY, 2, 1);
  play->setNinePatch(IMAGE_PLAY_BG,20,20,20,20, true);

  creds = new Spritesheet(IMAGE_CREDS, 2, 1);
  creds->setNinePatch(IMAGE_CREDS_BG,20,20,20,20, true);

  howtop = new Spritesheet(IMAGE_HOWTOP, 2, 1);
  howtop->setNinePatch(IMAGE_HOWTOP_BG,20,20,20,20, true);

  SDL_SetRenderDrawColor(renderer, 255,255,255,255);

  for(int i=0;i<100;i++){
    stars.push_back(new StarShape(utils::RandU(0,640),utils::RandU(0,480), utils::RandU(1,4), utils::RandU(10,40)));
  }

  int w = 400;
  int h = 70;
  SDL_Rect dstrect = {(WIDTH - w)/2,int((HEIGHT - h)*0.56666),w,h};

  b1 = Button(play, dstrect, NULL);

  dstrect.y += h + 8;
  b2 = Button(howtop, dstrect, NULL);

  dstrect.y += h + 8;
  b3 = Button(creds, dstrect, NULL);
}

void Menu::gameloop(float step){
  SDL_SetRenderDrawColor(renderer, 255,255,255,255);
  SDL_RenderClear(renderer);

  for(auto itr : stars){
    itr->increaseAndBuild(step);
    itr->drawStars(renderer);
  }

  SDL_Surface* tempSurface = SDL_CreateRGBSurface(0,WIDTH,HEIGHT, 32, 0xff, 0xff00, 0xff0000, 0xff000000);
  SDL_BlitScaled(title, NULL, tempSurface, &titleRect);

  b1.renderButton(tempSurface);
  b2.renderButton(tempSurface);
  b3.renderButton(tempSurface);

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_FreeSurface(tempSurface);
  SDL_DestroyTexture(texture);

  SDL_RenderPresent(renderer);
}

void Menu::eventHandler(const SDL_Event &event){
  b1.processEvent(&event);
  b2.processEvent(&event);
  b3.processEvent(&event);

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
  delete play;
  delete howtop;
  delete creds;
  // delete b1;
  printf("Menu Closed!!\n");
}

#endif
