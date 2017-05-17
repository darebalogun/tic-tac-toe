#include <iostream>
#include <string>
#include <Windows.h>
#include <algorithm>
#include <vector>
#include <tuple>
#include <stdlib.h>
#include "ai.h"
#include "player.h"
#include "buildboard.h"

using namespace std;

/*  upperCase function is passed in a string and returns uppercase of the string
*/
static string upperCase(const string & s) {
	string v(s);
	std::transform(v.begin(), v.end(), v.begin(), ::toupper);
	return v;
}

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

int main() {
	SetConsoleOutputCP(437); // Use code page 437 to print board characters
	bool player1Turn = true; // Player 1 goes first
	string noPlayers; //Hold the number of players
	Buildboard gameBoard; // Build
	gameBoard.print();	// and print game board.

	while (noPlayers.compare("1") != 0 && noPlayers.compare("2") != 0) { // Get user input on the number of players playing the game
		cout << "How many players? (Enter 1 or 2): ";
		getline(cin, noPlayers);
	}
	int no_Players = stoi(noPlayers);

	if (no_Players == 2) {

		gameBoard.print();

// Create 2 player objects
		Player Player1;
		Player Player2;
		AI ai;

// Get Player 1's name
		cout << "Player 1 goes first." << endl << endl;
		cout << "Player 1, What is your name? ";
		getline(cin, Player1.name);

		gameBoard.print();

//Get Players character
		cout << Player1.name + " would you like to be X or O?";
		getline(cin, Player1.playerCharacter);
		Player1.playerCharacter = upperCase(Player1.playerCharacter);

// If character is not valid then give error message and keep asking
		while (Player1.playerCharacter.compare("X") != 0 && Player1.playerCharacter.compare("O") != 0) {
			cout << endl << "That is not a valid character, please enter X or O ";
			getline(cin, Player1.playerCharacter);
			Player1.playerCharacter = upperCase(Player1.playerCharacter);
		}

// Assign the other player the complement character
		if (Player1.playerCharacter.compare("X") == 0) {
			Player2.playerCharacter = "O";
		}
		else {
			Player2.playerCharacter = "X";
		}

		gameBoard.print();

// Get player 2's name
		cout << "Player 2, What is your name? ";
		getline(cin, Player2.name);

		while (!Player1.isWinner() && !Player2.isWinner()) {

	//If gameboard is full. Game over
			if (gameBoard.isFull()) {
				cout << endl << "Game Over! DRAW!" << endl;
				break;
			}

			if (player1Turn) {
				Player1.playerTurn(ai, gameBoard); //Execute player 1's turn
				gameBoard.print();

				if (Player1.isWinner()) { //Check if player 1 has won after that turn
					cout << Player1.name +" Wins!" << endl << endl;
					break;
				}

				player1Turn = !player1Turn; // Switch turn to player 2
			}
			else {
				Player2.playerTurn(ai, gameBoard); //Execute player 2's turn
				gameBoard.print();

				if (Player2.isWinner()) { //CHeck if player 2 has won
					cout << Player2.name + " Wins!" << endl << endl;
					break;
				}

				player1Turn = !player1Turn; //Switch turns back to player 1
			}
		}
	}
	else {
		gameBoard.print();
		Player Player1;
		AI AI;

		vector <string> player1Moves; // Keep track of Player's moves for the A.I

// Get pplayers name and character
		cout << "Player 1, What is your name? " << endl << endl;
		getline(cin, Player1.name);
		gameBoard.print();
		cout << Player1.name + " would you like to be X or O? ";
		getline(cin, Player1.playerCharacter);
		Player1.playerCharacter = upperCase(Player1.playerCharacter);

//Keep asking if character is not valid
		while (Player1.playerCharacter.compare("X") != 0 && Player1.playerCharacter.compare("O") != 0) {
			cout << endl << "That is not a valid character, please enter X or O ";
			getline(cin, Player1.playerCharacter);
			Player1.playerCharacter = upperCase(Player1.playerCharacter);
		}
		if (Player1.playerCharacter.compare("X") == 0) {
			AI.playerCharacter = "O";
		}
		else {
			AI.playerCharacter = "X";
		}

		gameBoard.print();

		string player1first; // Ask user if they would like to go first
		while (player1first.compare("yes") != 0 && player1first.compare("no") != 0) {
			cout << Player1.name + " would you like to go first? (Enter yes or no): ";
			getline(cin, player1first);
		}

		if (player1first.compare("yes") == 0) {
			player1Turn = true;
		}
		else {
			player1Turn = false;
		}

		string difficultySTR; // Store user input for game difficulty

		cout << "Please enter difficulty from 0 - 5, with 5 being the perfect AI: ";
		getline(cin, difficultySTR);

		// Keep asking till user enter's valid difficulty
		while (difficultySTR.compare("0") != 0 && difficultySTR.compare("1") != 0 && difficultySTR.compare("2") != 0 && difficultySTR.compare("3") != 0 && difficultySTR.compare("4") != 0 && difficultySTR.compare("5") != 0) {
			cout << endl << "That is not a valid difficulty. Please enter a number from 0 to 5: ";
			getline(cin, difficultySTR);
		}

		int difficulty = stoi(difficultySTR); //Store difficulty as an int rather than a string
		difficulty = difficulty * 20;			// Scale difficulty up to a number between 20 and 100 inclusive 0, 20, 40, 60, 80 or 100

// Check if player or AI has won
		while (!Player1.isWinner() && !AI.isWinner()) {
			if (gameBoard.isFull()) {
				cout << endl << "Game Over! DRAW!" << endl;
				break;
			}

			if (player1Turn) {
				// Refresh board and execute players turn
				gameBoard.print();
				Player1.playerTurn(AI, gameBoard);
				gameBoard.print();

				// Check if player has won
				if (Player1.isWinner()) {
					cout << Player1.name + " Wins!" << endl << endl;
					break;
				}

				gameBoard.print();

				//Update the vector of player's moves for the AI
				player1Moves.push_back(Player1.location);

				//Switch turns to the AI
				player1Turn = !player1Turn;

			}
			else {

				/* The artificial intelligence works based on the strategy for a perfet game
				as outlined in Newell and Simon's 1972 tic-tac-toe program. The strategy is published at
				http://onlinelibrary.wiley.com/doi/10.1207/s15516709cog1704_3/epdf (by Kevin Crowley and Robert S. Siegler. 1993)

				****The Moves in Order****

				1. Win: If the player has two in a row, they can place a third to get three in a row.

				2. Block: If the opponent has two in a row, the player must play the third themselves to block the opponent.

				3. Fork: Create an opportunity where the player has two threats to win (two non-blocked lines of 2).

				4. Blocking an opponent's fork:

					Option 1: The player should create two in a row to force the opponent into defending, as long as it doesn't result in them creating a fork. For example, if "X" has a corner, "O" has the center, and "X" has the opposite corner as well, "O" must not play a corner in order to win. (Playing a corner in this scenario creates a fork for "X" to win.)

					Option 2: If there is a configuration where the opponent can fork, the player should block that fork.

				5. Center: A player marks the center. (If it is the first move of the game, playing on a corner gives "O" more opportunities to make a mistake and may therefore be the better choice; however, it makes no difference between perfect players.)

				6. Opposite corner: If the opponent is in the corner, the player plays the opposite corner.

				7. Empty corner: The player plays in a corner square.

				8. Empty side: The player plays in a middle square on any of the 4 sides.

				The difficulty challenge was achieved by deviating more from the order of priority of the moves with less diffculty.
				i.e at difficulty level 1. The AI will always play a winning move and a blocking move but it's move become random after that.
				At difficulty level 5 the AI wil play the perfect game by executing all the moves according to the priority as outlined above.
				*/

				//Attempt to win
				if (difficulty > 19 && get<0>(validMove(AI.move, gameBoard.validLocations)) == false) {
					AI.win();
				}

				// If cant win then block
				if (difficulty > 19 && get<0>(validMove(AI.move, gameBoard.validLocations)) == false) {
					AI.block(Player1, gameBoard);
				}

				// If nothing to block then create a fork
				if (difficulty > 39 && get<0>(validMove(AI.move, gameBoard.validLocations)) == false) {
					AI.fork(gameBoard);
				}

				// If cant create fork then block opponents fork
				if (difficulty > 39 && get<0>(validMove(AI.move, gameBoard.validLocations)) == false) {
					AI.blockOpponentFork(Player1, gameBoard);
				}

				// If no fork to block then play in the centre
				if (difficulty > 59 && get<0>(validMove(AI.move, gameBoard.validLocations)) == false) {
					AI.centre(gameBoard);
				}

				// If centre is invalid then play in the opposite corner of where player has played
				if (difficulty > 79 && get<0>(validMove(AI.move, gameBoard.validLocations)) == false) {
					AI.oppositeCorner(player1Moves, gameBoard);
				}

				// If no opposite corners are valid then play in an empty corner
				if (difficulty > 79 && get<0>(validMove(AI.move, gameBoard.validLocations)) == false) {
					AI.emptyCorner(gameBoard);
				}

				// If no opposite corners valid then play on empty side
				if (difficulty > 99 && get<0>(validMove(AI.move, gameBoard.validLocations)) == false) {
					AI.emptySide(gameBoard);
				}

				// If nothing above is valid then play a random valid move
				if (get<0>(validMove(AI.move, gameBoard.validLocations)) == false) {
					AI.randomMove(gameBoard);
				}

				//Execute the move
				AI.playerTurn(Player1, gameBoard);

				gameBoard.print();

				// Check if AI has won
				if (AI.isWinner()) {
					cout << "CPU Wins!" << endl << endl;
					break;
				}

				// Switch turns
				player1Turn = !player1Turn;

			}
		}
	}

	return 0;
}
