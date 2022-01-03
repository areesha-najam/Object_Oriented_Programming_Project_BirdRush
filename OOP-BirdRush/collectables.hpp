#include "SDL.h"
#pragma once
class Collectables
{
protected:
    SDL_Texture *assets;
    SDL_Rect src;
    SDL_Rect mover;
    SDL_Renderer *gRenderer;
public:
    Collectables();
    ~Collectables();
    void drawObjects(SDL_Texture *, SDL_Renderer *);
    SDL_Rect get_moverx();   //return x-cord 
};