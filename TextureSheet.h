#ifndef TEXTURESHEET_H
#define TEXTURESHEET_H

class TextureSheet{
  int r, c;
  int w, h;
public:
  SDL_Texture *texture = NULL;
  SDL_Rect currentSelection;

  TextureSheet(const char* path, SDL_Renderer *renderer, int rows=1, int column=1);
  ~TextureSheet();

  void select(int r, int c);
  void renderTexture(SDL_Renderer *renderer, const SDL_Rect *rect);
  void renderTextureEx(SDL_Renderer *renderer, const SDL_Rect *rect, const double angle, const SDL_Point *center, const SDL_RendererFlip flip);
};

#endif
