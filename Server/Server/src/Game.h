#pragma once
#include "Connection.h"

class Game {
private:
	Connection* Conn;
	Board board;

public:
	Game() : Conn(new Connection(1111)){};

	void Connect();
};