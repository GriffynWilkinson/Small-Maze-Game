#include "highscore.h"
#include <string>
#include <sstream>

using namespace std;

void CHighScore::setScore(int score)
{
    m_score = score;
    return;
}

int CHighScore::getScore()
{
    return (m_score);
}

void CHighScore::setName(string name)
{
    m_name = name;
    return;
}

string CHighScore::getName()
{
    return (m_name);
}

void CHighScore::reset()
{
    m_score = 99999;
    m_name = "none";
    return;
}