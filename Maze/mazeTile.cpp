#include "MazeTile.h"
#include "myColours.h"
#include <iostream>
#include <Windows.h>

using namespace std;

void CMazeTile::showTile()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, m_colour);
    cout << m_symbol;
    return;
}

void CMazeTile::setTileFromCharacter(char mazeIndex)
{
    //making the maze look prettier
    switch (mazeIndex)
    {
    case 'X':
        m_type = TILE_WALL;
        m_symbol = 219;
		m_colour = setColour(RED, BLACK);
        break;
    case ' ':
        m_type = TILE_FLOOR;
		m_symbol = '.';
		m_colour = setColour(GRAY, YELLOW); 
        break;
    case 'S':
        m_type = TILE_START;
        m_symbol = 'S';
		m_colour = setColour(LIGHT_RED, YELLOW);
        break;
    case 'T':
        m_type = TILE_TRIGGER;
        m_symbol = 237;
		m_colour = setColour(LIGHT_RED, YELLOW);
        break;
	case 'E':
		m_type = TILE_END;
		m_symbol = 219;
		m_colour = setColour(RED, BLACK);
		break;
    case 'P':
        m_type = TILE_PLAYER;
        break;
    case 'M':
        m_type = TILE_MINOTAUR;
        break;
	case ',':
		m_type = TILE_TRAP;
		m_symbol = 'O';
		m_colour = setColour(BLACK, YELLOW);
		break;
    default:
        m_type = TILE_ERROR;
        m_symbol = 'Q';
        break;
    }

    return;
}

CMazeTile::CMazeTile()
{
    m_colour = ' ';
    m_type = TILE_ERROR;
    m_symbol = ' ';
    return;
}

Tiles CMazeTile::getTileType()
{
    return m_type;
}

void CMazeTile::setTile(unsigned char symbol, unsigned char colour)
{
	m_symbol = symbol;
    m_colour = colour;
	return;
}

unsigned char CMazeTile::getSymbol()
{
	return m_symbol;
}