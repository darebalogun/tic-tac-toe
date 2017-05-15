#include <iostream>
#include <string>
#include <Windows.h>
#include <algorithm>
#include <vector>
#include <tuple>
#include <stdlib.h>
#include "buildboard.h"

using namespace std;

void Buildboard::print() { // Print out grid outline and placeholders which will be updated as game progresses

	system("cls"); //Refresh the console on each print
	cout << topLeft << horiz << topMid << horiz << topMid << horiz << topRight << endl;
	cout << vert << allLocations[0] << vert << allLocations[1] << vert << allLocations[2] << vert << endl;
	cout << midLeft << horiz << midMid << horiz << midMid << horiz << midRight << endl;
	cout << vert << allLocations[3] << vert << allLocations[4] << vert << allLocations[5] << vert << endl;
	cout << midLeft << horiz << midMid << horiz << midMid << horiz << midRight << endl;
	cout << vert << allLocations[6] << vert << allLocations[7] << vert << allLocations[8] << vert << endl;
	cout << bottomLeft << horiz << midBottom << horiz << midBottom << horiz << bottomRight << endl << endl << endl;

}

bool Buildboard::isFull() { // Return true if the board is full and false if there are still open spots
	return validLocations.empty();
}
