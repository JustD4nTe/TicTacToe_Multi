#include <iostream>

#include "Game.h"

std::ostream& operator <<(std::ostream& stream, const Board::X_OR_O &Field) {
	stream << (char)Field;
	return stream;
}

Board operator <<(Board& board, const Board::MOVE CurrentPlayer) {
	board.Array[CurrentPlayer.Position] = CurrentPlayer.Sign;
	return board;
}