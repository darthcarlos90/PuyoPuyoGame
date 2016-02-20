/*
	This class represents a game board, and the pieces that are on it some of the game logic is also here, as well
	as the "rendering" stuff.
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

	void PrintBoard(int score, HANDLE writter); // Prints the board into the console
	void SetValue(Location l, char value); // Set a value in the matrix
	void MovePair(Pair p); // Move a pair through the matrix
	bool isOccuppied(Location l); // Check if location l is occuppied
	bool canMove(Location from, int direction); // Check if the element at location from can move in the direction direction
	void SetStaticPair(Pair p); // Sets a pair static and adds its elements to the static pieces vector
	int CheckPoints(double difficulty);
	void move_piece(Piece p); // Public method accepts a piece class as parameter so it can be used on shifting
	


private:
	// Private method for internal use
	void MovePiece(char value, Location newLocation);  // Moves a piece with the value value, to the newLocation
	void DeleteValue(Location old_l); // So the spaces are first errased, then re printed in separate processes
	int CalculatePoints(Location l, char value); //Calculates the points in a state of the board (if any points can be achieved)
	int TrackAdjacents(Location l, char value); // Checks how many pieces of the same type are around a piece at location l with value value.
	/* More on the Gameboard.cpp class*/
	vector<Location> AdjacentSimilar(Location l, char value, vector<Location> checked);
	void DeleteLocation(Location l); // Deletes the value at location l

	Matrix<char>* board; // The actual representation of the game board
	
	// Flag to check if something changed in the board
	bool changes;

	vector<Piece> static_pieces; // The pieces on the board that are static

};