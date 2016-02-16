/*
	This is the class where the main game loop will reside, here all the
	elements of the game will be of some sort stored, and it will be changed
	any time I need something.

*/
#pragma once
#include "Matrix.h"


class GameLoop{
public:
	GameLoop(void);
	~GameLoop(void);

	void Start(void);

	// as coding goes on try adding more and more methods

private:
	void PrintElements();
	// start adding properties
	Matrix<char>* gameboard; // pointer to the matrix
	unsigned int score;
	bool player_lost;
};
