#include "GameTimer.h"

//Constructor
GameTimer::GameTimer(void){
	// Start the clock
	start = clock();
	lastTime = GetMS();
}


/*
	Returns the Milliseconds since the timer was started
*/
float GameTimer::GetMS(){
	return GetSecs() *1000.0f;
}


/* Same than above but in seconds*/
float GameTimer::GetSecs(){
	return (float)(clock() - start) / CLOCKS_PER_SEC;
}


float GameTimer::GetTimedMS(){
	float a = GetMS();
	float b = a - lastTime;
	lastTime = a;
	return b;
}

float GameTimer::GetTimedSecs(){
	return GetTimedMS() / 1000.0f;
}