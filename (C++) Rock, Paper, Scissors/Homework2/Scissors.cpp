//Author: Zane Draper
//
//Purpose: Instiate Scissors methods
//
//******************************

#include "Scissors.h"

//CONSTRUCTOR
Scissors::Scissors()
{
}

//CONSTRUCTOR - takes name
Scissors::Scissors(string name):
	Player(name, 's')
{
}

//Destructor
Scissors::~Scissors()
{
	cout << this->name << "'s Scissors are getting rusty!" << endl;
}

//PRINT
void Scissors::print() {
	cout << this->name << " (8>< Scissors)";
}

//Checks for similar type
bool Scissors::operator==(const Player& other) const {
	if (other.getType() == 's') {
		return true;
	}
	else return false;
}

//checks for loss
bool Scissors::operator>(const Player& other) const {
	if (other.getType() == 'p') {
		return true;
	}
	else return false;
}

//checks for win
bool Scissors::operator<(const Player& other) const {
	if (other.getType() == 'r') {
		return true;
	}
	else return false;
}