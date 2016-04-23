//Author: Zane Draper
//
//Purpose: Declare games methods
//
//******************************

#pragma once

#include <vector>
#include "Player.h"

class Game
{
public:
	//Methods
	Game();
	~Game();
	void assemble();
	void run();

protected:
	//Variables
	vector<Player*> players;
};

