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
  delete current;
  if(scene == SCENE_::MAIN){
    current = new Menu(window, renderer);
    printf("E21\n");
  }
  else if(scene == SCENE_::INGAME){
    current = new Game(window, renderer);
  }
  printf("E23\n");

}

void frame()
{
  printf("E30\n");

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
          printf("E25\n");
          current->eventHandler(event);
          printf("E47\n");

          break;
      }

  }
  printf("E55\n");

  Uint32 oldTime = currentTime;
  currentTime = SDL_GetTicks();
  float step = (currentTime - oldTime) / 1000.f;
  printf("E60\n");
  current->gameloop(step);
  printf("E62\n");

}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);

    current = new Game(window, renderer);
    currentTime = SDL_GetTicks();
    emscripten_set_main_loop(frame, 0, 1);
}
