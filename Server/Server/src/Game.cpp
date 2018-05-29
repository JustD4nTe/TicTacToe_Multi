#include <iostream>
#include <ctime>
#include <cstdlib>

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

bool Game::Shuffle() {
	srand(static_cast<unsigned int>(time(NULL)));
	bool isX = rand() % 2;

	ActualPlayer = (isX ? 2 : 1);

	if (Conn->GetPlayer(0) == nullptr)
		return false;
	else
		Conn->GetPlayer(0)->Sign = (isX ? Board::X : Board::O);

	if (Conn->GetPlayer(1) == nullptr)
		return false;
	else
		Conn->GetPlayer(1)->Sign = (!isX ? Board::X : Board::O);

	return true;
}