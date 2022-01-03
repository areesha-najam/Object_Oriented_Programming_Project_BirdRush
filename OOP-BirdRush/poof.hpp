
#pragma once

#include "SDL.h"
#pragma once
// #define fps 60
class poof
{
    SDL_Rect src[4];
    int frame = 0;
    SDL_Texture* assets;
    SDL_Rect mover;
    
    public:
    SDL_Rect getMover();
    poof(SDL_Texture*); 
    poof(SDL_Texture*, SDL_Rect);  //sets position of poof as per eagle rect
    void draw(SDL_Renderer*);
};