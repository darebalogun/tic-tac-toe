#ifndef BUILDBOARD_H
#define BUILDBOARD_H

//#include "player.h"
//#include "ai.h"

using namespace std;

class Buildboard {
/* One object of the buldboard class is used as the gameBoard. Player and AI objects have access to
this class as friends.
*/
	friend class Player;
	friend class AI;

public:
	vector <string> allLocations = { "A1", "A2", "A3", "B1", "B2", "B3", "C1", "C2", "C3" }; //Initialize place holders to be printed
	vector <string> validLocations = { "A1", "A2", "A3", "B1", "B2", "B3", "C1", "C2", "C3" }; //Initialize a vector of all valid locations
  void print();
	bool isFull();

private:
	// Code page 437 characters used to build the grid
	static const unsigned char topLeft = 201;
	static const unsigned char horiz = 205;
	static const unsigned char topMid = 203;
	static const unsigned char topRight = 187;
	static const unsigned char vert = 186;
	static const unsigned char midLeft = 204;
	static const unsigned char midMid = 206;
	static const unsigned char midRight = 185;
	static const unsigned char bottomLeft = 200;
	static const unsigned char midBottom = 202;
	static const unsigned char bottomRight = 188;
};
#endif
