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

// Connect with two players
void Game::Connect() {
	if (Conn->ListenForNewConnection())
		std::cout << "Created player!" << std::endl;
	if (Conn->ListenForNewConnection())
		std::cout << "Created player!" << std::endl;
}