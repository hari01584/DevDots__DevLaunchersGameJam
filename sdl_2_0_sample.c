#include <SDL.h>
#include <SDL_ttf.h>
#include <stdlib.h>
#include <string>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define WIDTH 512
#define HEIGHT 512


SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface *surface;


int RandU(int nMin, int nMax)
{
  int x = nMin + ( rand() % ( nMax - nMin + 1 ) );
  return x;
}

void doSomething() {
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
          SDL_SetRenderDrawColor(renderer, RandU(0,255),RandU(0,255), RandU(0,255), RandU(0,255));
          break;
      default:
          break;
      }
  }

  TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24);

  std::string score_text = "score: 20";
  SDL_Color textColor = { 255, 255, 255, 0 };
  SDL_Surface* textSurface = TTF_RenderText_Solid(font, score_text.c_str(), textColor);
  SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, textSurface);
  int text_width = textSurface->w;
  int text_height = textSurface->h;
  SDL_FreeSurface(textSurface);
  SDL_Rect renderQuad = { 20, 50, text_width, text_height };
  SDL_RenderCopy(renderer, text, NULL, &renderQuad);
  SDL_DestroyTexture(text);


  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
    surface = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);

    emscripten_set_main_loop(doSomething, 0, 1);
}
