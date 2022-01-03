#include <SDL.h>
#include <iostream>
using namespace std;
class Screen
{

    SDL_Renderer *gRenderer;
    SDL_Texture *assets;
    int x;
    int y;
    int count = 0;
    // pigeonSrc represents pigeon's rectangle in assets file.
    SDL_Rect Array; // 3 different animations stored in this Array.

    SDL_Rect srcRect = {0, 0, 626, 410}; // Getting the bird from the assests file
    

    SDL_Rect moverRect;
    SDL_Rect moverRect2;

public:
    Screen(SDL_Renderer *renderer, SDL_Texture *asst) : gRenderer(renderer), assets(asst) {}
    Screen()
    {
        Array = srcRect; // Adding bird picture in array.
        

        // Array[3] = srcRect1;
        // x = (rand() % 800) + 1;        //Getting Randomn Positions of x and y And declearing them in the constructor
        // y = (rand() % 600) + 1;
        moverRect = {0, 0, 800, 600}; // This will place the pigeon randomly in the screen with the randomn x and y
        moverRect2 = {800, 0, 800, 600};
    }
    void drawObjects(SDL_Renderer *renderer, SDL_Texture *asst);
};