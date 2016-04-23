//Author: Zane Draper
//
//Purpose: Declare Paper methods
//
//******************************

#pragma once

#include "Player.h"

class Paper :
	public Player
{
public:
	//Methods
	Paper();
	Paper(string name);
	~Paper();
	void print();
	bool operator==(const Player& other) const;
	bool operator>(const Player& other) const;
	bool operator<(const Player& other) const;
};

