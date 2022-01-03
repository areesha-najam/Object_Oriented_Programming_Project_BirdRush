#include <stdlib.h>
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#pragma once
//
class Text
{
    int text_width;
    int text_height;
    SDL_Surface *surface;
    SDL_Color textColor;
    SDL_Texture *texture;
    SDL_Rect rect;

public:
    Text();
    //draw text on given coordinates of font (specified in game.cpp).
    void draw(SDL_Renderer *renderer, int x, int y, char *text, TTF_Font *font, SDL_Texture *tex);
};