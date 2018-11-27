#include "help.h"
#include "menu.h"
#include <iostream>
#include <Windows.h>

using namespace std;

int showHelpMenu();
void showHelpScreen();
void showCreditScreen();

void helpOptions()
{
    int choice;
    do
    {
        choice = showHelpMenu();
        //What to do after choice has been made
        switch (choice)
        {
        case 1:
            showHelpScreen();
            break;
        case 2:
            showCreditScreen();
            break;
        default:
            break;
        }
    } while (choice != 0);

    return;
}

int showHelpMenu()
{
    int choice = 0;
    int low = 0;
    int high = 2;

    //help and options menu display
    do
    {
        system("cls");
        cout << "HELP AND OPTIONS" << endl;
        cout << "----------------" << endl;
        cout << "1) Display Help Screen" << endl;
        cout << "2) Display Credits" << endl;
        cout << "0) Go Back" << endl;

        choice = getValidNum(low, high, choice);
    } while (choice > high && choice < low);

    return choice;
}

void showHelpScreen()
{
	int choice = 0;
	int low = 0;
	int high = 0;
	do
	{
		system("cls");
		//display help screen
		cout << "HELP" << endl;
		cout << "----" << endl;
		cout << "You are stuck in the Labyrinth, and you must find your way out!" << endl;
		cout << "To do so you must use the arrow keys to manuever yourself to the the trigger in the middle of the maze, to open the exit back where you started." << endl;
		cout << "Be sure to avoid traps and the minotaur - as you don't have much health" << endl;
		cout << "\n0) Go Back" << endl;

		choice = getValidNum(low, high, choice);
	} while (choice != 0);

    return;
}

void showCreditScreen()
{
    system("cls");
    //display credits
    cout << "CREDITS" << endl;
    cout << "-------" << endl;
    cout << "Gameplay\t\t Griffyn Wilkinson" << endl;
	cout << "Music\t\t\t Fleshgod Apocalypse" << endl;

    Sleep(3500);
    return;
}