#include "poof.hpp"




poof::poof(SDL_Texture* texture)
{
    assets = texture;
    src[0] = {278,417,73,70};
    src[1] = {267,517,101,102};
    src[2] = {230,658,177,175};
    src[3] = {0,0,0,0};
    mover.x = rand() % 800;
    mover.y = mover.h = mover.w = 50;
    
}

SDL_Rect poof::getMover(){
    return mover;
}

poof::poof(SDL_Texture* texture, SDL_Rect rect): poof(texture){
    mover.x = rect.x;
    mover.y = rect.y;
}

void poof::draw(SDL_Renderer* renderer){

    SDL_RenderCopy(renderer, assets , &src[0], &mover);
    SDL_RenderCopy(renderer, assets , &src[3], &mover);
    SDL_RenderCopy(renderer, assets , &src[1], &mover);
    SDL_RenderCopy(renderer, assets , &src[3], &mover);
    SDL_RenderCopy(renderer, assets , &src[2], &mover);
    // frame++;
    // if (frame ==3)
    // {
    //     frame =0;
    // }
    
}