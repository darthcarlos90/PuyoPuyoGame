/*
	This header file contains various utilities like enums, structs, constants, etc
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
 // Sizes of the matrix of data
#define X_SIZE 12
#define Y_SIZE 6

 // The starting locations when a pair of pieces appear
#define X_START 0
#define Y_START 3

 // Difficulties
#define EASY 500.0f
#define MEDIUM 250.0f
#define HARD 125.0f
#define INSANE 0.0f

 // Sizes of window and buffer of console
#define WINDOW_X 35
#define WINDOW_Y 21



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