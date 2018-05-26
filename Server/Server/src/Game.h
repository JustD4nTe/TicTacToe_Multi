#pragma once
#include "Connection.h"

class Game {
private:
	Board board;

public:
	Connection * Conn;
	Game() {
		Conn = new Connection(1111);
	};
	void Connect();
};