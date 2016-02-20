#include "Menu.h"

Menu::Menu(void){
	start_game = false; // set the value to false
}

Menu::~Menu(void){
	// destructor
}
/*
	Show the menu and start the game
*/
void Menu::Start(void){
	cout << "Welcome to my Puyo Puyo Game!" << endl;
	cout << "Please select an option from below:\n1)Press 1 to start game.\n2)Press 2 to exit game." << endl;
	int option;
	cin >> option;
	if (option == 1){ // If the option is one, lets start the game
		start_game = true;
	}
}