#pragma once
#include "Connection.h"

class Game {
private:
	Connection * Conn;
	Board board;
	uint8_t ActualPlayer;
	uint8_t Moves;

	enum GAMESTATE {
		NOT_STARTED,
		IN_PROGRESS,
		END
	};

	GAMESTATE GameState;

	bool Pattern[8][9] = {  { 1,0,0, 1,0,0, 1,0,0 },
							{ 0,1,0, 0,1,0, 0,1,0 },
							{ 0,0,1, 0,0,1, 0,0,1 },

							{ 1,1,1, 0,0,0, 0,0,0 },
							{ 0,0,0, 1,1,1, 0,0,0 },
							{ 0,0,0, 0,0,0, 1,1,1 },

							{ 1,0,0, 0,1,0, 0,0,1 },
							{ 0,0,1, 0,1,0, 1,0,0 }
	};

public:
	Game() : Conn(new Connection(&ActualPlayer, 1111)), GameState(NOT_STARTED), Moves(0) {};

	void Connect();
	bool Shuffle();

	void Start() { GameState = IN_PROGRESS; };

	bool CheckMove();
	bool CheckBoard();

	bool InProgress() { return (GameState == IN_PROGRESS ? true : false); }
};