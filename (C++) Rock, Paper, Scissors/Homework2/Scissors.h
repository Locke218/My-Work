//Author: Zane Draper
//
//Purpose: Declare Scissors methods
//
//******************************

#pragma once

#include "Player.h"

class Scissors :
	public Player
{
public:
	//Methods
	Scissors();
	Scissors(string name);
	~Scissors();
	void print();
	bool operator==(const Player& other) const;
	bool operator>(const Player& other) const;
	bool operator<(const Player& other) const;
};

