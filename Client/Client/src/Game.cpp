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
	ActualPlayer = NO_ONE;
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

//	Ask server which sign player have
//	then chose who starts game
//	'O' always start
bool Game::RequestForSign() {
	//	When this client have O
	//	isO = true else isO = false;
	uint32_t isO;
	if (!Conn->GetSign(isO))
		return false;

	if (isO) {
		std::cout << "You starts game\n";
		ActualPlayer = ME;
		Sign = Board::O;
		OponentSign = Board::X;
	}
	else {
		std::cout << "Game starts enemy\n";
		ActualPlayer = ENEMY;
		Sign = Board::X;
		OponentSign = Board::O;
	}

	std::cout << "Your sign => " << Sign << std::endl;

	return true;
}

//	Writing board on console
//	yup this code is bad
void Game::ShowBoard() {
	system("cls");

	//	Pattern
	//	information for player which number
	//	is which field
	std::cout << "\t" << char(218) << char(196) << char(196) << char(196) << char(194) << char(196) << char(196) << char(196) << char(194) << char(196) << char(196) << char(196) << char(191) << std::endl;
	std::cout << "\t" << char(179) << " 0 " << char(179) << " 1 " << char(179) << " 2 " << char(179) << std::endl;
	std::cout << "\t" << char(195) << char(196) << char(196) << char(196) << char(197) << char(196) << char(196) << char(196) << char(197) << char(196) << char(196) << char(196) << char(180) << std::endl;
	std::cout << "\t" << char(179) << " 3 " << char(179) << " 4 " << char(179) << " 5 " << char(179) << std::endl;
	std::cout << "\t" << char(195) << char(196) << char(196) << char(196) << char(197) << char(196) << char(196) << char(196) << char(197) << char(196) << char(196) << char(196) << char(180) << std::endl;
	std::cout << "\t" << char(179) << " 6 " << char(179) << " 7 " << char(179) << " 8 " << char(179) << std::endl;
	std::cout << "\t" << char(192) << char(196) << char(196) << char(196) << char(193) << char(196) << char(196) << char(196) << char(193) << char(196) << char(196) << char(196) << char(217) << std::endl;
	std::cout << std::endl;

	//	Board
	//	actual board for game
	std::cout << "\t" << char(218) << char(196) << char(196) << char(196) << char(194) << char(196) << char(196) << char(196) << char(194) << char(196) << char(196) << char(196) << char(191) << std::endl;
	std::cout << "\t" << char(179) << " " << board[0] << " " << char(179) << " " << board[1] << " " << char(179) << " " << board[2] << " " << char(179) << std::endl;
	std::cout << "\t" << char(195) << char(196) << char(196) << char(196) << char(197) << char(196) << char(196) << char(196) << char(197) << char(196) << char(196) << char(196) << char(180) << std::endl;
	std::cout << "\t" << char(179) << " " << board[3] << " " << char(179) << " " << board[4] << " " << char(179) << " " << board[5] << " " << char(179) << std::endl;
	std::cout << "\t" << char(195) << char(196) << char(196) << char(196) << char(197) << char(196) << char(196) << char(196) << char(197) << char(196) << char(196) << char(196) << char(180) << std::endl;
	std::cout << "\t" << char(179) << " " << board[6] << " " << char(179) << " " << board[7] << " " << char(179) << " " << board[8] << " " << char(179) << std::endl;
	std::cout << "\t" << char(192) << char(196) << char(196) << char(196) << char(193) << char(196) << char(196) << char(196) << char(193) << char(196) << char(196) << char(196) << char(217) << std::endl;
	std::cout << std::endl;
}

void Game::YourMove() {
	std::string PlayerMove;
	do {
		ShowBoard();

		std::cout << "Your move as '" << Sign << "'" << std::endl;
		std::cout << "Move(0-8): ";
				
		std::cin >> PlayerMove;
		
		//	Player should write only one character
		if (PlayerMove.size() > 1)
			continue;

		//	Primitive prepare to nonpublic conversion
		PlayerMove[0] -= 48;
	} while (CheckPosition(PlayerMove[0]) == Packet::Move_Bad);

	//	Save move to board
	board << Board::MOVE(Sign, PlayerMove[0]);
}


Packet::Server Game::CheckPosition(const unsigned int PlayerMove) {
	//	There's eigth fields
	if (PlayerMove > 8) {
		std::cout << "Illegal move";
		return Packet::Move_Bad;
	}

	//	When everything goes well
	//	send move to Server
	return SendMove(PlayerMove);
}

Packet::Server Game::SendMove(const unsigned int Move) {
	return (Conn->isGoodMove(Move) ? Packet::Move_Good : Packet::Move_Bad);
}

bool Game::isEnd() {
	return Conn->isEnd();
}