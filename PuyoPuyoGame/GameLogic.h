/*
	The game logic class, it is in charge of showing the menu, staring the game, and finishing the game.
*/

#pragma once
#include "Menu.h"
#include "GameLoop.h"
#include "GameTimer.h"

class Gamelogic {
public:
	Gamelogic(void); // Constructor
	~Gamelogic(void); // destructor

	void Start(); //Starts the game

private:
	Menu menu; // A class to show a menu
	GameLoop loop; // Where the game loop resides

};