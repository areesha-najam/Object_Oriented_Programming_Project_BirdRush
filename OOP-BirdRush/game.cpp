#include "game.hpp"
#include <limits>
#include <SDL.h>
int delay = 125;
bool pause = false;
bool menu = true;
bool drop_bomb = false;
bool HowToPlay = false;
bool scoreBoard = false;
bool quit = false;

bool Game::init()
{

	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Bird Rush", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
				TTF_Init();
				font = TTF_OpenFont("OpenSans-ExtraBold.ttf", 24);
				font_gameover = TTF_OpenFont("OpenSans-ExtraBold.ttf", 40);
			}
		}
	}

	return success;
}

bool Game::loadMedia()
{
	//Loading success flag
	bool success = true;
	assets = loadTexture("assets.png");
	poofs = loadTexture("poof.png");
	hTexture = loadTexture("How_to_play.jpeg");
	oTexture = loadTexture("GameOver.jpeg");
	gTexture = loadTexture("background.jpg");
	pTexture = loadTexture("Pause.png");
	mTexture = loadTexture("Menu.jpeg");
	sbTexture = loadTexture("Scoreboard.jpeg");

	if (assets == NULL || gTexture == NULL)
	{
		printf("Unable to run due to error: %s\n", SDL_GetError());
		success = false;
	}
	music.bgMusic = Mix_LoadMUS("GameBeat.mpeg");
	music.ouch = Mix_LoadMUS("EagleCollision.mpeg");
	music.coinMusic = Mix_LoadMUS("Coin.mp3");
	music.healthMusic = Mix_LoadMUS("HealthMusic.mpeg");
	music.rockhit = Mix_LoadMUS("RockHit.mp3");
	music.pop = Mix_LoadMUS("Pop.mp3");

	if (music.bgMusic == NULL)
	{
		printf("Unable to load music: %s \n", Mix_GetError());
		success = false;
	}
	if (music.ouch == NULL)
	{
		printf("Unable to load music: %s \n", Mix_GetError());
		success = false;
	}
	if (music.rockhit == NULL)
	{
		printf("Unable to load music: %s \n", Mix_GetError());
		success = false;
	}
	if (music.pop == NULL)
	{
		printf("Unable to load music: %s \n", Mix_GetError());
		success = false;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	return success;
}

void Game::close()
{
	//Free loaded images
	SDL_DestroyTexture(assets);
	assets = NULL;
	SDL_DestroyTexture(poofs);
	poofs = NULL;
	SDL_DestroyTexture(gTexture);
	SDL_DestroyTexture(pTexture);
	SDL_DestroyTexture(mTexture);
	SDL_DestroyTexture(hTexture);
	SDL_DestroyTexture(oTexture);
	SDL_DestroyTexture(sbTexture);
	TTF_CloseFont(font);
	TTF_CloseFont(font_gameover);
	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	//dynamic memory deletion.
	for (auto E = eagle.begin(); E != eagle.end(); E++)
	{
		delete (*E);
		eagle.erase(E--);
	}
	for (auto C = coin.begin(); C != coin.end(); C++)
	{
		delete (*C);
		coin.erase(C--);
	}
	for (auto H = health.begin(); H != health.end(); H++)
	{
		delete (*H);
		health.erase(H--);
	}
	for (auto B = bomb.begin(); B != bomb.end(); B++)
	{
		delete (*B);
		bomb.erase(B--);
	}
	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}
SDL_Texture *Game::loadTexture(std::string path)
{
	//The final texture
	SDL_Texture *newTexture = NULL;
	//Load image at specified path
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}
void Game::birdKeys(SDL_Event e)
{
	if (e.type == SDL_KEYDOWN && pause == false && menu == false && HowToPlay == false && scoreBoard == false && gameOverState == false)
	{
		SDL_Keycode key = e.key.keysym.sym;
		string direction = "";
		if (key == SDLK_p) //KEY P pressed to pause game
			pause = true;
		if (key == SDLK_SPACE && drop_bomb == false) //dropping bomb
			drop_bomb = true;
		if (key == SDLK_UP)
		{
			direction = "up";
			bird.makeMove(direction);
		}
		if (key == SDLK_DOWN)
		{
			direction = "down";
			bird.makeMove(direction);
		}
		if (key == SDLK_RIGHT)
		{
			direction = "right";
			bird.makeMove(direction);
		}
		if (key == SDLK_LEFT)
		{
			direction = "left";
			bird.makeMove(direction);
		}
	}
}
void Game::NewGame()
{
	bird.reset();
	for (auto E = eagle.begin(); E != eagle.end(); E++)
	{
		delete (*E);
		eagle.erase(E--);
	}
	for (auto C = coin.begin(); C != coin.end(); C++)
	{
		delete (*C);
		coin.erase(C--);
	}
	for (auto H = health.begin(); H != health.end(); H++)
	{
		delete (*H);
		health.erase(H--);
	}
	for (auto B = bomb.begin(); B != bomb.end(); B++)
	{
		delete (*B);
		bomb.erase(B--);
	}
	for (int i = 0; i < 4; i++)
	{
		rock[i].resetRock();
	}
	collectedHealth = 100;
	Red.w = 200;
	collectedCoins = 0;
	pause = false;
	HowToPlay = false;
	menu = false;
	scoreBoard = false;
	gameOverState = false;
	drop_bomb = false;
}
void Game::howToPlayKeys(SDL_Event e)
{
	if (e.type == SDL_KEYDOWN && pause == false && menu == false && HowToPlay == true && scoreBoard == false)
	{
		SDL_Keycode key = e.key.keysym.sym;
		if (key == SDLK_ESCAPE)
		{
			menu = true;
			pause = false;
			HowToPlay = false;
			scoreBoard = false;
		}
		if (key == SDLK_RIGHT)
		{
			menu = false;
			scoreBoard = false;
			pause = false;
			HowToPlay = false;
		}
	}
}
void Game::pauseKeys(SDL_Event e)
{
	if (e.type == SDL_KEYDOWN && pause == true && menu == false && HowToPlay == false && scoreBoard == false)
	{
		SDL_Keycode key = e.key.keysym.sym;
		if (key == SDLK_DOWN && rect.y < 356 && count < 2)
		{
			rect.y += 89;

			if (count < 2)
				count++;
		}
		else if (key == SDLK_UP && rect.y > 178 && count > 0)
		{
			rect.y -= 89;
			if (count > 0)
				count--;
		}
		else if (key == SDLK_RETURN) //ENTER KEY PRESSED
		{
			rect.y = 178;
			if (count == 0)
			{ //resume button
				pause = false;
				HowToPlay = false;
				menu = false;
				scoreBoard = false;
			}
			else if (count == 1)
				NewGame();
			else if (count == 2)
			{
				//if exit selected return to mainmenu
				menu = true;
				pause = false;
			}
			count = 0;
		}
	}
}
void Game::ScoreBoardKeys(SDL_Event e)
{
	if (e.type == SDL_KEYDOWN && pause == false && menu == false && HowToPlay == false && scoreBoard == true)
	{
		SDL_Keycode key = e.key.keysym.sym;
		if (key == SDLK_ESCAPE)
		{
			menu = true;
			pause = false;
			HowToPlay = false;
			scoreBoard = false;
		}
	}
}
void Game::gameOverKeys(SDL_Event e)
{
	if (e.type == SDL_KEYDOWN && pause == true && menu == true && HowToPlay == true && gameOverState == true && scoreBoard == false)
	{
		SDL_Keycode key = e.key.keysym.sym;
		if (key == SDLK_DOWN && count < 2)
		{
			if (count == 0)
			{
				rect0.y = 356; //moves to second option
				count++;
			}
			else if (count == 1)
			{
				rect0.y = 445;
				count++;
			}
		}
		else if (key == SDLK_UP && count >= 0)
		{
			if (count == 2)
			{
				rect0.y = 356; //moves to second option
				count--;
			}
			else if (count == 1)
			{
				rect0.y = 267;
				count--;
			}
		}
		else if (key == SDLK_RETURN) //ENTER KEY PRESSED
		{
			rect0.y = 267; //initial rect.y
			if (count == 0)
				NewGame();
			else if (count == 1)
			{
				//SCORE BOARD DISPLAY KARAOO
				pause = false;
				menu = false;
				HowToPlay = false;
				scoreBoard = true;
				count = 0;
			}
			else if (count == 2)
			{
				menu = true;
				pause = false;
				HowToPlay = false;
				gameOverState = false;

				count = 0;
			}
		}
	}
}
void Game::key(SDL_Event e)
{
	//BIRD MOVEMENT
	birdKeys(e);
	//HOW TO PLAY SCREEN
	howToPlayKeys(e);
	//Score board screen
	ScoreBoardKeys(e);
	//PAUSE SCREEN
	pauseKeys(e);
	//Gameover SCREEN
	gameOverKeys(e);
}
bool Game::Collision(SDL_Rect A, SDL_Rect B) // Code for Collision
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;
	//Calculate the sides of rect A
	leftA = A.x;
	rightA = A.x + A.w;
	topA = A.y;
	bottomA = A.y + A.h;
	//Calculate the sides of rect B
	leftB = B.x;
	rightB = B.x + B.w;
	topB = B.y;
	bottomB = B.y + B.h;
	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}
	if (topA >= bottomB)
	{
		return false;
	}
	if (rightA <= leftB)
	{
		return false;
	}
	if (leftA >= rightB)
	{
		return false;
	}
	//If none of the sides from A are outside B
	return true;
}
void Game::drawCollectables()
{
	if (coin.size() < 10)
		coin.push_back(new Coin());
	if (health.size() < 1)
		health.push_back(new Health());
	for (auto C : coin)
	{
		C->drawObjects(assets, gRenderer);
	}
	for (auto H : health)
	{
		H->drawObjects(assets, gRenderer);
	}
}
void Game::drawEnemies()
{

	if (eagle.size() < 1)
		eagle.push_back(new Eagle());

	for (auto E : eagle)
	{
		E->drawObjects(assets, gRenderer);
	}

	for (int i = 0; i < 4; i++)
	{
		rock[i].drawObjects(assets, gRenderer);
	}
}
void Game::drawBomb()
{
	bool permit;
	if (drop_bomb == true)
	{
		if (bomb.size() < 1)
			bomb.push_back(new Bomb(bird.get_mover().x, bird.get_mover().y));
		for (auto B : bomb) //drawing bombs on screen
		{
			B->draw(gRenderer, assets);
			permit = B->permit();
		}
		if (permit == false)
		{
			for (auto B = bomb.begin(); B != bomb.end(); B++)
			{
				delete (*B);
				bomb.erase(B--);
			}
			drop_bomb = false;
		}
	}
}
void Game::drawAllObjects()
{
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
	SDL_RenderClear(gRenderer);
	S.drawObjects(gRenderer, gTexture); //gaming screen
	text.draw(gRenderer, 10, 30, "Health : ", font, gTexture);
	text.draw(gRenderer, 10, 0, "Coin Score : ", font, gTexture);
	bird.drawObjects(gRenderer, assets); //bird
	drawCollectables();					 //coin/health
	drawEnemies();						 //rocks/Eagle
	drawBomb();
	//Bomb
}
void Game::collectCollectables()
{
	//Destroy and Collect Coins if colliding with bird
	for (auto C = coin.begin(); C != coin.end(); C++)
	{
		SDL_Rect C_mover = (*C)->get_moverx(); //to get the coin movements
		if (Collision(bird.get_mover(), C_mover) == true)
		{
			collectedCoins++;
			delete (*C);
			coin.erase(C--);
			music.playMusic(music.coinMusic);
			break;
		}
	}
	//Destroy and Collect Health if colliding with bird
	for (auto H = health.begin(); H != health.end(); H++)
	{
		SDL_Rect H_mover = (*H)->get_moverx(); //to get the coin movements
		if (Collision(bird.get_mover(), H_mover) == true)
		{
			if (collectedHealth <= 90)
			{
				collectedHealth += 10;
				Red.w += 20;
			}
			delete (*H);
			health.erase(H--);
			music.playMusic(music.healthMusic);
			break;
		}
	}
}
void Game::destroyEagle()
{
	for (auto B = bomb.begin(); B != bomb.end(); B++)
	{
		for (auto E = eagle.begin(); E != eagle.end(); E++)
		{
			SDL_Rect B_mover = (*B)->getMover(); //Gets bomb's location
			SDL_Rect E_mover = (*E)->getMover(); //Gets bomb's location
			E_mover.x = E_mover.x + 50;
			E_mover.y = E_mover.y + 30;
			if (Collision(B_mover, E_mover) == true)
			{
				poof p(poofs, E_mover);
				delete (*B);
				bomb.erase(B--);
				// shoot = false;
				delete (*E);
				eagle.erase(E--);
				p.draw(gRenderer);
				p.draw(gRenderer);
				p.draw(gRenderer);
				music.playMusic(music.pop);
				drop_bomb = false;
				break;
			}
		}
	}
}
void Game::decreaseHealth()
{
	for (int i = 0; i < 4; i++)
	{
		SDL_Rect R_mover = rock[i].getMover();
		if (Collision(bird.get_mover(), R_mover) == true && rock[i].Attack() == false)
		{
			collectedHealth -= 30;
			Red.w -= 60;
			rock[i].setAttack(true);
			music.playMusic(music.rockhit);
			break;
		}
	}
	//Decrease Health by 3 if Bird and Eagle collide
	for (auto E = eagle.begin(); E != eagle.end(); E++)
	{
		SDL_Rect E_mover = (*E)->getMover();
		E_mover.x = E_mover.x - 20;
		if (Collision(bird.get_mover(), E_mover) == true && (*E)->Attack() == false)
		{
			collectedHealth -= 30;
			Red.w -= 60;
			(*E)->setAttack(true);
			music.playMusic(music.ouch);
			break;
		}
	}
}
void Game::Game_implementation()
{
	if (pause == false && menu == false && HowToPlay == false && scoreBoard == false && gameOverState == false)
	{
		delay = 100;
		//returning from pause screen.
		if (Mix_PausedMusic() == 1)
			//Resume the music
			Mix_ResumeMusic();

		//********draw the objects here*******

		drawAllObjects();
		if (Mix_PlayingMusic() == 0)
			//Play the music
			music.playMusic(music.bgMusic);

		//*******destroy collectables here *******

		collectCollectables(); //destroy coin and health coins
		//Destroy Eagle if bomb collides
		destroyEagle();
		//decrease helath on collision with rock/Eagle
		decreaseHealth();
		if (collectedHealth <= 0)
		{
			collectedHealth = 0;
			gameOverState = true;
			pause = true;
			HowToPlay = true;
			menu = true;
			leaderboard.updateScore(collectedCoins);
		}
		else
		{
			string coinCount = to_string(collectedCoins);
			char *charCoins = (char *)coinCount.c_str();
			text.draw(gRenderer, 200, 0, charCoins, font, gTexture);
		}
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255); //borders
		SDL_RenderDrawRect(gRenderer, &Black);			 //draw rect
		SDL_RenderFillRect(gRenderer, &Black);			 //fill colour

		SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255); //borders
		SDL_RenderDrawRect(gRenderer, &Red);			   //draw rect
		SDL_RenderFillRect(gRenderer, &Red);			   //fill colour
	}
}
void Game::PauseScreen()
{
	if (pause == true && menu == false && HowToPlay == false)
	{
		delay = 200;
		Mix_PauseMusic();
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);
		SDL_RenderClear(gRenderer);
		P.drawObjects(gRenderer, pTexture);
		SDL_SetRenderDrawColor(gRenderer, 100, 0, 100, 50);			//borders
		SDL_RenderDrawRect(gRenderer, &rect);						//draw rect
		SDL_RenderFillRect(gRenderer, &rect);						//fill colour
		SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND); //blend COLOUR
																	// SDL_RenderPresent(gRenderer);
	}
}

