#ifndef PLAYER_H
#define PLAYER_H

#include "buildboard.h"

using namespace std;

class Player {
	friend class AI;

public:
	string location; //String to hold the location of the players move
	string name; //String to hold the name of the player
	string playerCharacter; //String to hold player character x OR o
	bool isWinner(); //Checks if the player has won
	void playerTurn(AI &ai, Buildboard &board); //Executes the move
private:
	vector < vector <string> > winningCombo = // Vector that holds vectors of winning combinations of locations
	{
		{ "A1", "B1", "C1" },
		{ "A1", "A2", "A3" },
		{ "B1", "B2", "B3" },
		{ "C1", "C2", "C3" },
		{ "A2", "B2", "C2" },
		{ "A3", "B3", "C3" },
		{ "A1", "B2", "C3" },
		{ "A3", "B2", "C1" }
	};
	tuple <bool, string> isValid;

};

#endif
