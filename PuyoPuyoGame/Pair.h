/*
	This class represents a pair of movable pieces
*/

#include "Utils.h"

class Pair{
public:
	Pair(char val1, char val2);
	Pair(const Pair& p); // copy constructor
	~Pair();

	void Shift(); // So the movable piece shifts in respecto to the pivot
	void Move(int direction); // Move towards a direction
	
	// Getters to the pieces
	Piece getP1() { return p1; }
	Piece getPivot() { return p2; }

	// Changes the locations of the pieces separately
	void ChangeP1OldLocation(Location newLoc);
	void ChangeP1Location(Location newLoc);
	void ChangePivotOldLocation(Location newLoc);
	void ChangePivotLocation(Location newLoc);

	// Stop moving
	void Stop() { moving = false; }
	Piece getLowest(bool* both); // Gets the location of the element closest to the bottom.
	Piece getLeftMost(bool * both); // Gets the location closes to the left
	Piece getRightMost(bool* both); // Same but to the right
	// In all those three methods, the parameter both is changed to true in case both are closes to the given dierection
	
	

private:

	Piece p1;
	Piece p2;// pivot piece

	bool moving; // flag to detect if this pair is moving

	int state; // The state of the moving piece
};