#ifndef __MINOTAUR_H
#define __MINOTAUR_H

#include "maze.h"
#include "player.h"
#include <string>
#include <Windows.h>

class CMinotaur
{
private:
    COORD m_pos;
    unsigned char m_colour;
    unsigned char m_symbol;
    HANDLE m_hStdin;
    HANDLE m_hStdout;
public:
    void setPos(int x, int y);
    void setPos(COORD);
    void erase(COORD);
    COORD getPos();
    void showMinotaur();
    HANDLE getInputHandle();
	HANDLE getOutputHandle();
    COORD moveMinotaur(CMaze&, int, CPlayer&, std::string&);
    CMinotaur();
};

#endif 