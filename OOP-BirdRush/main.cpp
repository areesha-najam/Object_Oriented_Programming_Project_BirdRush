#include "game.hpp"
#include <SDL.h>

int main(int argc, char **argv){
    Game game;
    srand(time(NULL));
    if( !game.init() ){
		printf( "Failed to initialize!\n" );
        return 0;
	}
	//Load media
    if( !game.loadMedia() ){
        printf( "Failed to load media!\n" );
        return 0;
    }
    game.run();
    //Main loop flag
    game.close();
    return 0;
}