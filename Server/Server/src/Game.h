#pragma once
#include "Connection.h"

class Game {
private:
	Connection* Conn;
	Board board;
	uint8_t ActualPlayer;

public:
	Game() : Conn(new Connection(1111)){};

	void Connect();
	bool Shuffle();
};