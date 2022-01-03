#include "Bomb.hpp"

Bomb::Bomb(){
    mover = { 100, 100, 30, 30};
    src={1128, 95, 171, 172};
}
//parametrized ctor
Bomb::Bomb(int x,int y){
    mover = { x, y, 30, 30};
    src={1128, 95, 171, 172};
    
}
SDL_Rect Bomb::getMover(){
    return mover;
}
void Bomb::draw( SDL_Renderer *renderer, SDL_Texture *assts){

    assets = assts;
    gRenderer = renderer;
    SDL_RenderCopy(renderer, assets , &src, &mover);
    mover.x += 20;
}
//check if bomb is out of screen or not
bool Bomb::permit()
{
    if (mover.x >= 800){
        return false;     
    }
    else
    {
        return true;
    }  
}