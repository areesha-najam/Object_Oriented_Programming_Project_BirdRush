#include <SDL_mixer.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

struct Music
{
    //data members
    Mix_Music *bgMusic = NULL;     //backgroung sound
    Mix_Music *coinMusic = NULL;   //coin sound
    Mix_Music *healthMusic = NULL; //health sound
    Mix_Music *rockhit = NULL; //rock hit sound
    Mix_Music *pop = NULL; //poof sound
    Mix_Music *ouch = NULL; //poof sound
    Music();
    ~Music();  //delete pointers
    //plays music
    void playMusic(Mix_Music *m);

    
};
