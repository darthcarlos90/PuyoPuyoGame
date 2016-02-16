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
	Location getLowest(); // Gets the location of the element closest to the bottom.

private:

	Piece p1;
	Piece p2;// pivot piece

	bool moving; // flag to detect if this pair is moving

	
};