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
		loop.Start();
		while (!loop.getPlayerLost()){
			loop.UpdateGame();
		}
	}

	system("pause");
}