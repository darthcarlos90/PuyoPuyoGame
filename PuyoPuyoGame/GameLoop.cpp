#include "GameLoop.h"


GameLoop::GameLoop(void){
	// construct elements
	gameboard = new Matrix<char>(12, 6);
	score = 0;
	player_lost = false;
}

GameLoop::~GameLoop(void){
	//deconstruct elements
	delete gameboard;
}

void GameLoop::Start(void){
	system("cls");
	//first, lets set all the elements of the matrix to ' '
	for (unsigned int i = 0; i < gameboard->get_x_size(); i++){
		for (unsigned int j = 0; j < gameboard->get_y_size(); j++){
			gameboard->set_element(i, j, ' ');
		}
	}

	PrintElements();
}
// prints on screen the elements of the game (score and the board basically)
void GameLoop::PrintElements(){
	cout << "Score: " << score << endl;
	cout << *gameboard << endl;
}