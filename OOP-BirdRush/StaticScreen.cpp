#include "StaticScreen.hpp"
#include <iostream>
using namespace std;
void StaticScreen::drawObjects(SDL_Renderer *renderer, SDL_Texture *asst)
{

    gRenderer = renderer;
    assets = asst;
    SDL_RenderCopy(gRenderer, assets, NULL, &moverRect);
}
StaticScreen::StaticScreen()
{
    moverRect = {0, 0, 800, 600};
}