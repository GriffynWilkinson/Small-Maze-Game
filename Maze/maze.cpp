#include "Maze.h"
#include "MazeTile.h"
#include "player.h"
#include "cursor.h"
#include "functions.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

void CMaze::loadMaze(int choice)
{
    ifstream mazeFile;
    if (choice == 1)
    {
        mazeFile.open("maze.txt", ios::in); //open the easy maze file for reading
    }
    else if (choice == 2)
    {
        mazeFile.open("medMaze.txt", ios::in); //open the medium maze file for reading
    }
    else if (choice == 3)
    {
        mazeFile.open("hardMaze.txt", ios::in); //open the hard maze file for reading
    }
    if (!mazeFile.is_open())
    {
        // file open failed. Exit
        cout << "Unable to open file for reading!" << endl;
        return;
    }

	//reead in the number of rows and columns
    mazeFile >> m_rows;
    mazeFile >> m_columns;

    m_theMaze = new CMazeTile[m_rows * m_columns];

	//ignore the character return
    mazeFile.ignore(1000000, '\n');

    string line;
    for (int i = 0; i < m_rows; i++)
    {
        getline(mazeFile, line);

        //error check if line in .txt is too small or too big
        if (line.size() != m_columns)
        {
            cout << "Incorrect # of characters in row index " << i << endl;
        }

		//replace what the maze looks like in the .txt with nicer characters
        for (int j = 0; j < m_columns; j++)
        {
            m_theMaze[i * m_columns + j].setTileFromCharacter(line[j]);
        }
    }
    mazeFile.close();
    return;
}

void CMaze::showMaze()
{
    //prints the maze tile by tile onto the screen
    system("cls");
    for (int i = 0; i < m_columns*m_rows; i++)
    {
        //    if (i % m_columns == 0 && i != 0)
        //    {
        //        cout << '\n';
        //    }
        m_theMaze[i].showTile();
    }

    cout << endl;
    return;
}

CMaze::CMaze()
{
    m_theMaze = NULL;
    return;
}

CMaze::~CMaze()
{
    delete[] m_theMaze;
    m_theMaze = NULL;
    return;
}

//function takes in a coordinate and returns what type of tile is on that spot
int CMaze::getTileType(COORD pos)
{
    int index;
    index = pos.Y * m_columns + pos.X;
    return m_theMaze[index].getTileType();
}

//function takes an integer, and returns the 2D coordinate
COORD CMaze::getCoord(int index)
{
    COORD pos;
    pos.X = index % m_columns;
    pos.Y = index / m_columns;
    return pos;
}

int CMaze::getSize()
{
    return m_columns * m_rows;
}

int CMaze::getRows()
{
    return m_rows;
}