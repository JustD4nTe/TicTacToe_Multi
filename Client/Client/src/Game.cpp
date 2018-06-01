#include <iostream>
#include <Windows.h>
#include <string>

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
	Conn = new Connection("127.0.0.1", 1111);
}


void Game::Connect() {
	//	Try to connect with Server every 1s
	while (!Conn->ConnectToServer()) {
		std::cout << "Failed to connect to server..." << std::endl;
		Sleep(1000);
	}

	//	When we connected with Server
	//	We're getting name Like "PlayerOne"
	Conn->GetName(PlayerName);
	std::cout << "Hello " << PlayerName << "!\n";
}

bool Game::AskForOponent() {
	Conn->SendPacketType(Packet::Client::Conn_WaitForSecondPlayer);
	Packet::Server PacketDump;
	Conn->GetPacketType(PacketDump);
	return (PacketDump == Packet::Conn_OponentConnected ? true : false);
}

bool Game::RequestForSign() {
	uint32_t isO;
	if (!Conn->GetSign(isO))
		return false;
	Sign = (isO ? Board::O : Board::X);

	std::cout << "Your sign => " << Sign << std::endl;

	//	Choose which player starts
	//	'O' starts game of course
	ActualPlayer = (Sign == Board::O ? ME : ENEMY);
	if (ActualPlayer)
		std::cout << "Game starts enemy\n";
	else
		std::cout << "You starts game\n";
	return true;
}
}