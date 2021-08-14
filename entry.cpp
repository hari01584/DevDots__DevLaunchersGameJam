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
          if(current) current->eventHandler(event);
          break;
      }

  }
  Uint32 oldTime = currentTime;
  currentTime = SDL_GetTicks();
  float step = (currentTime - oldTime) / 1000.f;

  if(current) current->gameloop(step);
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    if(SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0){
         printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
    }

    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);

    int flags = IMG_INIT_PNG;
    int initted = IMG_Init(flags);
    if ((initted & flags) != flags) {
        printf("IMG_Init: Failed to init!\n");
        printf("IMG_Init: %s\n", IMG_GetError());
        // handle error
    }
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
      printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }

    current = new Game(window, renderer);
    currentTime = SDL_GetTicks();
    emscripten_set_main_loop(frame, 0, 1);

    delete current;
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();

    printf("Yes? \n");
}
