#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <SDL_ttf.h>

#include "bird.hpp"
#include "screen.hpp"
#include "StaticScreen.hpp"
#include "coin.hpp"
#include "health.hpp"
#include "Rock.hpp"
#include "eagle.hpp"
#include "Bomb.hpp"
#include "Text.hpp"
#include "Music.hpp"
#include "Scoreboard.hpp"
#include "poof.hpp"

class Game
{
    Screen S;
    StaticScreen P; //pause screen
    StaticScreen M; //menu screen
    StaticScreen O; //game over screen
    StaticScreen H; //How to play screen
    StaticScreen SB;  //Scoreboard screen.
    Scoreboard leaderboard;  

    Text text;
    int count = 0;

    SDL_Rect rect = {259, 178, 279, 78};  //rect on pause screen
    SDL_Rect rectM = {260, 169, 264, 72}; //rect on main menu screen
    SDL_Rect rect0 = {259, 267, 277, 75}; //rect on gameOver screen

    

    //Screen dimension constants
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    //The window we'll be rendering to
    SDL_Window *gWindow = NULL;

    //The window renderer
    SDL_Renderer *gRenderer = NULL;

    //Current displayed texture
    SDL_Texture *gTexture = NULL; //background screen
    SDL_Texture *pTexture = NULL; //pause screens
    SDL_Texture *mTexture = NULL; //menu screens
    SDL_Texture *hTexture = NULL;  //how to play screen
    SDL_Texture *oTexture = NULL;  //gameover screen
    SDL_Texture *sbTexture = NULL;  //scoreboard screen
    SDL_Texture *poofs = NULL;
    
    //global reference to png image sheets
    SDL_Texture *assets = NULL;
    Music music;
    //For text fonts
    TTF_Font *font;
    TTF_Font *font_gameover;

    int collectedCoins = 0;
    int collectedHealth = 100;
    SDL_Rect Black = {100, 30, 220, 30};
    SDL_Rect Red = {110, 35, 200, 20 };
    bool gameOverState = false;

public:
    Bird bird;             // Making Birds here
    list<Bomb *> bomb;     //making bomb here
    list<Coin *> coin;     //making coins here
    //Bomb bomb;
    list<Health *> health; //making health here
    Rock rock[4];
    list<Eagle *> eagle;

    // healths health[3]; // Making 3 health boosters here
    bool init();
    bool loadMedia();
    void close();
    void key(SDL_Event); //buttons functionality and bird movement.

    SDL_Texture *loadTexture(std::string path);
    void run();
    void makemove();
    void Game_implementation();         //implementing logic here
    void PauseScreen();                 //rendering pause screen (button functionality)
    void MenuScreen(); 
    void HowToPlayScreen(); 
    void GameOverScreen();              //rendering menu screen (button functionality)
    void ScoreboardScreen();
    bool Collision(SDL_Rect, SDL_Rect); //checks all collisions
    void drawAllObjects();  //drawing all object here
    void drawBomb();
    void drawCollectables();//drawing coin and health here
    void drawEnemies();  //drawing rocks and eagles here
    void destroyCoin();          //pick coin
    void destroyHealth();        //pick health 
    void collectCollectables();  //destroy collectables here
    void destroyEagle();         //destroy Eagle here upon collision
    void decreaseHealth();
    void NewGame();


    //keys function
    void birdKeys(SDL_Event e);
    void pauseKeys(SDL_Event e);
    void howToPlayKeys(SDL_Event e);
    void ScoreBoardKeys(SDL_Event e);
    void gameOverKeys(SDL_Event e);
    void MenuKeys(SDL_Event e);


};
