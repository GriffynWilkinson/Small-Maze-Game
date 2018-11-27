#ifndef __PLAYER_H
#define __PLAYER_H

#include "maze.h"
#include <Windows.h>

class CPlayer
{
private:
	COORD m_pos;
	unsigned char m_colour;
	unsigned char m_symbol;
	HANDLE m_hStdin;
	HANDLE m_hStdout;
	int m_health;
public:
	void setPos(int x, int y);
    void setPos(COORD);
    void erase(COORD, CMaze&);
	COORD getPos();
	void showPlayer();
	HANDLE getInputHandle();
	HANDLE getOutputHandle();
	bool hitTrigger(COORD);
	int getHealth();
    void setHealth(int);
	CPlayer();
};

#endif 