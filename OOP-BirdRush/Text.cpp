#include "Text.hpp"

Text::Text()
{
}

void Text::draw(SDL_Renderer *renderer, int x, int y, char *text, TTF_Font *font,SDL_Texture * tex)
{
    texture = tex;
    textColor = {0, 0, 255, 0};
    surface = TTF_RenderText_Solid(font, text, textColor);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    rect.x= x ;
    rect.y= y ;
    rect.w= surface->w;
    rect.h= surface->h;
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}