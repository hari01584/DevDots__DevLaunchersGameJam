#ifndef TEXTURESHEET_CPP
#define TEXTURESHEET_CPP

#include "TextureSheet.h"

TextureSheet::TextureSheet(const char* path, SDL_Renderer *renderer, int rows, int column){
  this->r = rows;
  this->c = column;

  SDL_Surface* loadedSurface = IMG_Load(path);
  this->w = loadedSurface->w / c;
  this->h = loadedSurface->h / r;

  texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
  if(loadedSurface) SDL_FreeSurface(loadedSurface);

  select(1, 1);
}

TextureSheet::~TextureSheet(){
  if(texture) SDL_DestroyTexture(texture);
}

void TextureSheet::select(int ir, int ic){
  if(ir>r || ic>c || ir<0 || ic < 0){
    printf("Error in selecting texture box! Invalid row or column => %d %d\n", ir, ic);
  }
  ir--; ic--;
  currentSelection = { ic*w , ir*h, w, h };
}

void TextureSheet::renderTexture(SDL_Renderer *renderer, const SDL_Rect *rect){
  SDL_RenderCopy(renderer, texture, &currentSelection, rect);
}

void TextureSheet::renderTextureEx(SDL_Renderer *renderer, const SDL_Rect *rect, const double angle, const SDL_Point *center, const SDL_RendererFlip flip){
  SDL_RenderCopyEx(renderer, texture, &currentSelection, rect, angle, center, flip);
}

#endif
