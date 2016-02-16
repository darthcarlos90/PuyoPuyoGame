/*
	This header file contains various utilities like enums, structs, constant variables, etc
*/

#pragma once

// This enum represents the directions where a pair can move
 enum Directions{
	DOWN, LEFT, RIGHT
};

 // This constants will be used through the game
#define X_SIZE 12
#define Y_SIZE 6
#define X_START 0
#define Y_START 3

struct Piece {
	Location location;
	// Old locations used for erasing purposes in the game board
	Location old_location;
	char value;


};

//To simplify stuff, we are having a location struct
struct Location{
	int x;
	int y;

	// Assigment operator, just in case
	Location& operator = (const Location& l){
		x = l.x;
		y = l.y;
	}
};