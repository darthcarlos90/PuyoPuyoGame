/*
	This class will handle all the dealings with the console in the hopes to make a prettier
	application.
	This class is based on the console tutorials from: http://benryves.com/tutorials/?t=winconsole
*/

#pragma once
#include <string>
#include <Windows.h>
#include "Utils.h"



class Window{
public:
	Window();
	~Window();

	HANDLE getWritter() { return wHnd; }
	HANDLE getReader() { return rHnd; }

	void MakeFontSmall();
	void MakeFontBig();

private:
	void changeFont(int x, int y);
	// The window handlers
	HANDLE wHnd;
	HANDLE rHnd;
};