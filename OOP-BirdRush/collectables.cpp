#include "collectables.hpp"

Collectables::Collectables()
{
}
Collectables::~Collectables()
{
}

void Collectables::drawObjects(SDL_Texture *texture, SDL_Renderer *renderer)
{
    assets = texture;
    gRenderer = renderer;
    SDL_RenderCopy(renderer, assets, &src, &mover);
    mover.x -= 20;
    if (mover.x <= 0) //to bring object back once passed.
    {
        mover.x = (rand() % 1300) + 1000;
        mover.y = rand() % 500;
    }
}
SDL_Rect Collectables::get_moverx()
{
    return mover;
}

