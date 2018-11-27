#include "player.h"
#include "MazeTile.h"
#include "myColours.h"
#include "maze.h"
#include <Windows.h>
#include <iostream>

using namespace std;

void CPlayer::setPos(int x, int y)
{
	m_pos.X = x;
	m_pos.Y = y;
	return;
}

void CPlayer::setPos(COORD pos)
{
    m_pos = pos;
}

//replace the trailing player with a period
void CPlayer::erase(COORD oldPos, CMaze& maze)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    //If you walk over the start symbol, a trap, or the trigger, don't replace it with a period
    if (maze.getTileType(oldPos) == TILE_START)
    {
        SetConsoleTextAttribute(handle, setColour(LIGHT_RED, YELLOW));
        SetConsoleCursorPosition(m_hStdout, oldPos);
        cout << 'S';
    }
    else if (maze.getTileType(oldPos) == TILE_TRAP)
    {
        SetConsoleTextAttribute(handle, setColour(WHITE, YELLOW));
        SetConsoleCursorPosition(m_hStdout, oldPos);
        cout << 'O';
    }
    else if (maze.getTileType(oldPos) == TILE_TRIGGER)
    {
        unsigned char symbol = 237;
        SetConsoleTextAttribute(handle, setColour(BLACK, YELLOW));
        SetConsoleCursorPosition(m_hStdout, oldPos);
        cout << symbol;
    }
    else
    {  
        SetConsoleTextAttribute(handle, setColour(GRAY, YELLOW));
        SetConsoleCursorPosition(m_hStdout, oldPos);
        cout << '.';
        SetConsoleCursorPosition(m_hStdout, m_pos);
    }
}

COORD CPlayer::getPos()
{
	return m_pos;
}

void CPlayer::showPlayer()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, m_colour);
	m_symbol = 1;
	SetConsoleCursorPosition(m_hStdout, m_pos);
	cout << m_symbol;
}

CPlayer::CPlayer()
{
	m_hStdin = GetStdHandle(STD_INPUT_HANDLE);
	m_hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	m_symbol = ' ';
	m_colour = setColour(BLUE, YELLOW);
	m_health = 3;
    setPos(0, 0);
}

HANDLE CPlayer::getInputHandle()
{
    return m_hStdin;
}

HANDLE CPlayer::getOutputHandle()
{
	return m_hStdout;
}

bool CPlayer::hitTrigger(COORD pos)
{
	CMaze maze;
	if (maze.getTileType(pos) == TILE_TRIGGER)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int CPlayer::getHealth()
{
	return m_health;
}

void CPlayer::setHealth(int health)
{
    m_health = health;
}