//Author: Zane Draper
//
//Purpose: Declare Player variables and functions
//
//******************************

#pragma once

#include <iostream>
#include <string>

using namespace std;

class Player
{
public:
	//Methods
	Player();
	Player(string name, char type);
	virtual ~Player();
	string getName() const;
	char getType() const;
	virtual void print();
	virtual bool operator==(const Player& other) const;
	virtual bool operator>(const Player& other) const;
	virtual bool operator<(const Player& other) const;

protected:
	//Variables
	string name;
	char type;
};

