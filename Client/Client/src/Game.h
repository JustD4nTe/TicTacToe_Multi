#pragma once
#include "Connection.h"
#include "Board.h"

class Game {
private:
	Board board;
	Connection* Conn;
	std::string PlayerName;

public:
	Game();
	void Connect();
};