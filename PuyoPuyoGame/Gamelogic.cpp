#include "GameLogic.h"

/*
	Let's have a simple structure for the game, show menu, start game depending on the menu output.
	Finish program, exit.
*/
Gamelogic::Gamelogic(void){
}

Gamelogic::~Gamelogic(void){
}

void Gamelogic::Start(){
	menu.Start();
	if (menu.GameStarted()){
		// Lets start the game logic
		GameTimer timer;
		loop.Start();
		while (!loop.getPlayerLost()){
			float msec = timer.GetTimedMS();
			loop.UpdateGame(msec);
			loop.PrintElements(); // Separate game logic from "rendering" if it can be called that way
		}
	}

	system("pause");
}