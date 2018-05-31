#pragma once
#include "Connection.h"
#include "Board.h"

class Game {
private:
	Board board;
	Connection* Conn;
	std::string PlayerName;
	Board::X_OR_O Sign;

public:
	Game();
	void Connect();

	bool AskForOponent();
	bool RequestForSign();
};