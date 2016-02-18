/*
	This is the class where the main game loop will reside, here all the
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

	void Start(HANDLE writter); 
	// Temporary fix
	void UpdateGame(float msec = 0.0f); // Game update method

	// as coding goes on try adding more and more methods
	bool getPlayerLost() { return player_lost; }
	void PrintElements(HANDLE writter);

private:
	
	void DeletePair();


	unsigned int score;
	unsigned int frames; // for debugging purposes
	float frames_p_sec;
	bool player_lost;
	float game_timer;


	// These variables are used to save where the 
	bool falling; // flag to detect if a piece is still falling

	Gameboard gameboard;
	Pair* pair; //This pair will be recycled for the upcoming pairs

	double difficulty;

};
