#pragma once
#include <string>
#include <winsock.h>

#include "Board.h"

struct Player {
	SOCKET socket;
	std::string Name;
	Board::X_OR_O Sign;
	bool isMyMove;
	Player() : socket(NULL), Name(std::string()), Sign(Board::EMPTY), isMyMove(false) {};
};