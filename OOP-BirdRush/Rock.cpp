#include "Rock.hpp"
#include "SDL.h"

Rock::Rock() : Enemy()
{
    src = {204, 718, 110, 108};                       //for rocks
    mover = {(rand() % 800), (rand() % 500)-500, 25, 25}; //random x and y
    
}
void Rock::drawObjects(SDL_Texture *texture, SDL_Renderer *renderer)
{
    Enemy::drawObjects(texture, renderer);
    mover.y += 15;
    if (mover.y >= 600) //to bring rock back once passed.
    {
        mover.y = 0;
        mover.x = rand() % 800;
        Enemy::setAttack(false);
    }
}

void Rock::resetRock(){
    mover = {(rand() % 800), (rand() % 500)-500, 25, 25}; //random x and y
}
