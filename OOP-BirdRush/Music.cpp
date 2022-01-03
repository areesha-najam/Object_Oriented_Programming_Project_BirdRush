#include "Music.hpp"
#include <iostream>
Music::Music()
{
    
}
Music::~Music()
{
	
    Mix_FreeMusic(bgMusic);
	bgMusic = NULL;
	Mix_FreeMusic(healthMusic);
	healthMusic = NULL;
	Mix_FreeMusic(coinMusic);
	coinMusic = NULL;
	Mix_FreeMusic(rockhit);
	rockhit = NULL;
	Mix_FreeMusic(pop);
	pop = NULL;
	Mix_FreeMusic(ouch);
	ouch = NULL;
}
void Music::playMusic(Mix_Music *m)
{
	Mix_PlayMusic(m, 1);
}
