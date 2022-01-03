#include "bird.hpp"
#include <iostream>
using namespace std;
Bird::Bird()
{
    //initializing different frames of the player bird
    src[0] = {166, 52, 243, 170};
    src[1] = {448, 91, 252, 152};
    src[2] = {165, 384, 243, 181};
    src[3] = {448, 385, 243, 181};

    moverRect = {0, 100, 100, 75}; 
}


void Bird::reset(){
    moverRect = {0, 100, 100, 75}; 
}

void Bird::drawObjects(SDL_Renderer *renderer, SDL_Texture *asst)
{
    gRenderer = renderer;
    assets = asst;
    SDL_RenderCopy(gRenderer, assets, &(src[frame]), &moverRect);
    frame++;
    if (frame == 4)
    {
        frame = 0;
    }
}
//moving upon user input
void Bird::makeMove(string direction)
{
    if (direction == "up" && moverRect.y > 0)
    {
        moverRect.y -= 20;
    }
    if (direction == "down" && moverRect.y < 500)
    {
        moverRect.y += 20;
    }
    if (direction == "left" && moverRect.x > 0)
    {
        moverRect.x -= 20;
    }
    if (direction == "right" && moverRect.x < 700)
    {
        moverRect.x += 20;
    }
}
SDL_Rect Bird::get_mover()
{
    return moverRect;
}
void Bird::set_moverx(int x)
{
    moverRect.x = x;
}
