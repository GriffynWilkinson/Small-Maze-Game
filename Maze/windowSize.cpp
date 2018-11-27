#include "windowSize.h"
#include <Windows.h>
#include <iostream>

using namespace std;

bool changeWindowSize(int width, int height)
{
	HANDLE hStdout;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD maxSize = GetLargestConsoleWindowSize(hStdout);
	if (maxSize.X < width || maxSize.Y < height)
	{
		// Error: window cannot be resized to this
		cout << "changeWindowSize: Exceeds max size X:" << maxSize.X << ", Y:" << maxSize.Y << endl;
		return false;
	}

	// Get current size of screen buffer.  curWindow.dwSize will be current buffer size
	CONSOLE_SCREEN_BUFFER_INFO curWindow;
	GetConsoleScreenBufferInfo(hStdout, &curWindow);

	struct _SMALL_RECT temp;
	COORD coord = { width, height };

	// Resize: Window size can NEVER exceed buffer
	if (width > curWindow.dwSize.X && height > curWindow.dwSize.Y)
	{

		// If we are increasing both width and height
		temp = { (SHORT)0, (SHORT)0, (SHORT)(width - 1), (SHORT)(height - 1) };
		SetConsoleScreenBufferSize(hStdout, coord); // buffer
		SetConsoleWindowInfo(hStdout, true, &temp); // window
	}
	else if (width < curWindow.dwSize.X && height < curWindow.dwSize.Y)
	{
		// Decreasing both width and hieght
		temp = { (SHORT)0, (SHORT)0, (SHORT)(width - 1), (SHORT)(height - 1) };
		SetConsoleWindowInfo(hStdout, true, &temp); // window
		SetConsoleScreenBufferSize(hStdout, coord); // buffer
	}
	else if (width >= curWindow.dwSize.X && height < curWindow.dwSize.Y)
	{
		temp = { (SHORT)0, (SHORT)0, (SHORT)(curWindow.dwSize.X - 1), (SHORT)(height - 1) }; // first, reduce only the height of the window
		SetConsoleWindowInfo(hStdout, true, &temp);

		SetConsoleScreenBufferSize(hStdout, coord); // increase to buffer to the desired size
		temp = { (SHORT)0, (SHORT)0, (SHORT)(width - 1), (SHORT)(height - 1) }; // Set window to match new buffer
		SetConsoleWindowInfo(hStdout, true, &temp);
	}
	else
	{
		// Decreasing width and same or greater height
		temp = { (SHORT)0, (SHORT)0, (SHORT)(width - 1), (SHORT)(curWindow.dwSize.Y - 1) }; // smaller width, same height
		SetConsoleWindowInfo(hStdout, true, &temp); // Shrink window
		SetConsoleScreenBufferSize(hStdout, coord); // increase to desired size
		temp = { (SHORT)0, (SHORT)0, (SHORT)(width - 1), (SHORT)(height - 1) }; // Set window to match new buffer
		SetConsoleWindowInfo(hStdout, true, &temp);
	}
	return true;
}