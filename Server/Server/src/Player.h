#pragma once
#include <string>
#include <winsock.h>

#include "Board.h"

class Player {
public:
	SOCKET socket;
	std::string Name;
	Board::X_OR_O Sign;
};