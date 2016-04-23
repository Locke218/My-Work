//Author: Zane Draper
//
//Purpose: Instiate Player methods
//
//******************************

#include "Player.h"

//CONSTRUCTOR
Player::Player()
{
}

//CONSTRUCTOR - takes name and type
Player::Player(string name, char type)
{
	this->name = name;
	this->type = type;
}

//DESTRUCTOR
Player::~Player()
{
	cout << "Goodbye " << name << endl;
}

//return name
string Player::getName() const
{
	return this->name;
}

//return type
char Player::getType() const
{
	return this->type;
}


//VIRTUAL FUNCTIONS
void Player::print() {

}

bool Player::operator==(const Player& other) const {
	return true;
}

bool Player::operator>(const Player& other) const {
	return true;
}

bool Player::operator<(const Player& other) const {
	return true;
}
