#include "GameLoop.h"
#include <stdlib.h>
#include <string>
#include <Windows.h>



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
		if (gameboard.isOccuppied(pair->getP1().location) || gameboard.isOccuppied(pair->getPivot().location)){
			player_lost = true;
		}
		else {
			gameboard.SetMoving(pair->getP1().value, pair->getP1().location);
			gameboard.SetMoving(pair->getPivot().value, pair->getPivot().location);
			falling = true;
			PrintElements();
		}
		
	}
	else {// If the piece is falling, lets move it a step downward
		// First, is there any input from the user?
		//TODO: If time, create a function out of the stuff below
		if (GetAsyncKeyState(VK_LEFT)){ // If left was pressed
			if (gameboard.canMove(pair->getP1().location, LEFT) && gameboard.canMove(pair->getPivot().location, LEFT)){
				pair->Move(LEFT);
				//TODO: Left here, add the setmoving to all this methods so that the board can get updated
			}
		}
		else if (GetAsyncKeyState(VK_RIGHT)){ // If right was pressed
			if (gameboard.canMove(pair->getP1().location, RIGHT) && gameboard.canMove(pair->getPivot().location, RIGHT)){
				pair->Move(RIGHT);
			}
		}
		else if (GetAsyncKeyState(VK_DOWN)){// If down was pressed
			if (gameboard.canMove(pair->getP1().location, DOWN) && gameboard.canMove(pair->getPivot().location, DOWN)){
				pair->Move(DOWN);
		}
		//Now see if you can move further down
		if (gameboard.canMove(pair->getP1().location, DOWN) && gameboard.canMove(pair->getPivot().location, DOWN)){
			pair->Move(DOWN);
		}
		else {
			//If not, make the pair static
			gameboard.SetValue(pair->getP1().location, pair->getP1().value);
			gameboard.SetValue(pair->getPivot().location, pair->getPivot().value);
			pair = NULL; // delete the pair to create a new one
		}
		

	}

	

}