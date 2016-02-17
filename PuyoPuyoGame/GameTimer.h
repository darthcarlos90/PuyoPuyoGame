/*
	Small timer class created to be able to separate spawning and movement of the pieces from the
	framerate.
*/

#include <time.h>

class GameTimer{
public:
	GameTimer(void);
	~GameTimer(void) {}

	// How many milliseconds have passed since the timer was created
	float GetMS();
	float GetSecs(); // same as above but in seconds

	// How many milliseconds have passed since the las time this function was called
	float GetTimedMS();
	float GetTimedSecs(); // Same as above but in seconds

protected:
	clock_t start; // when the timer started

	float lastTime; // Las time getTimedMS() was called


};