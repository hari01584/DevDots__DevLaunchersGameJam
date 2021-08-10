//
// Created by hari0 on 15-04-2021.
//
#ifndef BUTTON_CPP
#define BUTTON_CPP

#include "Button.h"
#include "SDL.h"
#include "Spritesheet.h"

Button::Button() {
}

Button::Button(Spritesheet* s, SDL_Rect r, void(*c)())
{
    sprites = s;
    Message_rect = r;
    click = c;
}

void Button::processEvent(const SDL_Event *e) {
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x > Message_rect.x && x < Message_rect.x + Message_rect.w && y>Message_rect.y && y < Message_rect.y + Message_rect.h) {
            if (e->type == SDL_MOUSEBUTTONDOWN && buttonRelease) {
                sprites->select_sprite(0, 1);
                buttonClick = true;
                buttonRelease = false;
            }
            else if (e->type == SDL_MOUSEBUTTONUP && buttonClick) {
                sprites->select_sprite(0, 1);
                click();
                buttonClick = false;
                buttonRelease = true;
            }
            else if(e->type == SDL_MOUSEMOTION){
                sprites->select_sprite(0, 1);
            }
        }
        else if(e->type == SDL_MOUSEMOTION){
            sprites->select_sprite(0, 0);
        }
    }
    else{
        sprites->select_sprite(0, 0);
    }
}

void Button::renderButton(SDL_Surface* surface)
{
    sprites->draw_selected_sprite(surface, &Message_rect);
}

#endif
