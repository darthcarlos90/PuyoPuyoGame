/*
	This class represents a game board, and the pieces that are on it and the logic behind stuff related with the gameboard.
*/

#include "Matrix.h"
#include "Utils.h"
#include <vector>

class Gameboard{
public:
	Gameboard();// creates empty gameboard
	~Gameboard(); // Destructs the gameboard

	void PrintBoard();
	void SetValue(Location l, char value); 
	void SetMoving(char value, Location l, Location old_l = Location()); // Old location is an optional parameter
	bool isOccuppied(Location l);
	bool canMove(Location from, int direction);


private:
	Matrix<char>* board;
	
	

};