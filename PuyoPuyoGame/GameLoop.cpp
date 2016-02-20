#include "GameLoop.h"
#include <time.h>



GameLoop::GameLoop(void){
	// construct elements
	score = 0;
	game_timer =  0.0f;
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

/*
	Simply prints the board without anything
*/
void GameLoop::Start(HANDLE writter){
	PrintElements(writter);
}

/* 
	This method is in charge of deleting the pair for further recycling.
*/
void GameLoop::DeletePair(){
	delete pair;
	pair = NULL;
}

// "Renders" the game elements. When the player lost, it shows you your score.
void GameLoop::PrintElements(HANDLE writter){
	// If the player hasn't lost, continue printing the board
	if(!player_lost) gameboard.PrintBoard(score, writter);
	else { // Otherwise, print the score and a sad message :(
		system("cls");
		cout << "You lost :(" << endl;
		cout << "Score: " << score << endl;
	}

}

// The msec input refers to how many miliseconds have passed since the last frame
// The reader will be used to read inputs from the user
void GameLoop::UpdateGame(HANDLE reader, float msec){
	game_timer += msec; // Lets add how many milliseconds have passed
	

	// Variables used for the detection of a pressed key
	DWORD numEvents = 0;
	DWORD numEventsRead = 0;

	// Get the pressed key elements
	GetNumberOfConsoleInputEvents(reader, &numEvents);
	
	
		//Firstly, lets see if a piece is already falling.
		if (falling == false){ // If not, lets make one fall
			srand(time(NULL)); // Seed for the random generator
			// Select the two random values that will drop.
			std::string value1 = std::to_string(rand() % 4 + 1); // a random number between 1 and 4
			std::string value2 = std::to_string(rand() % 4 + 1);
			// convert from string to char by taking the first element of the string
			pair = new Pair(value1[0], value2[0]); // Create a new pair with the random values

			// If the newly generated pair can't move further, then the player already lost
			if (gameboard.isOccuppied(pair->getP1().location) || gameboard.isOccuppied(pair->getPivot().location)){
				player_lost = true;
			}
			else {
				// Otherwise start moving the pair downwards
				gameboard.MovePair(*pair);
				falling = true; // Set the falling flag to true
			}

		}
		else {// If the piece is falling, lets move it a step downward
			// First, is there any input from the user?
			bool both = false; // A flag to check if both elements of the pair are at the same level

			if (numEvents != 0){ // If the number of events is not zero
				INPUT_RECORD *eventBuffer = new INPUT_RECORD[numEvents]; // Save the events in the event buffer
				ReadConsoleInput(reader, eventBuffer, numEvents, &numEventsRead); // Read the input from the console
				for (DWORD i = 0; i < numEventsRead; i++){ // Go through all the events read
					if (eventBuffer[i].EventType == KEY_EVENT){ // If it was a key pressed
						if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_UP){ // If up was pressed
							// Lets shift the pair
							shift++; //Increase the sanitizer helper variable
							if (shift >= 2){ // If it is more than two, then proceed to shift
								pair->Shift();
								gameboard.move_piece(pair->getP1()); // Only move p1, since is the one that shifts
								shift = 0; // Reset counter
							}
						}
						if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_LEFT){ // If left was pressed
							left++;
							if (left >= 2){
								Piece p = pair->getLeftMost(&both);
								MovePairHelper(LEFT, both, p.location); // Call the move helper
								left = 0; // Reset the counter
							}
						}

						if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_RIGHT){
							right++;
							if (right >= 2){
								Piece p = pair->getRightMost(&both);
								MovePairHelper(RIGHT, both, p.location);
								right = 0;
							}
						}

						if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_DOWN){
							down++;
							if (down >= 2){
								Piece p = pair->getLowest(&both);
								MovePairHelper(DOWN, both, p.location);
								down = 0;
							}
						}
					}
				}

				delete eventBuffer; // Delete the pointer
			}
			
			/*
				Here we compare how many time has passed since the last frame, that way we can manage the speed of the
				pieces falling depending on the difficulty. If the difficulty is higher, the pieces will move faster.
			*/
			if (game_timer > difficulty){ // If the timer is greater than the difficulty
				game_timer = 0.0f; // reset timer
				//Now see if you can move further down
				Piece p = pair->getLowest(&both);
				if (both){ // If both are at the same level
					// Check if both can move downward
					if (gameboard.canMove(pair->getP1().location, DOWN) && gameboard.canMove(pair->getPivot().location, DOWN)){
						pair->Move(DOWN);
						gameboard.MovePair(*pair);
					}
					else {
						//If not, make the pair static
						MakeStaticPairHelper();
					}
				}
				else {
					if (gameboard.canMove(p.location, DOWN)){
						pair->Move(DOWN);
						gameboard.MovePair(*pair);
					}
					else {
						//If not, make the pair static
						MakeStaticPairHelper();
					}
				}
			}

			}
		
}

/*
	Helper method to move a pair.
	The parameters are:
	- direction: the value of the direction which it will move (see enum on Utils.h)
	- both: if both are on the same level
	- location: If not at the same level, what location to use
*/
void GameLoop::MovePairHelper(int direction, bool both, Location location){
	if (both){ // If both are at the same level
		// If both are at the same level, check if they are both able to move in that direction
		if (gameboard.canMove(pair->getP1().location, direction) && gameboard.canMove(pair->getPivot().location, direction)){
			pair->Move(direction);
			gameboard.MovePair(*pair);
		}

	}
	else {
		// Otherwise get the element that is on the side where we are moving, and move in that direction
		if (gameboard.canMove(location, direction)){
			pair->Move(direction);
			gameboard.MovePair(*pair);
		}
	}
}

/*
	Helper method for when a piece must stop moving and stay static
*/
void GameLoop::MakeStaticPairHelper(){
	gameboard.SetStaticPair(*pair); // Set the piece static
	DeletePair(); // delete the pair to create a new one
	falling = false; // The piece stopped falling
	score += gameboard.CheckPoints(difficulty); // Calculate points if any

	// Modify the difficulty
	if (score > 200 && score < 400) difficulty = MEDIUM;
	if (score > 800 && score < 900) difficulty = HARD;
	if (score > 900) difficulty = INSANE;

}