#include "GameLoop.h"



GameLoop::GameLoop(void){
	// construct elements
	score = frames = 0;
	frames_p_sec = game_timer =  0.0f;
	player_lost = false;
	
	falling = false;
}

GameLoop::~GameLoop(void){
	//deconstruct elements
	DeletePair();
}

void GameLoop::Start(void){
	PrintElements();
}

void GameLoop::DeletePair(){
	delete pair;
	pair = NULL;
}

// prints on screen the elements of the game (score and the board basically)
void GameLoop::PrintElements(){
	
	//cout << "Score: " << score << endl;
	// For debugging purposes
	//cout << "Frames: " << frames << endl;
	//cout << "Frames per second: " << frames_p_sec << endl;
	gameboard.PrintBoard();
}

// The msec input refers to how many miliseconds have passed since the last frame
void GameLoop::UpdateGame(float msec){
	game_timer += msec; // Lets add how many milliseconds have passed
	if (game_timer > 500.0f){ // If the timer is less than X seconds, skip 
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
				gameboard.MovePair(*pair);
				falling = true;
			}

		}
		else {// If the piece is falling, lets move it a step downward
			// First, is there any input from the user?
			//TODO: If time, create a function out of the stuff below
			bool both = false;
			if (GetAsyncKeyState(0x53)){
				pair->Shift();
				gameboard.MovePair(*pair);
			}
			else if (GetAsyncKeyState(VK_LEFT)){ // If left was pressed
				Piece p = pair->getLeftMost(&both);
				if (both){
					if (gameboard.canMove(pair->getP1().location, LEFT) && gameboard.canMove(pair->getPivot().location, LEFT)){
						pair->Move(LEFT);
						gameboard.MovePair(*pair);
					}

				}
				else {
					if (gameboard.canMove(p.location, LEFT)){
						pair->Move(LEFT);
						gameboard.MovePair(*pair);
					}
				}
			}
			else if (GetAsyncKeyState(VK_RIGHT)){ // If right was pressed
				Piece p = pair->getRightMost(&both);
				if (both){
					if (gameboard.canMove(pair->getP1().location, RIGHT) && gameboard.canMove(pair->getPivot().location, RIGHT)){
						pair->Move(RIGHT);
						gameboard.MovePair(*pair);
					}
				}
				else {
					if (gameboard.canMove(p.location, RIGHT)){
						pair->Move(RIGHT);
						gameboard.MovePair(*pair);
					}
				}

			}
			else if (GetAsyncKeyState(VK_DOWN)){// If down was pressed
				Piece p = pair->getLowest(&both);
				if (both){
					if (gameboard.canMove(pair->getP1().location, DOWN) && gameboard.canMove(pair->getPivot().location, DOWN)){
						pair->Move(DOWN);
						gameboard.MovePair(*pair);
					}

				}
				else {
					if (gameboard.canMove(p.location, DOWN)){
						pair->Move(DOWN);
						gameboard.MovePair(*pair);
					}
				}


			}

			//Now see if you can move further down
			Piece p = pair->getLowest(&both);
			if (both){

				if (gameboard.canMove(pair->getP1().location, DOWN) && gameboard.canMove(pair->getPivot().location, DOWN)){
					pair->Move(DOWN);
					gameboard.MovePair(*pair);
				}
				else {
					//If not, make the pair static
					gameboard.SetStaticPair(*pair);
					DeletePair(); // delete the pair to create a new one
					falling = false;

				}
			}
			else {

				if (gameboard.canMove(p.location, DOWN)){
					pair->Move(DOWN);
					gameboard.MovePair(*pair);
				}
				else {
					//If not, make the pair static
					gameboard.SetValue(pair->getP1().location, pair->getP1().value);
					gameboard.SetValue(pair->getPivot().location, pair->getPivot().value);
					DeletePair(); // delete the pair to create a new one
					falling = false;

				}
			}


		}

		frames++;
		frames_p_sec = 1.0f / (msec / 1000.0f);
		PrintElements();
		game_timer = 0.0f; // reset timer
	}
}