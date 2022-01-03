#include "Enemy.hpp"
// #include "SDL.h"

#pragma once
class Rock : public Enemy
{
    bool hit = false;
public:
    Rock();
    void drawObjects(SDL_Texture *texture, SDL_Renderer *renderer);
    void resetRock();
    
};