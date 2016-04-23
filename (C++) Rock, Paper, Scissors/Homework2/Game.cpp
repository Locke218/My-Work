//Author: Zane Draper
//
//Purpose: Instiate Games methods
//
//******************************

#include <iostream>
#include <time.h>

#include "Game.h"
#include "Paper.h"
#include "Rock.h"
#include "Scissors.h"

using namespace std;

//CONSTRUCTOR
Game::Game()
{
}

//DESTRUCTOR
Game::~Game()
{
	for (int i = 0; i < players.size(); i++) {
		delete players[i];
	}
	while(players.size() > 0)
		players.erase(players.begin());
	cout << "Game Over!!";
}

//Instatiates variables and get beinning user input
void Game::assemble()
{
	int playerNum = 0;
	cout << "Welcome to Rock, Paper, Scissors!" << endl;

	//Gets number of players from user
	while (playerNum < 2 || playerNum > 10) {
		cout << "Enter the number of players (2 - 10): ";
		cin >> playerNum;
		cin.ignore();
		if (playerNum < 2 || playerNum > 10) {
			cout << "Invalid choice. Please choose between 2 and 10 players." << endl;
		}
	}

	int random;
	srand(time(NULL));

	//Gets player names from user, assigns random state
	for (int i = 1; i <= playerNum; i++) {
		string temp = "";
		cout << "Enter the name of Player " << i << ": ";
		getline(cin, temp);

		random = rand() % 3 + 1;

		//assigns random type
		if (random == 1) players.push_back(new Rock(temp));
		else if (random == 2) players.push_back(new Paper(temp));
		else if (random == 3) players.push_back(new Scissors(temp));
	}
}

//Runs the main game loop
void Game::run()
{
	bool gameplay = true;

	//main game loop
	while (gameplay == true) {
		//if only 1 player left, winner
		if (players.size() == 1) {
			cout << "The winner is " << players[0]->getName() << endl;
			gameplay = false;
		}

		else {
			bool stalemate = true;
			char type = players[0]->getType();
			//checks for simlar type
			for (int i = 1; i < players.size(); i++) {
				if (players[i]->getType() != type) {
					stalemate = false;
				}
			}
			//if not same type
			if (stalemate == false) {
				cout << endl;
				//players choice for battle
				cout << "* Which players would you like to battle each other (1.." << players.size() << ")? " << endl;

				int temp1 = 0;
				int temp2 = 0;

				//gets player choice, checks for incorrect input
				while (temp1 < 1 || temp1 > players.size()) {
					cout << "Opponent 1: ";
					cin >> temp1;
					if (temp1 < 1 || temp1 > players.size()) {
						cout << "Incorrect entry" << endl;
					}
				}
				while (temp2 < 1 || temp2 > players.size()) {
					cout << "Opponent 2: ";
					cin >> temp2;
					if (temp2 < 1 || temp2 > players.size()) {
						cout << "Incorrect entry" << endl;
					}
				}
				temp1 -= 1;
				temp2 -= 1;

				//checks possible outcomes for battle
				if (*(players[temp1]) > *(players[temp2])) {
					cout << endl;
					players[temp1]->print();
					cout << " beats ";
					players[temp2]->print();
					cout << endl;
					delete players[temp2];
					players.erase(players.begin() + temp2);
				}
				else if (*(players[temp1]) < *(players[temp2])) {
					cout << endl;
					players[temp2]->print();
					cout << " beats ";
					players[temp1]->print();
					cout << endl;
					delete players[temp1];
					players.erase(players.begin() + temp1);
				}
				else if (*(players[temp1]) == *(players[temp2])) {
					players[temp1]->print();
					cout << " ties ";
					players[temp2]->print();
					cout << endl;
				}

			}
			//if all players have same type
			else {
				cout << "The game has ended in stalemate. There are no winners!" << endl;
				cout << "\n" << endl;
				gameplay = false;
			}
		}

		//repeat game, checks for correct input
		if (gameplay == true) {
			char cont = 'l';
			while (cont != 'y' && cont != 'n') {
				cout << endl;
				cout << "Would you like to play again (y/n)? ";
				cin >> cont;
				cout << endl;
			}
			if (cont == 'n') gameplay = false;
		}
	}
}

