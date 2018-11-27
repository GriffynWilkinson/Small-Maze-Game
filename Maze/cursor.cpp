#include "cursor.h"
#include "MazeTile.h"
#include "myColours.h"
#include "player.h"
#include <Windows.h>
#include <iostream>
#include <iomanip>

using namespace std;

//function to display a message on the screen
void displayMessage(string message, COORD pos)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hStdout, pos);
    cout << message;
}

void displayMessage(string healthMessage, int health, string message, string timeMessage, int time, string numMoves, int num, COORD pos, CPlayer& player)
{
    unsigned char heart[3] = { 3, 3, 3 };
    unsigned char colour = ' ';
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hStdout, pos);
    cout << healthMessage;
    colour = setColour(LIGHT_RED, BLACK);
    SetConsoleTextAttribute(hStdout, colour);

    //determining if you need to display a space or a heart
    if (player.getHealth() == 3)
    {
        cout << heart[0] << " " << heart[1] << " " << heart[2] << " ";
    }
    else if (player.getHealth() == 2)
    {
        cout << heart[0] << " " << heart[1] << "   ";
    }
    else if (player.getHealth() == 1)
    {
        cout << heart[0] << "     ";
    }
    else
    {
        cout << "      ";
    }

    setColourBack();
    cout << right << setw(35) << message << right << setw(10) << timeMessage << time << numMoves << num;
}