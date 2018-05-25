#pragma once

class Board {
public:
	enum X_OR_O { X = 'X', O = 'O', EMPTY = ' ' };

	struct MOVE {
		Board::X_OR_O Sign;
		unsigned int Position;
		MOVE(Board::X_OR_O _Sign, unsigned int _Position) : Sign(_Sign), Position(_Position) {};
	};


private:
	X_OR_O Array[9] = {
		EMPTY, EMPTY, EMPTY,
		EMPTY, EMPTY, EMPTY,
		EMPTY, EMPTY, EMPTY
	};

public:
	X_OR_O operator[](const unsigned int Position) { return Array[Position]; }
	friend Board operator <<(Board& board, const MOVE CurrentPlayer);
};