#include "coin.hpp"
#include "SDL.h"

Coin::Coin() : Collectables()
{
    src = {1119, 856, 151, 152};                             //for coins
    mover = {(rand() % 1000) + 800, (rand() % 500), 25, 25}; //random x and y
}
