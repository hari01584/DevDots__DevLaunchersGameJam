#ifndef ANDROID_PROJECT_SPRITESHEET_H
#define ANDROID_PROJECT_SPRITESHEET_H

class Spritesheet
{
public:
    Spritesheet();
    Spritesheet(char const* path, int row, int column);
    ~Spritesheet();

    void select_sprite(int x, int y);
    void draw_selected_sprite(SDL_Surface* window_surface, SDL_Rect* position);

    void getSize(int* w, int* h);

    void draw_9patch_sprite(SDL_Surface *target, SDL_Rect* position);

    void setNinePatch(const char* loc,int top, int bottom, int left, int right, bool repeat);
private:
    SDL_Rect     m_clip;
    SDL_Surface* m_spritesheet_image;

    int srcX[3];
    int srcY[3];
    int srcW[3];
    int srcH[3];

    SDL_Surface* ninepbg;
    bool isContainsBg;
    int top;
    int bottom;
    int left;
    int right;;
    bool repeat;

};

#endif //ANDROID_PROJECT_SPRITESHEET_H
