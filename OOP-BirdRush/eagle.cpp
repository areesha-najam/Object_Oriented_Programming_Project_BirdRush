#include "eagle.hpp"
#include "SDL.h"

Eagle::Eagle() : Enemy()
{
    src[0] = {956, 1136, 434, 234};
    src[1] = {534, 1173, 408, 234};
    src[2] = {163, 1165, 283, 234};
    src[3] = {1007, 1705, 334, 234};
    src[4] = {585, 1639, 305, 269};
    src[5] = {117, 1659, 381, 234};
    mover.x = 900; //random x and y
    mover.y = 300;
    mover.w = 180;
    mover.h = 160;
}
void Eagle::drawObjects(SDL_Texture *texture, SDL_Renderer *renderer)
{
    Enemy::src = src[frame];
    Enemy::drawObjects(texture, renderer);
    mover.x -= 10;
    if (mover.y < 500 && mover.y > 50) //to be in middle of screen
        mover.y -= rand() % 5 + 1;
    frame++;
    if (frame == 6)
    {
        frame = 0;
    }
    if (mover.x < -100) //to bring eagle back once passed.
    {
        mover.x = rand() % 1200 + 900;
        mover.y = (rand() % 500);
        Enemy::setAttack(false);
    }
}
Eagle::Eagle(int x, int y)
{
  mover.y = y;
  mover.x = x;
   
}


