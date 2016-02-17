/*
	This class represents a pair of movable pieces
*/

#include "Utils.h"

class Pair{
public:
	Pair(char val1, char val2);
	Pair(const Pair& p); // copy constructor
	~Pair();

	void Shift();
	void Move(int direction);
	Piece getP1() { return p1; }
	Piece getPivot() { return p2; }
	void Stop() { moving = false; }
	Piece getLowest(bool* both); // Gets the location of the element closest to the bottom.
	Piece getLeftMost(bool * both);
	Piece getRightMost(bool* both);
	
	

private:

	Piece p1;
	Piece p2;// pivot piece

	bool moving; // flag to detect if this pair is moving

	
};