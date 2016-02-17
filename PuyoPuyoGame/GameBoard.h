/*
	This class represents a game board, and the pieces that are on it and the logic behind stuff related with the gameboard.
*/

#include "Matrix.h"
#include "Utils.h"
#include "Pair.h"
#include <vector>
#include <algorithm>

class Gameboard{
public:
	Gameboard();// creates empty gameboard
	~Gameboard(); // Destructs the gameboard

	void PrintBoard();
	void SetValue(Location l, char value); 
	void MovePair(Pair p);
	bool isOccuppied(Location l);
	bool canMove(Location from, int direction);
	void SetStaticPair(Pair p); // Sets a pair static and adds its elements to the static pieces vector
	int CheckPoints();


private:
	// Private helper methods
	void MovePiece(char value, Location l, Location old_l = Location()); // Old location is an optional parameter
	int CalculatePoints(Location l, char value);
	int TrackAdjacents(Location l, char value);
	vector<Location> AdjacentSimilar(Location l, char value, vector<Location> checked);

	Matrix<char>* board;
	
	// Flag to check if something changed in the board
	bool changes;

	vector<Piece> static_pieces;
	
	

};