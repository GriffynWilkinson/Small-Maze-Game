#ifndef __MAZE_H
#define __MAZE_H

#include "MazeTile.h"
#include <Windows.h>

class CMaze
{
private:
	int m_columns;
	int	m_rows;
    CMazeTile *m_theMaze;
public:
    void loadMaze(int);
    void showMaze();
    int getSize();
    int getRows();
    int getTileType(COORD);
    COORD getCoord(int);
    CMaze();
    ~CMaze();
};
#endif