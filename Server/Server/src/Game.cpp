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

//	Draw a sign for players
bool Game::Shuffle() {
	srand(static_cast<unsigned int>(time(NULL)));

	//	Select sign for PlayerOne
	//	he can get 'X' (as number 1)
	//	or 'O' (as number 0)s
	bool isX = rand() % 2;

	//	Only sign 'O' start game
	//	e.g. PlayerOne has a X
	//	then PlayerTwo start game
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

bool Game::CheckMove() {
	while (true) {
		if (Conn->CheckMove) {
			if (board[Conn->Move] != Board::EMPTY && Conn->Move != 9) {
				if (!Conn->SendGoodMove()) {
					board << Board::MOVE(Conn->GetPlayer(ActualPlayer - 1)->Sign, Conn->Move);
					return false;
				}
				break;
			}
			else {
				if (!Conn->SendGoodMove(false))
					return false;
			}
		}
	}
	Moves++;
	return true;
}

bool Game::CheckBoard() {
	for (int i = 0; i < 8; ++i) {
		unsigned int MatchCounter = 0;
		for (int j = 0; j < 9; ++j) {
			if (Pattern[i][j] && board[j] == Conn->GetPlayer(ActualPlayer - 1)->Sign) {
				if (++MatchCounter == 3) {
					GameState = END;
					Conn->Winner();
					return true;
				}
			}
		}
	}

	if (Moves == 8) {
		GameState = END;
		Conn->Draw();
		return true;
	}

	return false;
}