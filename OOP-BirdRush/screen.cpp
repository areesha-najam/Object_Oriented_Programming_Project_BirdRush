#include "screen.hpp"
#include <iostream>
using namespace std;
// int count = 0;
void Screen::drawObjects(SDL_Renderer *renderer, SDL_Texture *asst)
{

    gRenderer = renderer;
    assets = asst;

    SDL_RenderCopy(gRenderer, assets, NULL, &moverRect);
    SDL_RenderCopy(gRenderer, assets, NULL, &moverRect2);
    if (moverRect.x == -800)
    {
        moverRect.x = 800;
    }
    if (moverRect2.x == -800)
    {
        moverRect2.x = 800;
    }

    moverRect.x -= 20;
    moverRect2.x -= 20;

    count++;
    // if (count > 5)
    // {
    //     count = 0;
    // }
    // if (moverRect.x > 800)
    // {
    //     moverRect.x = 0;
    // }
    // if (moverRect.y > 500)
    // {
    //     moverRect.y = 200;
    // }
    // SDL_RenderCopy(gRenderer, assets, &srcRect1, &moverRect1);
    // SDL_RenderCopy(gRenderer, assets, &srcRect2, &moverRect2);
}