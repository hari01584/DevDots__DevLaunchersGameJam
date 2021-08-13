//
// Created by hari0 on 15-04-2021.
//
#ifndef SPRITESHEET_CPP
#define SPRITESHEET_CPP

#include "Spritesheet.h"
#include "SDL.h"
#include <SDL_image.h>

Spritesheet::Spritesheet(){}
Spritesheet::Spritesheet(char const* path, int row, int column)
{
    m_spritesheet_image = IMG_Load(path);
    if(m_spritesheet_image == NULL){
        SDL_Log("Failed to set normal image");
    }
    // m_clip.x = -1; //Force initialization : useful in android devices
    m_clip.w = m_spritesheet_image->w / column;
    m_clip.h = m_spritesheet_image->h / row;
    select_sprite(0,0);
    isContainsBg = false;
}

Spritesheet::~Spritesheet()
{
    if(m_spritesheet_image) SDL_FreeSurface(m_spritesheet_image);
    if(ninepbg && isContainsBg) SDL_FreeSurface(ninepbg);
}

void Spritesheet::select_sprite(int x, int y)
{
    if(m_clip.x == x*m_clip.w && m_clip.y == y*m_clip.h)
        return; //Already selected sprite, No need to change

    m_clip.x = x * m_clip.w;
    m_clip.y = y * m_clip.h;

    if(isContainsBg){
        srcX[0] = m_clip.x;
        srcX[1] = m_clip.x + left;
        srcX[2] = m_clip.x + m_clip.w - right;

        srcY[0] = m_clip.y;
        srcY[1] = m_clip.y + top;
        srcY[2] = m_clip.y+ m_clip.h - bottom;

        srcW[0] = left;
        srcW[1] = m_clip.w - right - left;
        srcW[2] = right;

        srcH[0] = top;
        srcH[1] = m_clip.h - bottom - top;
        srcH[2] = bottom;
    }
}
void Spritesheet::draw_selected_sprite(SDL_Surface* window_surface, SDL_Rect* position)
{
    if(isContainsBg){
        // draw_9patch_sprite(window_surface, position);
        SDL_BlitScaled(ninepbg, &m_clip, window_surface, position);
    }
    SDL_BlitScaled(m_spritesheet_image, &m_clip, window_surface, position);
}

void Spritesheet::setNinePatch(const char* loc, int top, int bottom, int left, int right, bool repeat){
    ninepbg = IMG_Load(loc);
    if(ninepbg == NULL){
        SDL_Log("Failed to set 9P backround");
        return;
    }
    isContainsBg = true;
    this->top = top;
    this->bottom = bottom;
    this->left = left;
    this->right = right;
    this->repeat = repeat;
}

//https://github.com/cxong/sdl2-9-slice/blob/master/main.c
inline void Spritesheet::draw_9patch_sprite(SDL_Surface *target, SDL_Rect* position)
{
    // int x = position->x;
    // int y = position->y;
    // int w = position->w;
    // int h = position->h;
    //
    // int dstX[] = {x, x + left, x + w - right, x + w};
    // int dstY[] = {y, y + top, y + h - bottom, y + h};
    // int dstW[] = {left, w - right - left, right};
    // int dstH[] = {top, h - bottom - top, bottom};
    // SDL_Rect src;
    // SDL_Rect dst;
    // for (int i = 0; i < 3; i++)
    // {
    //     src.x = srcX[i];
    //     src.w = srcW[i];
    //     dst.w = repeat ? srcW[i] : dstW[i];
    //     for (dst.x = dstX[i]; dst.x < dstX[i + 1]; dst.x += dst.w)
    //     {
    //         if (dst.x + dst.w > dstX[i + 1])
    //         {
    //             src.w = dst.w = dstX[i + 1] - dst.x;
    //         }
    //         // for (int j = 0; j < 3; j++)
    //         // {
    //         //     src.y = srcY[j];
    //         //     src.h = srcH[j];
    //         //     dst.h = repeat ? srcH[j] : dstH[j];
    //         //     // for (dst.y = dstY[j]; dst.y < dstY[j + 1]; dst.y += dst.h)
    //         //     // {
    //         //     //     // if (dst.y + dst.h > dstY[j + 1])
    //         //     //     // {
    //         //     //     //     src.h = dst.h = dstY[j + 1] - dst.y;
    //         //     //     // }
    //         //     //     // SDL_BlitSurface(ninepbg, &src, target, NULL);
    //         //     // }
    //         // }
    //     }
    // }
}

#endif
