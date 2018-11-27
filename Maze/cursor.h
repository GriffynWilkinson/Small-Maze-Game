#ifndef __CURSOR_H
#define __CURSOR_H

#include "player.h"
#include <Windows.h>
#include <string>

void displayMessage(std::string, COORD);
void displayMessage(std::string, int, std::string, std::string, int, std::string, int, COORD, CPlayer&);

#endif