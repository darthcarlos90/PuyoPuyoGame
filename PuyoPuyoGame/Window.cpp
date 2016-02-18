#include "Window.h"


Window::Window(int x_size, int y_size):
x_size(x_size), y_size(y_size)
{
	// Set up the handles
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	rHnd = GetStdHandle(STD_INPUT_HANDLE);

	SetConsoleTitle(TEXT("PUYO PUYO GAME"));

	// Window size
	SMALL_RECT windowSize = { 0, 0, this->x_size, this->y_size };

	// Set the window size
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);

	COORD bufferSize = { 80, 50 }; // Lets change the buffer size to get rid of the extra space
	SetConsoleScreenBufferSize(wHnd, bufferSize);
}

Window::~Window(){}