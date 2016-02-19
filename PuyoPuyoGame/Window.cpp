#include "Window.h"


Window::Window()
{
	// Set up the handles
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	rHnd = GetStdHandle(STD_INPUT_HANDLE);

	SetConsoleTitle(TEXT("PUYO PUYO GAME"));

	COORD bufferSize = { WINDOW_X, WINDOW_Y }; // Lets change the buffer size to get rid of the extra space
	SetConsoleScreenBufferSize(wHnd, bufferSize);

	// Window size
	SMALL_RECT windowSize = { 0, 0, WINDOW_X- 1, WINDOW_Y- 1 };

	// Set the window size
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);

	



	CONSOLE_FONT_INFOEX fontInfo = { sizeof (CONSOLE_FONT_INFOEX) };
	bool value = GetCurrentConsoleFontEx(wHnd, 0, &fontInfo);
	fontInfo.dwFontSize.X = 12;
	fontInfo.dwFontSize.Y = 16;
	bool value2 =  SetCurrentConsoleFontEx(wHnd, 0, &fontInfo);


}

Window::~Window(){}