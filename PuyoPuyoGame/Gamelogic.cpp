#include "GameLogic.h"
#include "Window.h"

/*
	Let's have a simple structure for the game:
	show menu ----> start game  or finish program depending on the menu output --- >Finish program ---> exit.
*/
Gamelogic::Gamelogic(void){
	// Nothing to construct
}

Gamelogic::~Gamelogic(void){
	// Nothing to destroy
}

void Gamelogic::Start(){
	menu.Start(); // Show the menu
	if (menu.GameStarted()){ // If the user chosed to start the game
		// Lets start the game logic
		GameTimer timer; // A timer to measure time between frames and stuff
		Window w; // A class to handle stuff related to the windows
		loop.Start(w.getWritter()); // Prepare the game to start
		while (!loop.getPlayerLost()){ // while the player hasn't lost
			float msec = timer.GetTimedMS(); //calculate the amount of milliseconds that has passed since the last frame
			loop.UpdateGame(w.getReader(), msec); // Update the game logic
			loop.PrintElements(w.getWritter()); // Separate game logic from "rendering" 
		}
	}

	system("pause"); // Pause before exiting
}