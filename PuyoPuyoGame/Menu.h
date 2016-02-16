/*
	A simple menu class to show a menu and possibly some options.
	Just want to keep stuff separated so they are easily read.
	
*/

#include <iostream>

using namespace std;

class Menu{
public:
	Menu(void); //Constructor
	~Menu(void); // Destructor
	
	void Start(void); // show the menu to the user
	bool GameStarted(void) { return start_game; }; // has the user started the game?

private:
	bool start_game;
	
};