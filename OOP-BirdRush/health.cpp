#include "health.hpp"
#include "SDL.h"

Health::Health() : Collectables()
{
    src = {1139, 504, 138, 137};                             //for health
    mover = {(rand() % 1000) + 700, (rand() % 500), 30, 30}; //random x and y
}
