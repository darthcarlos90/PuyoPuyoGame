#include "GameLoop.h"
#include <stdlib.h>



GameLoop::GameLoop(void){
	// construct elements
	gameboard = new Matrix<char>(12, 6);
	score = 0;
	player_lost = false;
	
	falling = false;
}

GameLoop::~GameLoop(void){
	//deconstruct elements
	delete gameboard;
}

void GameLoop::Start(void){
	system("cls");
	//first, lets set all the elements of the matrix to ' '
	for (unsigned int i = 0; i < gameboard->get_x_size(); i++){
		for (unsigned int j = 0; j < gameboard->get_y_size(); j++){
			gameboard->set_element(i, j, ' ');
		}
	}

	PrintElements();
}
// prints on screen the elements of the game (score and the board basically)
void GameLoop::PrintElements(){
	cout << "Score: " << score << endl;
	cout << *gameboard << endl;
}

// The msec input refers to how many miliseconds have passed since the last frame
void GameLoop::UpdateGame(float msec){
	/*
		For this game, we will use numbers instead of colours. We will use from 1 to 4 
		to depic different "colours".
	*/
	// Step 1: Is a piece falling?
	if (falling = false){ // If not, lets make one fall
		// Select the two random values that will drop.
		int value1 = rand() % 4 + 1; // a random number between 1 and 4
		int value2 = rand() % 4 + 1;

		// put those values at the top center of the board
		gameboard->set_element(x_location, y_location, (char)value1);
		gameboard->set_element(x_location, y_location + 1, (char)value2);
		falling = true;
	}
	else {// If the piece is falling, lets move it a step downward

	}

}