void Game::GameOverScreen()
{
	if (pause == true && menu == true && HowToPlay == true && gameOverState == true && scoreBoard == false)
	{

		delay = 50;
		Mix_PauseMusic();
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);
		SDL_RenderClear(gRenderer);
		O.drawObjects(gRenderer, oTexture);
		SDL_SetRenderDrawColor(gRenderer, 100, 0, 100, 50);			//borders
		SDL_RenderDrawRect(gRenderer, &rect0);						//draw rect
		SDL_RenderFillRect(gRenderer, &rect0);						//fill colour
		SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND); //blend COLOUR
		string coinCount = to_string(collectedCoins);
		char *charCoins = (char *)coinCount.c_str();
		text.draw(gRenderer, 400, 180, charCoins, font_gameover, oTexture);
	}
}
void Game::ScoreboardScreen()
{
	if (pause == false && menu == false && HowToPlay == false && scoreBoard == true)
	{
		delay = 50;
		Mix_PauseMusic();
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);
		SDL_RenderClear(gRenderer);
		SB.drawObjects(gRenderer, sbTexture);
		leaderboard.writeText(gRenderer, font_gameover, sbTexture);
	}
}
void Game::HowToPlayScreen()
{
	if (pause == false && menu == false && HowToPlay == true)
	{

		delay = 50;
		Mix_PauseMusic();
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);
		SDL_RenderClear(gRenderer);
		H.drawObjects(gRenderer, hTexture);
	}
}
void Game::MenuScreen()
{
	if (menu == true && pause == false && HowToPlay == false && scoreBoard == false)
	{
		delay = 50;
		Mix_PauseMusic();
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);
		SDL_RenderClear(gRenderer);
		M.drawObjects(gRenderer, mTexture);
		SDL_SetRenderDrawColor(gRenderer, 100, 0, 100, 50);			//borders
		SDL_RenderDrawRect(gRenderer, &rectM);						//draw rect
		SDL_RenderFillRect(gRenderer, &rectM);						//fill colour
		SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND); //blend COLOUR
																	// SDL_RenderPresent(gRenderer);
	}
}
void Game::MenuKeys(SDL_Event e)
{
	SDL_Keycode key = e.key.keysym.sym;
	if (key == SDLK_DOWN && rectM.y < 356 && count < 3)
	{
		rectM.y += 89;
		if (count < 3)
			count++;
	}
	else if (key == SDLK_UP && rectM.y > 178 && count > 0)
	{
		rectM.y -= 89;
		if (count > 0)
			count--;
	}
	else if (key == SDLK_RETURN)
	{

		rectM.y = 169;
		if (count == 0) //start new game
		{
			NewGame();
		}
		else if (count == 1) //How to play screen
		{
			pause = false;
			menu = false;
			HowToPlay = true;
			count = 0;
		}
		else if (count == 2) //display score board
		{
			pause = false;
			menu = false;
			HowToPlay = false;
			scoreBoard = true;
			count = 0;
		}
		else if (count == 3) //exit selected on main menu
		{
			quit = true;
			count = 0;
		}
	}
}
void Game::run()
{

	SDL_Event e;
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			if (e.type == SDL_KEYDOWN && pause == false && menu == true && HowToPlay == false && scoreBoard == false)
			{
				MenuKeys(e);
			}
			key(e);
		}
		//game logic
		Game_implementation();
		HowToPlayScreen();
		PauseScreen();
		GameOverScreen();
		ScoreboardScreen();
		MenuScreen();
		SDL_RenderPresent(gRenderer);
		SDL_Delay(delay); //causes sdl engine to delay for specified miliseconds
	}
}