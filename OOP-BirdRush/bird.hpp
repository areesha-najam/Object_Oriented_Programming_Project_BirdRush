#include <SDL.h>
#include <iostream>
using namespace std;
class Bird
{
    bool move = false;
    SDL_Renderer *gRenderer;
    SDL_Texture *assets;
    int x;
    int y;
    int frame = 0;
    SDL_Rect src[4]; 
    SDL_Rect moverRect;

public:
    Bird(SDL_Renderer *renderer, SDL_Texture *asst) : gRenderer(renderer), assets(asst) {}
    Bird();
    Bird(int,int);

    void drawObjects(SDL_Renderer *renderer, SDL_Texture *asst);
    void makeMove(string Direction);
    SDL_Rect get_mover();
    void set_moverx(int x);
    void reset();
};