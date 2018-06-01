#pragma once
#include "Connection.h"

class Game {
private:
	Connection* Conn;
	Board board;
	uint8_t ActualPlayer;

	enum GAMESTATE {
		NOT_STARTED,
		IN_PROGRESS,
		END
	};

	GAMESTATE GameState;

public:
	Game() : Conn(new Connection(1111)), GameState(NOT_STARTED) {};

	void Connect();
	bool Shuffle();

	void Start() { GameState = IN_PROGRESS; };
};