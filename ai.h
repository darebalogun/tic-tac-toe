#include <iostream>
#include <string>
#include <Windows.h>
#include <algorithm>
#include <vector>
#include <tuple>
#include <stdlib.h>
#include "buildboard.h"
#include "player.h"
#ifndef AI_H
#define AI_H

using namespace std;

class AI { // AI class is similar to player class but has access to the players moves as well.
public:
	string move; // Holds the move the AI is currently considering
	string playerCharacter; //Holds the character of the AI. x OR o
	void playerTurn(Buildboard &board); //Similar to the playerTurn function in the player class
	bool isWinner(); //Checks if the AI has won the game
	void win(); //AI attempts to win the game
	void block(Player &player, Buildboard &board); //AI attempts to block the player from winning
	void fork(Buildboard &board); //AI creates a fork for itself (creates two opportunities to win)
	void blockOpponentFork(Player &player, Buildboard &board); //Blocks the opponents fork
	void centre(Buildboard &board); // Plays in the centre of the board
	void oppositeCorner(vector <string> playerMoves, Buildboard &board); //Plays on a corner opposite to where the player has played
	void emptyCorner(Buildboard &board); //Plays on an empty corner
	void emptySide(Buildboard &board); //Plays on an empty side
	void randomMove(Buildboard &board); //Plays a completely pseudorandom move

private:
	vector < vector <string> > winningCombo = //vector of vectors that hold all possible winning combinations
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
