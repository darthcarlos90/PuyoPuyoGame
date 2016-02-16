#include "Pair.h"

Pair::Pair(char val1, char val2){
	p1.location.x = X_START;
	p1.location.y = Y_START;
	p1.value = val1;

	p2.location.x = X_START;
	p2.location.y = Y_START + 1;
	p2.value = val2;

	moving = true;
}

Pair::~Pair(){
	// Empty destructor for now
}

void Pair::Shift(){ // Left piece shifts, the other one stays as pivot
	// p2 is the pivot, p1 moves
	if (p1.location.y < p2.location.y && p1.location.x < X_SIZE){
		// if p1 is at the left of p2
		// AND it can be shifted
		p1.old_location = p1.location;
		p1.location.x++;
		p1.location.y++;
	}
	else if (p1.location.x > p2.location.x && p1.location.y < Y_SIZE){
		// If p1 is below p2, and it can be shifted
		p1.old_location = p1.location;
		p1.location.x--;
		p1.location.y++;
	}
	else if (p1.location.y > p2.location.y && p1.location.x > 0){
		// If p1 is to the right of p2, and it can be shifted
		p1.old_location = p1.location;
		p1.location.x--;
		p1.location.y--;
	}
	else if (p1.location.x < p2.location.x && p1.location.y > 0){
		// If p1 is above p2 and can be shifted
		p1.old_location = p1.location;
		p1.location.x++;
		p2.location.y--;
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