#include "leaderboard.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <Windows.h>

using namespace std;

void CLeaderboard::sortHighScores()
{
    //sorting the highScores
    for (int i = 0; i < m_size; i++)
    {
        for (int j = i; j < m_size; j++)
        {
            if (m_highScores[i].getScore() > m_highScores[j].getScore())
            {
                CHighScore tempObject = m_highScores[i];
                m_highScores[i] = m_highScores[j];
                m_highScores[j] = tempObject;
            }
        }
    }
    return;
}

void CLeaderboard::displayHighScores(int difficulty)
{
    bool canRead = false;

    system("cls");
    canRead = readHighScoreFile(difficulty);
    if (canRead == true)
    {
        sortHighScores();
        //displaying table
        cout << "+----------------------+" << endl;
        cout << left << setw(15) << "| NAME" << right << setw(5) << "  SCORE |" << endl;
        for (int i = 0; i < m_size; i++)
        {
            cout << "| " << left << setw(15) << m_highScores[i].getName() << right << setw(5) << m_highScores[i].getScore() << " |" << endl;
        }
        cout << "+----------------------+" << endl;
    }
    else
    {
        for (int i = 0; i < m_size; i++)
        {
            m_highScores[i].reset();
            writeHighScoreFile(difficulty);
        }
        displayHighScores(difficulty);
    }
    system("pause");
}

int CLeaderboard::insertScore(string myName, int myScore, int difficulty)
{
    //declaring variables
    int highScoreSpot = 0;
    bool isInLeaderboard;

    //checking if the score is in the leaderboard
    isInLeaderboard = isScoreInLeaderboard(myScore, difficulty);

    if (isInLeaderboard == true)
    {
        //finding where you are on the table
        for (int i = 0; i < m_size; i++)
        {
            if (myScore < m_highScores[i].getScore())
            {
                highScoreSpot = i;
                break;
            }
        }

        //sorting the table with my score in it
        for (int i = m_size - 1; i > highScoreSpot; i--)
        {
            m_highScores[i] = m_highScores[i - 1];
        }

        m_highScores[highScoreSpot].setName(myName);
        m_highScores[highScoreSpot].setScore(myScore);

        writeHighScoreFile(difficulty);
        displayHighScores(difficulty);

        return (highScoreSpot);
    }
    else
    {
        return -1;
    }
}

bool CLeaderboard::readHighScoreFile(int difficulty)
{
    ifstream hsFile;
    if (difficulty == 1)
    {
        hsFile.open("HighScore.txt", ios::in); //open the easy highscore
    }
    else if (difficulty == 2)
    {
        hsFile.open("HighScoreMed.txt", ios::in); //open the medium highscore
    }
    else if (difficulty == 3)
    {
        hsFile.open("HighScoreHard.txt", ios::in); //open the hard highscore
    }
    int score;
    string name;
    if (!hsFile.is_open())
    {
        return false;
    }

    for (int i = 0; i < m_size; i++)
    {
        hsFile >> name;
        m_highScores[i].setName(name);
        hsFile >> score;
        m_highScores[i].setScore(score);
    }

    hsFile.close();
    return true;
}

void CLeaderboard::writeHighScoreFile(int difficulty)
{
    ofstream hsFile;
    if (difficulty == 1)
    {
        hsFile.open("HighScore.txt", ios::out); //write to the easy maze
    }
    else if (difficulty == 2)
    {
        hsFile.open("HighScoreMed.txt", ios::out); //write to the medium maze
    }
    else if (difficulty == 3)
    {
        hsFile.open("HighScoreHard.txt", ios::out); //write to the hard maze
    }
    if (!hsFile.is_open())
    {
        // file open failed. Exit
        cout << "Unable to open file!" << endl;
        return;
    }

    for (int i = 0; i < m_size; i++)
    {
        hsFile << m_highScores[i].getName() << "\n";
        hsFile << m_highScores[i].getScore() << "\n";
    }

    hsFile.close();
    return;
}

int CLeaderboard::getSize()
{
    return (m_size);
}

bool CLeaderboard::isScoreInLeaderboard(int myScore, int difficulty)
{
    bool canRead = readHighScoreFile(difficulty);
    if (canRead == true)
    {
        if (myScore < m_highScores[m_size - 1].getScore())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        for (int i = 0; i < m_size; i++)
        {
            m_highScores[i].reset();
            writeHighScoreFile(difficulty);
        }
        isScoreInLeaderboard(myScore, difficulty);
    }
}