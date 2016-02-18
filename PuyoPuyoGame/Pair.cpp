#include "Pair.h"

Pair::Pair(char val1, char val2){
	p1.location.x = X_START;
	p1.location.y = Y_START;
	p1.value = val1;

	p2.location.x = X_START;
	p2.location.y = Y_START + 1;
	p2.value = val2;

	moving = true;
	state = P_LEFT;
}

Pair::Pair(const Pair& p){
	this->p1 = p.p1;
	this->p2 = p.p2;
	this->moving = p.moving;
}

Pair::~Pair(){
	// Empty destructor for now
}

void Pair::Shift(){ // Left piece shifts, the other one stays as pivot
	// p2 is the pivot, p1 moves
	switch (state){
	case P_LEFT:
		if (p1.location.x < X_SIZE){
			// if p1 is at the left of p2
			// AND it can be shifted
			p1.old_location = p1.location;
			p1.location.x++;
			p1.location.y++;
			state = P_DOWN;
		}
		break;
	case P_DOWN:
		if (p1.location.y < Y_SIZE){
			// If p1 is below p2, and it can be shifted
			p1.old_location = p1.location;
			p1.location.x--;
			p1.location.y++;
			state = P_RIGHT;
		}
		break;
	case P_RIGHT:
		if (p1.location.x > 0){
			// If p1 is to the right of p2, and it can be shifted
			p1.old_location = p1.location;
			p1.location.x--;
			p1.location.y--;
			state = P_UP;
		}
		break;
	case P_UP:
		if (p1.location.y > 0){
			// If p1 is above p2 and can be shifted
			p1.old_location = p1.location;
			p1.location.x++;
			p1.location.y--;
			state = P_LEFT;
		}
		break;
	}
}


void Pair::Move(int direction){
	switch (direction){
	case DOWN:
	default:
		if (p1.location.x < X_SIZE && p2.location.x < X_SIZE){
			p1.old_location = p1.location;
			p2.old_location = p2.location;
			p1.location.x++;
			p2.location.x++;
		}
		break;
	case LEFT:
		if (p1.location.y > 0 && p2.location.y > 0){
			p1.old_location = p1.location;
			p2.old_location = p2.location;
			p1.location.y--;
			p2.location.y--;
		}
		break;
	case RIGHT:
		if (p1.location.y < Y_SIZE && p2.location.y < Y_SIZE){
			p1.old_location = p1.location;
			p2.old_location = p2.location;
			p1.location.y++;
			p2.location.y++;
		}
		break;
	}
}


Piece Pair::getLowest(bool* both){
	if (p1.location.x == p2.location.x){
		*both = true;
		return p2;
	}
		
	if (p1.location.x < p2.location.x){
		*both = false;
		return p2;
	}
	if (p1.location.x > p2.location.x) {
		*both = false;
		return p1;
	}
}

Piece Pair::getLeftMost(bool* both){
	if (p1.location.y == p2.location.y){
		*both = true;
		return p2;
	}

	if (p1.location.y < p2.location.y){
		*both = false;
		return p1;
	}

	if (p1.location.y > p2.location.y){
		*both = false;
		return p2;
	}
}

Piece Pair::getRightMost(bool* both){
	if (p1.location.y == p2.location.y){
		*both = true;
		return p2;
	}

	if (p1.location.y < p2.location.y){
		*both = false;
		return p2;
	}

	if (p1.location.y > p2.location.y){
		*both = false;
		return p1;
	}
}

void Pair::ChangeP1OldLocation(Location newLoc){
	p1.old_location = newLoc;
}

void Pair::ChangeP1Location(Location newLoc){
	p1.location = newLoc;
}

void Pair::ChangePivotOldLocation(Location newLoc){
	p2.old_location = newLoc;
}

void Pair::ChangePivotLocation(Location newLoc){
	p2.location = newLoc;
}
