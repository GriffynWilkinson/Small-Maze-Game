#ifndef __HIGHSCORE_H
#define __HIGHSCORE_H

#include <string>

//declaring my high score class with members name and score
class CHighScore
{
private:
    std::string m_name;
    int m_score;
public:
    void setScore(int);
    void setName(std::string);
    int getScore();
    std::string getName();
    void reset();
};

#endif