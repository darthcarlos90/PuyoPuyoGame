#include "GameBoard.h"

Gameboard::Gameboard(){
	board = new Matrix<char>(X_SIZE, Y_SIZE);
	// creates an empty gameboard
	for (unsigned int i = 0; i < X_SIZE; i++){
		for (unsigned int j = 0; j < Y_SIZE; j++){
			board->set_element(i, j, ' ');
		}
	}
}

Gameboard::~Gameboard(){
	delete board;
}

void Gameboard::PrintBoard(){
	cout << *board << endl;
}

void Gameboard::SetValue(Location l, char value){
	board->set_element(l.x, l.y, value);
}

void Gameboard::SetMoving(char value, Location l, Location old_l){
	if (old_l.x != -1){ // if there is an old_x
		SetValue(old_l, ' '); // set empty
	}

	SetValue(l, value); // Re-use ;)
}