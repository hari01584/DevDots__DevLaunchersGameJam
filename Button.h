//
// Created by hari0 on 15-04-2021.
//

#ifndef ANDROID_PROJECT_BUTTON_H
#define ANDROID_PROJECT_BUTTON_H

#include <functional>

class Button
{
    SDL_Rect Message_rect;
    Spritesheet * sprites;
    bool buttonClick = false;
    bool buttonRelease = true;
    void(*click)();
    std::function<void(int)> callback;

public:
    Button();
    ~Button();
    Button(Spritesheet* s, SDL_Rect r, void(*c)());

    void addHandler(std::function<void(int)> callback);

    Spritesheet* getSprites() {
        return sprites;
    }

    const SDL_Rect * getRect() {
        return &Message_rect;
    }
    void processEvent(const SDL_Event *e);
    void renderButton(SDL_Surface* surface);
};



#endif //ANDROID_PROJECT_BUTTON_H
