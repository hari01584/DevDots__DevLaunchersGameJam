//
// Created by hari0 on 15-04-2021.
//

#ifndef ANDROID_PROJECT_BUTTON_H
#define ANDROID_PROJECT_BUTTON_H

class Button
{
    SDL_Rect Message_rect;
    Spritesheet * sprites;
    bool buttonClick = false;
    bool buttonRelease = true;
    void(*click)();

public:
    Button();
    ~Button();
    Button(Spritesheet* s, SDL_Rect r, void(*c)());

    Spritesheet* getSprites() {
        return sprites;
    }

    const SDL_Rect * getRect() {
        return &Message_rect;
    }
    void processEvent(const SDL_Event *e, bool *isClick=NULL);
    bool processEventGetClicked(const SDL_Event *e);
    void renderButton(SDL_Surface* surface);
};



#endif //ANDROID_PROJECT_BUTTON_H
