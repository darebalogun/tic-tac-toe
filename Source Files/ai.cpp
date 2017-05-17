#include <iostream>
#include <string>
#include <Windows.h>
#include <algorithm>
#include <vector>
#include <tuple>
#include <stdlib.h>
#include "ai.h"
#include "buildboard.h"
#include "player.h"

using namespace std;

/* validMove takes a string and a vector of strings and returns the same string and true if
 the string is in the vector and false if it is not. Function is used to check if tic-tac-toe move is valid
*/
static tuple <bool, string> validMove(string move, vector<string> location) {
	for (int i = 0; i < location.size(); i++) {
		if (move.compare(location[i]) == 0) {
			tuple <bool, string> foo{ true, location[i] };
			return foo;
		}
	}
	tuple <bool, string> foo{ false, "invalid" };
	return foo;
}

//Plays a random move by picking a pseudo random number within the range of values in the valid locations vector
void AI::randomMove(Buildboard &board) {
	int i = rand() % board.validLocations.size();
	move = board.validLocations[i];
}

//Plays an empty side by checking if any of the 4 sides are on the valid moves list
void AI::emptySide(Buildboard &board) {
	for (int i = 0; i < board.validLocations.size(); i++) {
		if (board.validLocations[i].compare("A2")) {
			move = board.validLocations[i];
		}
		else if (board.validLocations[i].compare("B1")) {
			move = board.validLocations[i];
		}
		else if (board.validLocations[i].compare("B3")) {
			move = board.validLocations[i];
		}
		else if (board.validLocations[i].compare("C2")) {
			move = board.validLocations[i];
		}
	}
}

// Plays an empty corner by checking if any of the corners are on the valid locations list
void AI::emptyCorner(Buildboard &board) {
	for (int i = 0; i < board.validLocations.size(); i++) {
		if (board.validLocations[i].compare("A1")) {
			move = board.validLocations[i];
		}
		else if (board.validLocations[i].compare("A3")) {
			move = board.validLocations[i];
		}
		else if (board.validLocations[i].compare("C1")) {
			move = board.validLocations[i];
		}
		else if (board.validLocations[i].compare("C1")) {
			move = board.validLocations[i];
		}
	}
}

//Plays in an empty opposing corner by checking for empty corners opposite where the player has played
void AI::oppositeCorner(vector <string> playerMoves, Buildboard &board) {
	for (int i = 0; i < playerMoves.size(); i++) {
		if (playerMoves[i].compare("A1") == 0) {
			move = "C3";
		}
		else if (playerMoves[i].compare("A3") == 0) {
			move = "C1";
		}
		else if (playerMoves[i].compare("C1") == 0) {
			move = "A3";
		}
		else if (playerMoves[i].compare("C3") == 0) {
			move = "A1";
		}
	}

}

// Tries to play in the centre of the board
void AI::centre(Buildboard &board) {
	move = "B2";
}

//Blocks an opponents fork by checking which valid location would give the opponnent more than 1 opportunity to win
void AI::blockOpponentFork(Player &player, Buildboard &board) {
	for (int i = 0; i < board.validLocations.size(); i++) {
		int count = 0;
		for (int j = 0; j < player.winningCombo.size(); j++) {
			if (player.winningCombo[j].size() == 2) {
				if (find(player.winningCombo[j].begin(), player.winningCombo[j].end(), board.validLocations[i]) != player.winningCombo[j].end()) {
					count++;
				}
			}
		}

		if (count > 1) {
			move = board.validLocations[i];
		}
	}
}

void AI::fork(Buildboard &board) {
//Fork by checking which valid location would give the AI more than one opportunity to win
	for (int i = 0; i < board.validLocations.size(); i++) {
		int count = 0;
		for (int j = 0; j < winningCombo.size(); j++) {
			if (winningCombo[j].size() == 2) {
				if (find(winningCombo[j].begin(), winningCombo[j].end(), board.validLocations[i]) != winningCombo[j].end()) {
					count++;
				}
			}
		}

		if (count > 1) {
			move = board.validLocations[i];
		}
	}
}

void AI::block(Player &player, Buildboard &board) {
//Block by checking which location the player needs to play to win
	for (int i = 0; i < player.winningCombo.size(); i++) {
		if (player.winningCombo[i].size() == 1) {
			move = player.winningCombo[i][0];
		}
	}
}

//Win by playing the last move required in a winning combo
void AI::win() {
	for (int i = 0; i < winningCombo.size(); i++) {
		if (winningCombo[i].size() == 1) {
			move = winningCombo[i][0];
		}
	}
}

void AI::playerTurn(Player &player, Buildboard &board) {

	isValid = validMove(move, (board.validLocations));

	for (int i = 0; i < (board.allLocations).size(); i++) {
		if (get<1>(isValid).compare((board.allLocations)[i]) == 0)
			(board.allLocations)[i] = playerCharacter + " ";
	}

	(board.validLocations).erase(remove((board.validLocations).begin(), (board.validLocations).end(), move), (board.validLocations).end());

	for (int i = 0; i < winningCombo.size(); i++) {
		winningCombo[i].erase(remove(winningCombo[i].begin(), winningCombo[i].end(), move), winningCombo[i].end());
	}

// Following iterator removes winning combinations from the player's list if that spot was just taken by the AI
	vector<vector <string>>::iterator it = player.winningCombo.begin();
	for (; it != player.winningCombo.end(); ) {
		if (find((*it).begin(), (*it).end(), move) != (*it).end()) {
			it = player.winningCombo.erase(it);
		}
		else {
			++it;
		}
	}
}

bool AI::isWinner() {
	for (int i = 0; i < winningCombo.size(); i++) {
		if (winningCombo[i].empty()) {
			return true;
		}
	}
	return false;
}
