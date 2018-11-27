#include "minotaur.h"
#include "player.h"
#include "maze.h"
#include "MazeTile.h"
#include "myColours.h"
#include <Windows.h>
#include <iostream>

using namespace std;

void CMinotaur::setPos(int x, int y)
{
    m_pos.X = x;
    m_pos.Y = y;
    return;
}

void CMinotaur::setPos(COORD pos)
{
    m_pos = pos;
}

//replace trailing minotaurs with a period
void CMinotaur::erase(COORD oldPos)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, setColour(GRAY, YELLOW));
    SetConsoleCursorPosition(m_hStdout, oldPos);
    cout << '.';
}

COORD CMinotaur::getPos()
{
    return m_pos;
}

void CMinotaur::showMinotaur()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, m_colour);
    m_symbol = 15;
    SetConsoleCursorPosition(m_hStdout, m_pos);
    cout << m_symbol;
}

CMinotaur::CMinotaur()
{
    m_hStdin = GetStdHandle(STD_INPUT_HANDLE);
    m_hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    m_symbol = ' ';
    m_colour = setColour(BLACK, YELLOW);
    setPos(0, 0);
}

HANDLE CMinotaur::getInputHandle()
{
    return m_hStdin;
}

HANDLE CMinotaur::getOutputHandle()
{
    return m_hStdout;
}

COORD CMinotaur::moveMinotaur(CMaze& maze, int numMoves, CPlayer& player, string& gameplay)
{
    COORD oldMinPos = m_pos;
    int num = rand() % 8;

    if (num == 0)
    {
        m_pos.Y -= 1;
    }
    else if (num == 1)
    {
        m_pos.Y += 1;
    }
    else if (num == 2 || num == 3 || num == 4)
    {
        m_pos.X -= 1;
    }
    else if (num == 5 || num == 6 || num == 7)
    {
        m_pos.X += 1;
    }

    //if the minotaur hits a wall dont move him
    if (maze.getTileType(m_pos) == TILE_WALL)
    {
        setPos(oldMinPos);
        showMinotaur();
    }
    else
    {
        //if the minotaur runs over the end symbol don't replace it
        unsigned char symbol = 237;
        if (maze.getTileType(oldMinPos) == TILE_TRIGGER)
        {
            HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(handle, setColour(LIGHT_RED, YELLOW));
            SetConsoleCursorPosition(m_hStdout, oldMinPos);
            cout << symbol;
        }
        //if the minotaur runs over a trap don't replace it
        else if (maze.getTileType(oldMinPos) == TILE_TRAP)
        {
            HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(handle, setColour(BLACK, YELLOW));
            SetConsoleCursorPosition(m_hStdout, oldMinPos);
            cout << 'O';
        }
        else if (oldMinPos.X == player.getPos().X && oldMinPos.Y == player.getPos().Y)
        {
            //if the minotaur steps on you, don't disapear
            unsigned char symbol = 1;
            HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(handle, setColour(BLUE, YELLOW));
            SetConsoleCursorPosition(m_hStdout, oldMinPos);
            cout << symbol;

            //lose 2 health when the minotaur hits you
            mciSendString("play minotaur.wav", 0, 0, 0);
            gameplay = "The minotaur hit you";
            int health = player.getHealth();
            health -= 2;
            player.setHealth(health);
        }
        else
        {
            //get rid of trailing
            erase(oldMinPos);
        }
        setPos(m_pos);
        showMinotaur();
    }
    return m_pos;
}