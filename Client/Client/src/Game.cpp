#include <iostream>
#include <Windows.h>

#include "Game.h"

std::ostream& operator <<(std::ostream& stream, const Board::X_OR_O &Field) {
	stream << (char)Field;
	return stream;
}

Board operator <<(Board& board, const Board::MOVE CurrentPlayer) {
	board.Array[CurrentPlayer.Position] = CurrentPlayer.Sign;
	return board;
}

Game::Game() {
	Conn = new Connection("127.0.0.1", 111);
}

void Game::Connect() {
	while (!Conn->ConnectToServer()){
		std::cout << "Failed to connect to server..." << std::endl;
		Sleep(1000);
	}
	
	// Wait 0.1s for response (name)
	Sleep(100);

	Conn->GetString(PlayerName);
}