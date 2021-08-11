#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <emscripten.h>
#include "SCENE_.h"
#include "SceneLayout.cpp"
#include "Menu.cpp"
#include "Game.cpp"
#include "entry.h"

SDL_Window *window;
SDL_Renderer *renderer;
TTF_Font *font;
SceneLayout* current;
Uint32 currentTime;

static void setScreen(SCENE_ scene){
  if(current) delete current;
  if(scene == SCENE_::MAIN){
    current = new Menu(window, renderer);
  }
  else if(scene == SCENE_::INGAME){
    current = new Game(window, renderer);
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
      default:
          current->eventHandler(event);
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
