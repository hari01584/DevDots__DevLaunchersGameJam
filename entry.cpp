#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <emscripten.h>

#include "SCENE_.h"
#include "Menu.cpp"
#include "SceneLayout.cpp"

SDL_Window *window;
SDL_Renderer *renderer;
TTF_Font *font;
SceneLayout* current;

void setScreen(SCENE_ scene){
  delete current;
  if(scene == SCENE_::MAIN){
    current = new Menu();
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
          break;
      default:
          break;
      }
  }

}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer);

    SceneLayout* current = new Menu();
    emscripten_set_main_loop(frame, -1, 1);
}
