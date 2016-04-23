//Author: Zane Draper
//
//Purpose: Declare Player methods
//
//******************************

#pragma once

#include "Player.h"

class Rock :
	public Player
{
public:
	//Methods
	Rock();
	Rock(string name);
	~Rock();
	void print();
	bool operator==(const Player& other) const;
	bool operator>(const Player& other) const;
	bool operator<(const Player& other) const;
};

