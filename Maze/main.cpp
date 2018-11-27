/***************************************************************************************
Title:    	Maze Game
Course:   	GAM1545 Game Development 1
Section:  	2
Author:   	Griffyn Wilkinson
Date:     	2015/12/16
Description:  	 Creates a “semi-real-time” maze game that displays and plays in the console window
*****************************************************************************************/

#include "menu.h"
#include "cursor.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <Windows.h>
#include <mmsystem.h>
#include <string>
#pragma comment(lib, "winmm.lib")
#include <process.h>

using namespace std;



int g_ticks = 0; // ticks used by timer thread
int g_tickResolution = 100; // How often to tick, in msecs
bool g_isThreadRunning = false; // turns on/off thread

void handleTimer()
{
    g_ticks++;
}

unsigned int __stdcall timerThread(void *p_thread_data)
{
    // Create an event. We don't actually care about the event itself. It will never occur.
    HANDLE event_handle = CreateEvent(NULL, FALSE, FALSE, "my_handle");
    while (g_isThreadRunning) // use the global variable to exit the thread
    {
        // Since the event never happens, the timeout will always occur. Good for us.
        switch (WaitForSingleObject(event_handle, g_tickResolution))
        {
        case WAIT_TIMEOUT:
            handleTimer(); // Call our timer function
            break;
        }
    }
    return(0); // exit thread
}

int main()
{
	//seeding random number
	srand((unsigned int)time(NULL));

    unsigned int thread_id = 0;
    g_isThreadRunning = true;
    _beginthreadex(NULL, 0, timerThread, NULL, 0, &thread_id);

	//start playing menu music
	PlaySound(TEXT("Labyrinth_01.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    //declaring variables
    int choice = 0;
	COORD messagePos;
	messagePos.X = 31;
	messagePos.Y = 5;
	string message = "/////////////////\n                               //THE LABYRINTH//\n                               /////////////////\n\n\n\n\n\n";
	displayMessage(message, messagePos);
	system("pause");

    do
    {
        //displaying the menu
        choice = handleMenu();

    } while (choice != 0);

    g_isThreadRunning = false;

    system("cls");
    cout << "Goodbye!";
    Sleep(1000);
    return 0;
}