#include <SDL.h>
#include <iostream>
using namespace std;
//the objects of this class are in game.hpp as its data menbers. 
//handles gameover, menu, howtoplay and scoreboard screen.
class StaticScreen
{

    SDL_Renderer *gRenderer;
    SDL_Texture *assets;
    SDL_Rect moverRect;

public:
    StaticScreen(SDL_Renderer *renderer, SDL_Texture *asst) : gRenderer(renderer), assets(asst) {}
    StaticScreen();
    void drawObjects(SDL_Renderer *renderer, SDL_Texture *asst);
};