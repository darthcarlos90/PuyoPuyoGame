/*
	This header file contains various utilities like enums, structs, constant variables, etc
*/

#pragma once

// This enum represents the directions where a pair can move
 enum Directions{
	DOWN, LEFT, RIGHT
};

 /* This enum will be used to save the state of one of the pieces in respect to the pivot
  in the Pair class. */
 enum Piece_State{
	 P_LEFT, P_RIGHT, P_DOWN, P_UP
 };

 // This constants will be used through the game
#define X_SIZE 12
#define Y_SIZE 6
#define X_START 0
#define Y_START 3



//To simplify stuff, we are having a location struct
struct Location{
	int x;
	int y;

	//Constructor
	Location(int x, int y){
		this->x = x;
		this->y = y;
	}

	// Default constructor
	Location(){
		x = -1;
		y = -1;
	}

	// Assigment operator, just in case
	Location& operator = (const Location& l){
		this->x = l.x;
		this->y = l.y;

		return *this;
	}

	// Equals operator
	bool operator == (const Location& l){
		return this->x == l.x && this->y == l.y;
	}
};

struct Piece {
	//Copy constructor just in case
	Piece(const Piece& p){
		this->location = p.location;
		this->old_location = p.old_location;
		this->value = p.value;
	}
	//Default constructor
	Piece(){
		location.x = 0;
		location.y = 0;
		old_location.x = -1;
		old_location.y = -1;
	}

	Location location;
	// Old locations used for erasing purposes in the game board
	Location old_location;
	char value;


};