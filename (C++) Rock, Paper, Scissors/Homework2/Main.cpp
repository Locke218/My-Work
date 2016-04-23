//Author: Zane Draper
//
//Purpose: Instantiate and run game
//
//******************************

#include <iostream>
#include <string>
#include <vector>
#include <time.h>

#include "Game.h"
#include "Player.h"
#include "Paper.h"
#include "Rock.h"
#include "Scissors.h"

using namespace std;

int main() {

	//creates game
	Game game;

	//initializes and runs game loop
	game.assemble();
	game.run();
	
	//Delete game;

	game.~Game();

	//pause game at end
	cin.ignore();
	cin.get();

}