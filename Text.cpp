//
// Created by hari0 on 21-04-2021.
//

#include "Text.h"
#include "dimens.h"

Text::Text(){
    this->tempTexture = NULL;
}

Text::~Text(){
    SDL_DestroyTexture(tempTexture);
}

Text::Text(SDL_Renderer* renderer,TTF_Font* font, std::string text, SDL_Color textColor, SDL_Rect rect){
    this->font = font;
    this->text = text;
    this->textColor=textColor;

    int w,h;
    TTF_SizeText(font, text.c_str(), &w, &h);
    if(rect.w == -1){
        rect.w=w;
    }
    if(rect.h == -1){
       // rect.h = rect.w * h/w;
       rect.h = h;
    }

    this->rect = rect;

    SDL_Surface* surfaceMessage = TTF_RenderText_Blended_Wrapped(font, text.c_str(), textColor, width);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    this->tempTexture = texture;

    SDL_FreeSurface(surfaceMessage);
}


void Text::renderText(SDL_Renderer* renderer){

    SDL_RenderCopy(renderer, tempTexture, NULL, &rect);
}

SDL_Rect* Text::getRect() {
    return &rect;
}

void Text::dynamicRender(SDL_Renderer* renderer, const char* c){
    SDL_DestroyTexture(tempTexture);

    SDL_Surface* surfaceMessage = TTF_RenderText_Blended_Wrapped(font, c, textColor, width);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    this->tempTexture = texture;

    int w,h;
    TTF_SizeText(font, c, &w, &h);

    //rect.w = w * rect.h/h;
    //rect.x -= rect.h/h;

    SDL_RenderCopy(renderer, tempTexture, NULL, &rect);
    SDL_FreeSurface(surfaceMessage);
}



void Text::processEvent(SDL_Event* event){


}
