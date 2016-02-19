/*
	This class represents a game board, and the pieces that are on it and the logic behind stuff related with the gameboard.
*/

#include "Matrix.h"
#include "Utils.h"
#include "Pair.h"
#include <vector>
#include <algorithm>
#include <Windows.h>



class Gameboard{
public:
	Gameboard();// creates empty gameboard
	~Gameboard(); // Destructs the gameboard

	void PrintBoard(int score, HANDLE writter);
	void SetValue(Location l, char value); 
	void MovePair(Pair p);
	bool isOccuppied(Location l);
	bool canMove(Location from, int direction);
	void SetStaticPair(Pair p); // Sets a pair static and adds its elements to the static pieces vector
	int CheckPoints(double difficulty);
	void move_piece(Piece p); // Public method accepts a piece class as parameter so it can be used on shifting
	


private:
	// Private helper methods
	// Private method for internal use
	void MovePiece(char value, Location newLocation); 
	void DeleteValue(Location old_l); // So the spaces are first errased, then re printed in separate processes
	int CalculatePoints(Location l, char value);
	int TrackAdjacents(Location l, char value);
	vector<Location> AdjacentSimilar(Location l, char value, vector<Location> checked);
	void DeleteLocation(Location l);

	Matrix<char>* board;
	
	// Flag to check if something changed in the board
	bool changes;

	vector<Piece> static_pieces;

	double difficulty;
	
	

};