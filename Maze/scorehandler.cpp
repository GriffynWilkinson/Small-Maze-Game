#include "leaderboard.h"
#include "cursor.h"
#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

void getNewScore(CLeaderboard &leaderboard, int numMoves, int difficulty)
{
    //getting info about the current console settings
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(hStdout, &info);

    //making the cursor visible again
    info.bVisible = true;
    SetConsoleCursorInfo(hStdout, &info);

    //declaring variables
    int myScore;
    string myName;
    bool isInLeaderboard;
    int index;

    myScore = numMoves;

    leaderboard.sortHighScores();
    //Checking if you made the highscore table
    isInLeaderboard = leaderboard.isScoreInLeaderboard(myScore, difficulty);
    if (isInLeaderboard == true)
    {
		system("cls");
		cout << "Congratulations! Your score of " << numMoves << " made it to the highscore table" << endl;
        cout << "What is your name? ";
        cin >> myName;

        //Putting you in the highscore table
        index = leaderboard.insertScore(myName, myScore, difficulty);
    }
    else
    {
		system("cls");
        cout << "I'm sorry my good sir, your score of " << numMoves << " did not quite make the leaderboards." << endl;
        cout << "Perhaps when you suck less you will make it." << endl;
        system("pause");
    }
    
    return;
}