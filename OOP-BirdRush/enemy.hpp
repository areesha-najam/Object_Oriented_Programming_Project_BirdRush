#include "SDL.h"
#pragma once
class Enemy
{
protected:
    SDL_Texture *assets;
    SDL_Rect src;
    SDL_Rect mover;
    SDL_Renderer *gRenderer;
    bool attack = false;

public:
    Enemy();
    virtual void drawObjects(SDL_Texture *texture, SDL_Renderer *renderer);
    SDL_Rect getMover();
    bool Attack();
    void setAttack(bool);
};