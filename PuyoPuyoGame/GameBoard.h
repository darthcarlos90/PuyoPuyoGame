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


private:
	Matrix<char>* board;
	

};