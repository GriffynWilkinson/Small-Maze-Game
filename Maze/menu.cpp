#include "menu.h"
#include "help.h"
#include "leaderboard.h"
#include "leaderboardMenu.h"
#include "gameMenu.h"
#include "functions.h"
#include "windowSize.h"
#include "scorehandler.h"
#include <iostream>
#include <Windows.h>
#include <mmsystem.h>

using namespace std;

int showMainMenu();

int handleMenu()
{
    //getting info about the current console settings
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(hStdout, &info);
    int choice;
    CLeaderboard leaderboard;
    choice = showMainMenu();
    int level;
    bool windowSize;
    int score;

    //what to do after menu choice has been made
    switch (choice)
    {
    case 1:
        level = showGameMenu();

        //getting rid of the cursor
        info.bVisible = false;
        SetConsoleCursorInfo(hStdout, &info);

        //what to do after choice has been made
        switch (level)
        {
        case 1:
            score = playGame(1);
            if (score > 0)
            getNewScore(leaderboard, score, 1);
            break;
        case 2:
            windowSize = changeWindowSize(100, 45);
            score = playGame(2);
            if (score > 0)
            getNewScore(leaderboard, score, 2);
            break;
        case 3:
            windowSize = changeWindowSize(150, 65);
            score = playGame(3);
            if (score > 0)
            getNewScore(leaderboard, score, 3);
            break;
        default:
            break;
        };

        //making the cursor visible again
        info.bVisible = true;
        SetConsoleCursorInfo(hStdout, &info);
        break;
    case 2:
        helpOptions();
        break;
    case 3:
        level = showLeaderboardMenu();

        //which leaderboard should be displayed
        switch (level)
        {
        case 1:
            leaderboard.displayHighScores(1);
            break;
        case 2:
            leaderboard.displayHighScores(2);
            break;
        case 3:
            leaderboard.displayHighScores(3);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
    return choice;
}

int showMainMenu()
{
    //displays the menu
    int choice = 0;
    int low = 0;
    int high = 3;
    do
    {
        system("cls");
        cout << "MAIN MENU" << endl;
        cout << "---------" << endl;
        cout << "1) Play Game" << endl;
        cout << "2) Help & Options" << endl;
        cout << "3) Leaderboards" << endl;
        cout << "0) Exit Game" << endl;

        choice = getValidNum(low, high, choice);
    } while (choice > high && choice < low);
    return choice;
}

int getValidNum(int low, int high, int choice)
{
    //makes sure you enter a valid number
    do
    {
        cin >> choice;
		mciSendString("play select.wav", 0, 0, 0);

        if (choice < low || choice > high)
        {
            cout << "Please enter a number between " << low << " and " << high << endl;
        }
    } while (choice > high || choice < low);
    return choice;
}