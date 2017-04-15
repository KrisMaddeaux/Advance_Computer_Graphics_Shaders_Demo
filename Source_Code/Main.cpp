
#include "game.h"

game *myGame;


//The is the starting point of the program
int main()
{
	myGame = new game();

	myGame->runGame();

	delete myGame;

    return EXIT_SUCCESS;
}



