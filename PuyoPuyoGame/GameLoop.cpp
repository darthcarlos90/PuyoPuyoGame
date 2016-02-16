#include "GameLoop.h"
#include <stdlib.h>
#include <string>



GameLoop::GameLoop(void){
	// construct elements
	score = 0;
	player_lost = false;
	
	falling = false;
}

GameLoop::~GameLoop(void){
	//deconstruct elements
}

void GameLoop::Start(void){


	PrintElements();
}
// prints on screen the elements of the game (score and the board basically)
void GameLoop::PrintElements(){
	system("cls");
	cout << "Score: " << score << endl;
	gameboard.PrintBoard();
}

// The msec input refers to how many miliseconds have passed since the last frame
void GameLoop::UpdateGame(float msec){
	/*
		For this game, we will use numbers instead of colours. We will use from 1 to 4 
		to depic different "colours".
	*/
	// Step 1: Is a piece falling?
	if (falling == false){ // If not, lets make one fall
		// Select the two random values that will drop.
		std::string value1 = std::to_string(rand() % 4 + 1); // a random number between 1 and 4
		std::string value2 = std::to_string(rand() % 4 + 1);

		pair = new Pair(value1[0], value2[0]);
		gameboard.SetMoving(pair->getP1().value, pair->getP1().location);
		gameboard.SetMoving(pair->getPivot().value, pair->getPivot().location);
		falling = true;
		PrintElements();
	}
	else {// If the piece is falling, lets move it a step downward
		// First, can the piece move?

	}

	player_lost = true;

}