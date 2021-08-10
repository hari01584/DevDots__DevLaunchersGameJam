#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <emscripten.h>

#include "SCENE_.h"
#include "SceneLayout.cpp"
#include "Menu.cpp"

SDL_Window *window;
SDL_Renderer *renderer;
TTF_Font *font;
SceneLayout* current;
Uint32 currentTime;

void setScreen(SCENE_ scene){
  delete current;
  if(scene == SCENE_::MAIN){
    current = new Menu(window, renderer);
  }
}

void frame()
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
      switch (event.type)
      {
      case SDL_QUIT:
          emscripten_cancel_main_loop();
          break;
      case SDL_WINDOWEVENT:
          if (event.window.event == SDL_WINDOWEVENT_RESIZED)
          {

          }
          break;
      case SDL_MOUSEBUTTONDOWN:
          // SDL_SetRenderDrawColor(renderer, RandU(0,255),RandU(0,255), RandU(0,255), RandU(0,255));
          current->eventHandler(event);
          break;
      default:
          break;
      }

  }
  Uint32 oldTime = currentTime;
  currentTime = SDL_GetTicks();
  float step = (currentTime - oldTime) / 1000.f;
  
  current->gameloop(step);
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer);

    current = new Menu(window, renderer);
    currentTime = SDL_GetTicks();
    emscripten_set_main_loop(frame, 0, 1);
}
