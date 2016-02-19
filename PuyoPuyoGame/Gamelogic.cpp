#include "GameLogic.h"
#include "Window.h"

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
		Window w;
		loop.Start(w.getWritter());
		while (!loop.getPlayerLost()){
			float msec = timer.GetTimedMS();
			loop.UpdateGame(w.getReader(), msec);
			loop.PrintElements(w.getWritter()); // Separate game logic from "rendering" if it can be called that way
		}
	}

	system("pause");
}