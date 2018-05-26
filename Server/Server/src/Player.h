#pragma once
#include <string>
#include <winsock.h>

#include "Board.h"

struct Player {
	SOCKET socket;
	std::string Name;
	Board::X_OR_O Sign;
};