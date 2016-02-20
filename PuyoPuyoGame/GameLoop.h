/*
	This is the class where the main game loop and "rendering" loop will reside, here all the
	elements of the game will be of some sort stored, and it will be changed
	any time I need something.

*/
#pragma once
#include "Matrix.h"
#include "GameBoard.h"
#include <stdlib.h>
#include <string>
#include <Windows.h>


class GameLoop{
public:
	GameLoop(void);
	~GameLoop(void);

	/* More on this on the .cpp file*/
	void Start(HANDLE writter); 

	/* Updates the game logic.
		The parameters are: a reader, so we can "catch" when the user presses a key, and the milliseconds that
		passed since the last update.
	*/
	void UpdateGame(HANDLE reader, float msec); 

	/* Returns the value of the player lost flag.*/
	bool getPlayerLost() { return player_lost; }

	/*
		Prints elements on the screen. It is kind of the "rendering" loop. 
		The writter parameter is used so we can write into the console.
	*/
	void PrintElements(HANDLE writter);

private:
	/* Deletes a pair of elements. More info on the .cpp file.*/
	void DeletePair();
	/* This is a helper function so I don't have to repeat the same code again and again.*/
	void MovePairHelper(int direction, bool both, Location location);
	/* Another helper function to save code repetition*/
	void MakeStaticPairHelper();


	unsigned int score; // the user score
	bool player_lost; // flag to detect if the player lost
	float game_timer; // a variable to save the state of the timer

	bool falling; // flag to detect if a piece is still falling

	Gameboard gameboard; // This class represents the board where the game is being played
	/* The pair represents a pair of pieces falling down*/
	Pair* pair; //This pair will be recycled for the upcoming pairs

	double difficulty; // The difficulty of the game
	
	// Counters to sanitize the inputs
	int shift, right, left, down;

};
