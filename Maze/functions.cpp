#include "maze.h"
#include "player.h"
#include "functions.h"
#include "cursor.h"
#include "minotaur.h"
#include "MazeTile.h"
#include "myColours.h"
#include "windowSize.h"
#include "scorehandler.h"
#include "leaderboard.h"
#include "highscore.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include <mmsystem.h>

using namespace std;

extern int g_ticks;
extern int g_tickResolution;

void gameOver(string);

int updateUI(int health, string gameplay, int numMoves, COORD messagePos, CPlayer& player)
{
    int secs = (g_ticks * g_tickResolution / 1000); // convert to seconds
    setColourBack();
    displayMessage("Health left ", health, gameplay, "Time: ", secs, "\nPress \'escape\' to exit!\t\tNumber of moves: ", numMoves, messagePos, player);

    return (secs);
}


unsigned char getKeyEventProc(KEY_EVENT_RECORD ker)
{
    if (ker.bKeyDown)//Returns the "value" of the keys pressed
    {
        if (ker.wVirtualKeyCode == VK_LEFT)
            return VK_LEFT;
        else if (ker.wVirtualKeyCode == VK_RIGHT)
            return VK_RIGHT;
        else if (ker.wVirtualKeyCode == VK_UP)
            return VK_UP;
        else if (ker.wVirtualKeyCode == VK_DOWN)
            return VK_DOWN;
        else if (ker.wVirtualKeyCode == VK_ESCAPE)
            return VK_ESCAPE;
    }
    return 0;
}

