#include <iostream>
#include <string>
#include <Windows.h>
#include <algorithm>
#include <vector>
#include <tuple>
#include <stdlib.h>
#include "player.h"
#include "buildboard.h"

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

/*  upperCase function is passed in a string and returns uppercase of the string
*/
static string upperCase(const string & s) {
	string v(s);
	std::transform(v.begin(), v.end(), v.begin(), ::toupper);
	return v;
}

void Player::playerTurn(Buildboard &board) { 
// Method executes the player's turn. Parameter is an object of the Buildboard class
// Ask the user for the location of next move and check if the move is valid
	cout << name +"'s turn" << endl;
	cout << endl << "Enter location of your next move: ";
	getline(cin, location);
	location = upperCase(location);
	isValid = validMove(location, board.validLocations);

//If the user inputs an invalid move, keep asking until the move is valid
	while (get<0>(isValid) == false) {
		cout << endl << "That is not a valid move, please try again: ";
		getline(cin, location);
		location = upperCase(location);
		isValid = validMove(location, board.validLocations);
	}

// Once you get a valid move, replace the placeholder on the board with the players character. So show the move on the board
	for (int i = 0; i < board.allLocations.size(); i++) {
		if (get<1>(isValid).compare(board.allLocations[i]) == 0)
			board.allLocations[i] = playerCharacter + " ";
	}

// Remove that move from the vector of valid locations. That spot is now taken
	board.validLocations.erase(remove(board.validLocations.begin(), board.validLocations.end(), location), board.validLocations.end());

// Also remove the location from the vector of vectors of winning combo strings
	for (int i = 0; i < winningCombo.size(); i++) {
		winningCombo[i].erase(remove(winningCombo[i].begin(), winningCombo[i].end(), location), winningCombo[i].end());
	}
}

bool Player::isWinner() { //Check is any of the winning combination vectors is empty. If it is the player has won the game
	for (int i = 0; i < winningCombo.size(); i++) {
		if (winningCombo[i].empty()) {
			return true;
		}
	}
	return false;
}
