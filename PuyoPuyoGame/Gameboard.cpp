#include "GameBoard.h"

Gameboard::Gameboard(){ // Constructor
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

/*
	"Renders" the board on the console. 
	The inputs are the score (so it can print it at some point) and the
	writter to the console.
*/
void Gameboard::PrintBoard(int score, HANDLE writter){
	// If there was any change on the matrix
	if (changes){
		
		//Create a "back buffer" and first "render" it there
		CHAR_INFO backBuffer[WINDOW_X * WINDOW_Y];

		// "Clear" the buffer with green colour
		CHAR_INFO clearing;
		clearing.Char.AsciiChar = ' ';
		clearing.Attributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
		for (unsigned int i = 0; i < (WINDOW_X * WINDOW_Y); i++){
			backBuffer[i] = clearing;
		}


		////Move the matrix info into the "back buffer"
		for (unsigned int i = 0; i < board->get_x_size(); i++){
			for (unsigned int j = 0; j < board->get_y_size(); j++){
				
				char element = board->get_element(i, j);
				CHAR_INFO character;
				// Each internall character represents a different figure to show
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

				// borderx and border y represent in what specific location of the console 
				// we are printing the board
				int borderx = (WINDOW_X / 2) - (X_SIZE / 2);
				int bordery = (WINDOW_Y / 2) - (Y_SIZE / 2);

				// "render" to the back buffer
				backBuffer[(j + borderx) + WINDOW_X * (i + bordery)] = character;

			}
		}

		// We are not setting the character buffer size and window size of the area we are rendering
		COORD charBufSize = { WINDOW_X, WINDOW_Y };
		COORD characterPos = { 0, 0 };
		SMALL_RECT writeArea = { 0, 0, WINDOW_X - 1, WINDOW_Y - 1};
 
		// "Bring" the "back buffer" to the "front"
		WriteConsoleOutputA(writter, backBuffer, charBufSize, characterPos, &writeArea); 
		
		changes = false; // reset the changes flag
	}
	
}

// Pretty much self explanatory
void Gameboard::SetValue(Location l, char value){
	board->set_element(l.x, l.y, value);
	changes = true;
}

// The same as above
void Gameboard::MovePiece(char value, Location newLocation){
	SetValue(newLocation, value); // Re-use ;)
}

// Checks if a location is occupied
bool Gameboard::isOccuppied(Location l){
	// So it can't go out of the borders
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

// Depending on where do you want to move, checks wether that spot is occupied
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

// Moves the pair into the location stated on the struct (see utils.h)
// This method assumes that the old location is where the pair currently is, and location is where the pair should move
void Gameboard::MovePair(Pair p){
	// First, delete them from their old location
	DeleteValue(p.getP1().old_location);
	DeleteValue(p.getPivot().old_location);

	// Now print them on the new location
	MovePiece(p.getP1().value, p.getP1().location);
	MovePiece(p.getPivot().value, p.getPivot().location);
}

// Stops a pair from moving
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

	// Add them to the static pices vector
	static_pieces.push_back(p.getP1());
	static_pieces.push_back(p.getPivot());
	
	// Set the values on the matrix
	SetValue(p.getP1().location, p.getP1().value);
	SetValue(p.getPivot().location, p.getPivot().value);
}

// This method calculates the points based on the difficulty
int Gameboard::CheckPoints(double difficulty){
	int points = 0;
	// If there are enough pieces to start checking for color matches
	if (static_pieces.size() >= 4){
		// For each static piece
		for (unsigned int i = 0; i < static_pieces.size(); i++){
			// Calculate the possible points in case that piece is part of a series of matching pieces
			// This proces deletes the matching pieces
			int pointsFromPiece = CalculatePoints(static_pieces[i].location, static_pieces[i].value);
			if (pointsFromPiece > 0) i--; // so that this step is repeated, since the element has been deleted from the list
			points += pointsFromPiece; // increase points
		}
	}
	// Increase the points based on the difficulty
	if (difficulty == MEDIUM) points *= 2;
	else if (difficulty == HARD) points *= 3;
	else if (difficulty == INSANE) points *= 5;

	return points;
}

/*
	Helper method that helps find matching values at a certain location with a certain value.
*/
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
	Helper method: Gets the adjacent elements that are equal to the location l.
	Then starts looking through the adjacent elements for more matching pieces
	until it finishes.
*/
int Gameboard::TrackAdjacents(Location l, char value){
	// pass an empty vector
	vector<Location> adjacents = AdjacentSimilar(l, value, vector<Location>());
	for (unsigned int i = 0; i < adjacents.size(); i++){
		vector<Location> temp = AdjacentSimilar(adjacents[i], value, adjacents);
		if(temp.size() > 0) adjacents.insert(adjacents.end(), temp.begin(), temp.end()); //insert at the end of the vector
	}

	// If there are more than 4 matching elements, destroy them from the board and remove them from the vector
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

	// Uncoment for debugging
	/*if (index == -1)
		cout << "Error" << endl;*/
	
	static_pieces.erase(static_pieces.begin() + index);
}


/*
	Simply move a piece from old location to new location.
*/
void Gameboard::move_piece(Piece p){
	DeleteValue(p.old_location);
	MovePiece(p.value, p.location);
}

/* Delete a value from the board*/
void Gameboard::DeleteValue(Location old_l){
	if (old_l.x != -1)
		board->set_element(old_l.x, old_l.y, ' ');
}