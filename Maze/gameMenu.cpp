#include "gameMenu.h"
#include "menu.h"
#include "functions.h"
#include "windowSize.h"
#include <iostream>
#include <Windows.h>

using namespace std;

int showGameMenu()
{
	int choice = 0;
	int low = 0;
	int high = 3;

	//help and options menu display
	do
	{
		system("cls");
		cout << "GAME DIFFICULTY" << endl;
		cout << "----------------" << endl;
		cout << "1) Easy" << endl;
		cout << "2) Medium" << endl;
		cout << "3) Hard" << endl;
		cout << "0) Go Back" << endl;

		choice = getValidNum(low, high, choice);
	} while (choice > high && choice < low);

	return choice;
}