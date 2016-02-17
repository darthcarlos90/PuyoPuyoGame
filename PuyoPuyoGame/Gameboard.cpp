#include "GameBoard.h"

Gameboard::Gameboard(){
	board = new Matrix<char>(X_SIZE, Y_SIZE);
	// creates an empty gameboard
	for (unsigned int i = 0; i < X_SIZE; i++){
		for (unsigned int j = 0; j < Y_SIZE; j++){
			board->set_element(i, j, ' ');
		}
	}

	changes = false;
}

Gameboard::~Gameboard(){
	delete board;
}

void Gameboard::PrintBoard(){

	if (changes){
		system("cls");
		cout << *board << endl;
		changes = false;
	}
	
}

void Gameboard::SetValue(Location l, char value){
	board->set_element(l.x, l.y, value);
	changes = true;
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

void Gameboard::SetStaticPair(Pair p){
	static_pieces.push_back(p.getP1());
	static_pieces.push_back(p.getPivot());
	SetValue(p.getP1().location, p.getP1().value);
	SetValue(p.getPivot().location, p.getPivot().value);
}

int Gameboard::CheckPoints(){

}

int Gameboard::CalculatePoints(Location l, char value){
	int points = 0;
	return points;
}

/* 
	Checks the elements on the vector and the matrix, if there is any adjacent element,
	the function calls itself with an increase in level.
	If the level is 4, it starts deleting itself
*/
int Gameboard::TrackAdjacents(Location l, char value){
	// pass an empty vector
	vector<Location> adjacents = AdjacentSimilar(l, value, vector<Location>());
	for (unsigned int i = 0; i < adjacents.size(); i++){
		vector<Location> temp = AdjacentSimilar(adjacents[i], value, adjacents);
		if(temp.size() > 0) adjacents.insert(adjacents.end(), temp.begin(), temp.end()); //insert at the end of the vector
	}

	// If there are more than 4 elements, destroy them from the board
	if (adjacents.size() > 4){
		for (unsigned int i = 0; i < adjacents.size(); i++){
			board->set_element(adjacents[i].x, adjacents[i].y, ' '); // TODO: Left here

		}
	}


	return adjacents.size();

}
/*
	Gets all the adjacents that have the same value
	The checked parameter is a parameter that lets the method know which elements have been checked
*/
vector<Location> Gameboard::AdjacentSimilar(Location l, char value, vector<Location> checked){
	vector<Location> result; // the result elements
	char type;

	// to ease writting
	int x = l.x;
	int y = l.y;

	// To see if there is any available element at the left
	if (y - 1 >= 0){
		type = board->get_element(x, y - 1);
		if (type == value){
			Location toAdd(x, y - 1);
			if (std::find(checked.begin(), checked.end(), toAdd) != checked.end()){} // if it is contained, do nothing
			else {
				result.push_back(toAdd);
			}
		}
	}

	// To see if there is any element above
	if (x - 1 >= 0){
		type = board->get_element(x - 1, y);
		if (type == value){
			Location toAdd(x - 1, y);
			if (std::find(checked.begin(), checked.end(), toAdd) != checked.end()){} // if it is contained, do nothing
			else {
				result.push_back(toAdd);
			}
		}
	}

	// See if there is any element below
	if (x + 1 < board->get_x_size()){
		type = board->get_element(x + 1, y);
		if (type == value){
			Location toAdd(x + 1, y);
			if (std::find(checked.begin(), checked.end(), toAdd) != checked.end()){} // if it is contained, do nothing
			else {
				result.push_back(toAdd);
			}
		}
	}

	// See if there is any element to the right
	if (y + 1 < board->get_y_size()){
		type = board->get_element(x, y + 1);
		if (type == value){
			Location toAdd(x, y + 1);
			if (std::find(checked.begin(), checked.end(), toAdd) != checked.end()){} // if it is contained, do nothing
			else {
				result.push_back(toAdd);
			}
		}
	}


	return result;
	
}