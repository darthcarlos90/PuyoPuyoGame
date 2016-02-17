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

void Gameboard::MovePiece(char value, Location l, Location old_l){
	if (old_l.x != -1){ // if there is an old_x
		SetValue(old_l, ' '); // set empty
	}

	SetValue(l, value); // Re-use ;)
}

bool Gameboard::isOccuppied(Location l){
	// So it cant go out of the borders
	if (l.x >= board->get_x_size()) return true;
	else if (l.y >= board->get_y_size()) return true;
	else if (l.y < 0) return true;

	// Now if the location is inside the borders, see if it is occuppied
	char value = board->get_element(l.x, l.y);
	if (value == ' '){
		return false;
	}
	else return true;
}


bool Gameboard::canMove(Location from, int direction){
	switch (direction){
	case DOWN:
		return !isOccuppied(Location(from.x + 1, from.y));
		break;
	case LEFT:
		return !isOccuppied(Location(from.x, from.y - 1));
		break;
	case RIGHT:
		return !isOccuppied(Location(from.x, from.y + 1));
		break;
	}
}

void Gameboard::MovePair(Pair p){
	MovePiece(p.getP1().value, p.getP1().location, p.getP1().old_location);
	MovePiece(p.getPivot().value, p.getPivot().location, p.getPivot().old_location);
}
