/*
	This class represents a game board, and the pieces that are on it and the logic behind stuff related with the gameboard.
*/

#include "Matrix.h"
#include "Utils.h"
#include "Pair.h"
#include <vector>

class Gameboard{
public:
	Gameboard();// creates empty gameboard
	~Gameboard(); // Destructs the gameboard

	void PrintBoard();
	void SetValue(Location l, char value); 
	void MovePair(Pair p);
	bool isOccuppied(Location l);
	bool canMove(Location from, int direction);


private:
	void MovePiece(char value, Location l, Location old_l = Location()); // Old location is an optional parameter
	Matrix<char>* board;
	
	

};