int playGame(int difficulty)
{
    //playing background music
    PlaySound(TEXT("Minotaur (Wrath of Poseidon)_01.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    //declring variables
    COORD messagePos;
    INPUT_RECORD irInBuf[128];  // event buffer
    DWORD cNumRead;  // number of events read
    CMazeTile tile;
    bool windowSize;
    CPlayer player;
    CMinotaur minotaur;
    HANDLE hStdin = player.getInputHandle();
    HANDLE hStdout = minotaur.getOutputHandle();
    CMaze maze;
    string gameplay = " ";
    bool hitTrigger = false;
    COORD tileEnd;
    COORD minPos;
    int secs;
    COORD pos;
    system("cls");

    if (difficulty == 1)
    {
        maze.loadMaze(1); //easy maze
        maze.showMaze();
        //print a message at these coordinates
        messagePos.X = 0;
        messagePos.Y = maze.getRows();
    }
    else if (difficulty == 2)
    {
        maze.loadMaze(2); //medium maze
        maze.showMaze();
        //print a message at these coordinates
        messagePos.X = 0;
        messagePos.Y = maze.getRows();
    }
    else if (difficulty == 3)
    {
        maze.loadMaze(3); //hard maze
        maze.showMaze();
        //print a message at these coordinates
        messagePos.X = 0;
        messagePos.Y = maze.getRows();
    }
    if (hStdin == INVALID_HANDLE_VALUE)
    {
        cout << "Error!: getStdHandle";
        return 0;
    }
    //find where the player should spawn, and put in the player
    for (int i = 0; i < maze.getSize(); i++)
    {
        if (maze.getTileType(maze.getCoord(i)) == TILE_PLAYER)
        {
            player.setPos(maze.getCoord(i));
            player.showPlayer();
            break;
        }
    }
    //find where the minotaur should spawn, and put in the minotaur
    for (int i = 0; i < maze.getSize(); i++)
    {
        if (maze.getTileType(maze.getCoord(i)) == TILE_MINOTAUR)
        {
            minotaur.setPos(maze.getCoord(i));
            minotaur.showMinotaur();
            break;
        }
    }
    for (int i = 0; i < maze.getSize(); i++)
    {
        if (maze.getTileType(maze.getCoord(i)) == TILE_END)
        {
            tileEnd = maze.getCoord(i);
            break;
        }
    }
    pos = player.getPos();
    minPos = minotaur.getPos();
    int numMoves = 0;
    g_ticks = 0;
    int tickTemp = g_ticks;
    while (1)
    {
        int health = player.getHealth();
        //if you run out of health - die
        if (health <= 0)
        {
            string message = "Game Over\tYou ran out of health!";
            gameOver(message);
            break;
        }
        PeekConsoleInput(hStdin, irInBuf, 1, &cNumRead);

        if (cNumRead > 0)
        {
            if (!ReadConsoleInput(hStdin, irInBuf, 1, &cNumRead))
            {
                cout << "Error:ReadConsoleInput" << endl;
                return 0;
            }
            if (irInBuf[0].EventType == KEY_EVENT && irInBuf[0].Event.KeyEvent.bKeyDown == true)
            {
                //getting rid of message1 (see cursor.cpp)
                gameplay = "                              ";

                pos = player.getPos();
                COORD oldPos = pos;

                unsigned char key = getKeyEventProc(irInBuf[0].Event.KeyEvent);

                // Check keys we care about 
                if (key == VK_LEFT)
                {
                    pos.X -= 1;
                }
                else if (key == VK_RIGHT)
                {
                    pos.X += 1;
                }
                else if (key == VK_DOWN)
                {
                    pos.Y += 1;
                }
                else if (key == VK_UP)
                {
                    pos.Y -= 1;
                }
                else if (key == VK_ESCAPE)
                {
                    PlaySound(TEXT("Labyrinth_01.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
                    windowSize = changeWindowSize(80, 25);
                    break;
                }

                //don't move if you hit a wall
                if (maze.getTileType(pos) == TILE_WALL || (maze.getTileType(pos) == TILE_END && hitTrigger == false))
                {
                    pos = oldPos;
                    player.setPos(pos);
                    player.showPlayer();
                }
                else
                {
                    //replace the previous you with a period (get rid of trailing)
                    player.erase(oldPos, maze);

                    //move your position to the updated position
                    player.setPos(pos);
                    player.showPlayer();
                }

                //win if you touch the end
                if (maze.getTileType(pos) == TILE_END)
                {
                    Sleep(100);
                    windowSize = changeWindowSize(80, 25);
                    PlaySound(NULL, 0, 0);
                    mciSendString("play win.wav", 0, 0, 0);
                    setColourBack();
                    system("cls");
                    messagePos.X = 10;
                    messagePos.Y = 10;
                    displayMessage("Congratulations!\tYou Win!", messagePos);
                    Sleep(4000);
                    PlaySound(TEXT("Labyrinth_01.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
                    return (numMoves * secs / 40 - (100 * player.getHealth()));
                }

                //if you hit the trigger, you can now get to the exit
                if (maze.getTileType(pos) == TILE_TRIGGER)
                {
                    mciSendString("play trigger.wav", 0, 0, 0);
                    mciSendString("play door.wav", 0, 0, 0);
                    hitTrigger = true;
                    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleCursorPosition(hStdout, tileEnd);
                    tile.setTile(24, setColour(BLACK, YELLOW));
                    tile.showTile();
                }

                //lose 1 health if you step on a trap
                else if (maze.getTileType(pos) == TILE_TRAP)
                {
                    mciSendString("play trap.wav", 0, 0, 0);
                    gameplay = "You stepped on a trap";
                    health -= 1;
                    player.setHealth(health);
                }

                //lose 2 health if you step on the minotaur
                if (pos.X == minPos.X && pos.Y == minPos.Y)
                {
                    mciSendString("play minotaur.wav", 0, 0, 0);
                    gameplay = "The minotaur hit you";
                    health -= 2;
                    player.setHealth(health);
                }

                //add one to your move number
                numMoves++;
            }
        }

        if (g_ticks % 2 == 0)
        {
            if (tickTemp != g_ticks)
            {
                //moving the minotaur
                minPos = minotaur.moveMinotaur(maze, numMoves, player, gameplay);
            }
            tickTemp = g_ticks;
        }
        secs = updateUI(health, gameplay, numMoves, messagePos, player);
    }

    return 0;
}

void gameOver(string message)
{
    COORD messagePos;
    bool windowSize;

    Sleep(100);
    windowSize = changeWindowSize(80, 25);
    PlaySound(NULL, 0, 0);
    mciSendString("play gameOver.wav", 0, 0, 0);
    setColourBack();
    system("cls");
    messagePos.X = 10;
    messagePos.Y = 10;
    displayMessage(message, messagePos);
    Sleep(3500);
    PlaySound(TEXT("Labyrinth_01.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}