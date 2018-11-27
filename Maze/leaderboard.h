#ifndef __LEADERBOARD_H
#define __LEADERBOARD_H

#include "highscore.h"
#include <string>

class CLeaderboard
{
private:
    static const int m_size = 15;
    CHighScore m_highScores[m_size];
public:
    void sortHighScores();
    void displayHighScores(int);
    bool readHighScoreFile(int);
    void writeHighScoreFile(int);
    int insertScore(std::string, int, int);
    int getSize();
    bool isScoreInLeaderboard(int, int);
};

#endif