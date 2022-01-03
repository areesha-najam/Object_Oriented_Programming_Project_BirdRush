#include "SDL.h"
#include "Text.hpp"
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <string>
#pragma once

class Scoreboard
{
    int scores[5]; 
    Text t;
    public:
    Scoreboard();
    void updateScore(int score);
    void writeText(SDL_Renderer* , TTF_Font* , SDL_Texture*);

};
