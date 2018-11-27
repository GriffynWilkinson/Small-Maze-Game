#include "leaderboard.h"
#include "leaderboardMenu.h"
#include "menu.h"
#include <iostream>
#include <Windows.h>

using namespace std;

int showLeaderboardMenu()
{
    int choice = 0;
    int low = 0;
    int high = 3;

    //leaderboard menu display
    do
    {
        system("cls");
        cout << "LEADERBOARDS" << endl;
        cout << "------------" << endl;
        cout << "1) Display Easy Leaderboard" << endl;
        cout << "2) Display Medium Leaderboard" << endl;
        cout << "3) Display Hard Leaderbaord" << endl;
        cout << "0) Go Back" << endl;

        choice = getValidNum(low, high, choice);
    } while (choice > high && choice < low);

    return choice;
}