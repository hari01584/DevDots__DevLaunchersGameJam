//
// Created by hari0 on 21-04-2021.
//

#ifndef ANDROID_PROJECT_TEXT_H
#define ANDROID_PROJECT_TEXT_H


#include "import.h"

class Text {
    TTF_Font * font;
    std::string text;
    SDL_Rect rect;
    SDL_Color textColor;
    SDL_Texture* tempTexture;

public:
    Text();
    ~Text();
    Text(SDL_Renderer* renderer, TTF_Font* font, std::string text, SDL_Color textColor, SDL_Rect rect);
    void renderText(SDL_Renderer* renderer);
    void dynamicRender(SDL_Renderer* renderer, const char* c);
    void processEvent(SDL_Event* event);

    SDL_Rect* getRect();
};


#endif //ANDROID_PROJECT_TEXT_H
