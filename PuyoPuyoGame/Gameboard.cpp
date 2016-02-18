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

void Gameboard::PrintBoard(int score, HANDLE writter){

	if (changes){
		system("cls");
		//cout << *board << endl;
		//Create a "back buffer" and put the info there
		CHAR_INFO backBuffer[80 * 50];

		//Move the matrix info into the back buffer
		for (unsigned int i = 0; i < board->get_x_size(); i++){
			for (unsigned int j = 0; j < board->get_y_size(); j++){
				char element = board->get_element(i, j);
				CHAR_INFO character;
				
				switch (element){
				case '1':
					character.Char.AsciiChar = 0x04;
					character.Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY;
					break;
				case '2':
					character.Char.AsciiChar = 0x1E;
					character.Attributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY;
					break;
				case '3':
					character.Char.AsciiChar = 0x0E;
					character.Attributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY;
					break;
				case '4':
					character.Char.AsciiChar = 0x01;
					character.Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY;
					break;
				case ' ':
					character.Char.AsciiChar = element;
					character.Attributes =  BACKGROUND_BLUE |BACKGROUND_GREEN |BACKGROUND_RED | BACKGROUND_INTENSITY;
					break;
				}

				backBuffer[j + 80 * i] = character;

				
			}

		}

		COORD charBufSize = { 80, 50 };
		COORD characterPos = { 0, 0 };
		SMALL_RECT writeArea = { 0, 0, 79, 49 };

		WriteConsoleOutputA(writter, backBuffer, charBufSize, characterPos, &writeArea);
		changes = false;
		//cout << "Score: " << score << endl;
	}
	
}

void Gameboard::SetValue(Location l, char value){
	board->set_element(l.x, l.y, value);
	changes = true;
}

void Gameboard::MovePiece(char value, Location newLocation){
	SetValue(newLocation, value); // Re-use ;)
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
	DeleteValue(p.getP1().old_location);
	DeleteValue(p.getPivot().old_location);
	MovePiece(p.getP1().value, p.getP1().location);
	MovePiece(p.getPivot().value, p.getPivot().location);
}

void Gameboard::SetStaticPair(Pair p){
	// Before setting a static pair, see if it can move further down
	while (canMove(p.getP1().location, DOWN)){
		p.ChangeP1OldLocation(p.getP1().location);
		p.ChangeP1Location(Location(p.getP1().location.x + 1, p.getP1().location.y));
		DeleteValue(p.getP1().old_location);
	}

	while (canMove(p.getPivot().location, DOWN)){
		p.ChangePivotOldLocation(p.getPivot().location);
		p.ChangePivotLocation(Location(p.getPivot().location.x + 1, p.getPivot().location.y));
		DeleteValue(p.getPivot().old_location);
	}
	static_pieces.push_back(p.getP1());
	static_pieces.push_back(p.getPivot());
	
	SetValue(p.getP1().location, p.getP1().value);
	SetValue(p.getPivot().location, p.getPivot().value);
}

int Gameboard::CheckPoints(double difficulty){
	int points = 0;
	if (static_pieces.size() >= 4){
		for (unsigned int i = 0; i < static_pieces.size(); i++){
			int pointsFromPiece = CalculatePoints(static_pieces[i].location, static_pieces[i].value);
			if (pointsFromPiece > 0) i--; // so that this step is repeated, since the element has been deleted from the list
			points += pointsFromPiece;
		}
	}
	if (difficulty == MEDIUM) points *= 2;
	else if (difficulty == HARD) points *= 3;

	return points;
	
}

int Gameboard::CalculatePoints(Location l, char value){
	int points = 0;
	// Get how many contiguous elements are with this element
	int contiguous = TrackAdjacents(l, value);
	if (contiguous >= 4){
		// If there are 4 contiguous elements, it means some elements where removed from the board
		// First calculate the points
		int difference = contiguous - 4;
		points = 40 + (difference * 20);


		// Then, move elements down (if available)
		for (unsigned int i = 0; i < static_pieces.size(); i++){
			while (canMove(static_pieces[i].location, DOWN)){
				Location oldLoc = static_pieces[i].location;
				Location newLoc(oldLoc.x + 1, oldLoc.y);
				DeleteValue(oldLoc);
				MovePiece(static_pieces[i].value, newLoc);
				static_pieces[i].location = newLoc;
				static_pieces[i].old_location = oldLoc;
			}
		}

	}
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

	// If there are more than 4 elements, destroy them from the board and remove them from the vector
	if (adjacents.size() >= 4){
		for (unsigned int i = 0; i < adjacents.size(); i++){
			board->set_element(adjacents[i].x, adjacents[i].y, ' ');
			DeleteLocation(adjacents[i]);
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

/* Helper method to delete locations from the static_pieces vector */
void Gameboard::DeleteLocation(Location l){
	int index = -1;
	for (unsigned int i = 0; i < static_pieces.size(); i++){
		if (static_pieces[i].location == l){
			index = i;
			break;
		}
	}
	if (index == -1)
		cout << "Holis" << endl;
	
	static_pieces.erase(static_pieces.begin() + index);
}

void Gameboard::move_piece(Piece p){
	DeleteValue(p.old_location);
	MovePiece(p.value, p.location);
}

void Gameboard::DeleteValue(Location old_l){
	if (old_l.x != -1)
		board->set_element(old_l.x, old_l.y, ' ');
}