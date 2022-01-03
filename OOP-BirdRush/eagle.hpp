#include "Enemy.hpp"
// #include "SDL.h"
#pragma once
class Eagle : public Enemy
{
    SDL_Rect src[9]; // Getting eagle from the assests file
    int frame = 0;
    
public:
    Eagle();
    Eagle (int x, int y);
    void drawObjects(SDL_Texture *texture, SDL_Renderer *renderer);
    
};

