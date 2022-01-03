#include "SDL.h"
#pragma once

class Bomb
{
    protected:
    SDL_Texture *assets;
    SDL_Rect src;
    SDL_Rect mover;
    SDL_Renderer *gRenderer;
    bool can_shoot = true;

    

public:
    Bomb();
    Bomb(int,int);
    void draw(SDL_Renderer *, SDL_Texture* );
    SDL_Rect getMover();
    bool permit();

};
