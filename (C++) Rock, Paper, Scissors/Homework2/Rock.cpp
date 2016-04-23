//Author: Zane Draper
//
//Purpose: Instiate Rocks methods
//
//******************************

#include "Rock.h"

//CONSTRUCTOR
Rock::Rock()
{
}

//CONSTRUCTOR - takes name
Rock::Rock(string name):
	Player(name, 'r')
{
}

//DESTRUCTOR
Rock::~Rock()
{
	cout << getName() << "'s Rock is pretty heavy!" << endl;
}

//PRINT
void Rock::print() {
	cout << getName() << " (O Rock)";
}

//checks for tie
bool Rock::operator==(const Player& other) const {
	if (other.getType() == 'r') {
		return true;
	}
	else return false;
}

//checks for win
bool Rock::operator>(const Player& other) const {
	if (other.getType() == 's') {
		return true;
	}
	else return false;
}

//checks for loss
bool Rock::operator<(const Player& other) const {
	if (other.getType() == 'p') {
		return true;
	}
	else return false;
}
