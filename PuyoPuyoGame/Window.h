/*
	This class will handle all the dealings with the console in the hopes to make a prettier
	application.
	This class is based on the console tutorials from: http://benryves.com/tutorials/?t=winconsole
*/

#pragma once
#include <string>
#include <Windows.h>

class Window{
public:
	Window( int x_size = 70, int y_size = 49);
	~Window();

	HANDLE getWritter() { return wHnd; }
	HANDLE getReader() { return rHnd; }

private:
	// The sizes of the screen
	int x_size;
	int y_size;

	// The window handlers
	HANDLE wHnd;
	HANDLE rHnd;
};