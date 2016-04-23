//Author: Zane Draper
//
//Purpose: Instiate Paper methods
//
//******************************

#include "Paper.h"

//CONSTRUCTOR
Paper::Paper()
{
}

//CONSTRUCTOR - Takes name of object
Paper::Paper(string name):
	Player(name, 'p')
{
}

//DESTRUCTOR
Paper::~Paper()
{
	cout << this->name << "'s Paper is getting crumpled!" << endl;
}

//PRINT
void Paper::print() {
	cout << this->name << "( --- Paper)";
}

//checks for tie
bool Paper::operator==(const Player& other) const {
	if (other.getType() == 'p') {
		return true;
	}
	else return false;
}

//checks for loss
bool Paper::operator>(const Player& other) const {
	if (other.getType() == 'r') {
		return true;
	}
	else return false;
}

//checks for win
bool Paper::operator<(const Player& other) const {
	if (other.getType() == 's') {
		return true;
	}
	else return false;
}
