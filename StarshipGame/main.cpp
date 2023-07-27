#include <iostream>
#include "Game.h"

using namespace std;

int main()
{
	Game game; // creates game object

	while (game.running())  // main loop of the game
	{
		game.pollEvents(); // event handling
		game.update();	// updates all game objects
		game.render(); // renders all game objects
	}

	return 0;
}