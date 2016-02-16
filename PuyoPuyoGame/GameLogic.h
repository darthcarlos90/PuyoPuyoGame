/*
	The game logic class, it is in charge of showing the menu, staring the game, and finishing the game.
*/

#pragma once
#include "Menu.h"
#include "GameLoop.h"

class Gamelogic {
public:
	Gamelogic(void); // Constructor
	~Gamelogic(void); // destructo

	void Start(); // Method to start the game

private:
	Menu menu;
	GameLoop loop;

};