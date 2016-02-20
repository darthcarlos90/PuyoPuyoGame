#include "GameLoop.h"
#include <time.h>



GameLoop::GameLoop(void){
	// construct elements
	score = frames = 0;
	frames_p_sec = game_timer =  0.0f;
	player_lost = false;
	difficulty = EASY;
	falling = false;
	shift = 0;
	right = 0;
	left = 0;
	down = 0;
}

GameLoop::~GameLoop(void){
	//deconstruct elements
	DeletePair();
}

void GameLoop::Start(HANDLE writter){
	 PrintElements(writter);
}

void GameLoop::DeletePair(){
	delete pair;
	pair = NULL;
}

// prints on screen the elements of the game (score and the board basically)
void GameLoop::PrintElements(HANDLE writter){
	
	if(!player_lost) gameboard.PrintBoard(score, writter);
	else {
		system("cls");
		cout << "You lost :(" << endl;
		cout << "Score: " << score << endl;
	}

}

// The msec input refers to how many miliseconds have passed since the last frame
void GameLoop::UpdateGame(HANDLE reader, float msec){
	game_timer += msec; // Lets add how many milliseconds have passed
	DWORD numEvents = 0;
	DWORD numEventsRead = 0;
	GetNumberOfConsoleInputEvents(reader, &numEvents);
	srand(time(NULL));
	
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

			if (numEvents != 0){
				INPUT_RECORD *eventBuffer = new INPUT_RECORD[numEvents];
				ReadConsoleInput(reader, eventBuffer, numEvents, &numEventsRead);
				for (DWORD i = 0; i < numEventsRead; i++){
					if (eventBuffer[i].EventType == KEY_EVENT){
						if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_UP){
							shift++;
							if (shift >= 2){
								pair->Shift();
								gameboard.move_piece(pair->getP1()); // Only move p1, since is the one that shifts
								shift = 0;
							}
						}
						if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_LEFT){
							left++;
							if (left >= 2){
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
								left = 0;
							}
						}

						if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_RIGHT){
							right++;
							if (right >= 2){
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
						}

						if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_DOWN){
							down++;
							if (down >= 2){
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
						}
					}
				}
			}
			
			if (game_timer > difficulty){ // If the timer is less than X seconds, skip 
				game_timer = 0.0f; // reset timer
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
						score += gameboard.CheckPoints(difficulty);
						if (score > 200 && score < 400) difficulty = MEDIUM;
						if (score > 800) difficulty = HARD;
					}
				}
				else {
					if (gameboard.canMove(p.location, DOWN)){
						pair->Move(DOWN);
						gameboard.MovePair(*pair);
					}
					else {
						//If not, make the pair static
						gameboard.SetStaticPair(*pair);
						DeletePair(); // delete the pair to create a new one
						falling = false;
						score += gameboard.CheckPoints(difficulty);
						if (score > 200 && score < 400) difficulty = MEDIUM;
						if (score > 800 && score < 900) difficulty = HARD;
						if (score > 900) difficulty = INSANE;
					}
				}
			}

				frames++;
				frames_p_sec = 1.0f / (msec / 1000.0f);

			}
		
}