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
	Conn->GetPlayer((ActualPlayer - 1))->isMyMove = true;

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

//	Verify move from player
bool Game::CheckMove() {
	while (true) {
		if (Conn->CheckMove) {
			if (Conn->Move < 9 && board[Conn->Move] == Board::EMPTY) {
				if (Conn->SendGoodMove()) {	//	Send aprove about move to ActualPlayer
					Board::X_OR_O temp = Conn->GetPlayer(ActualPlayer - 1)->Sign;
					//	Write down this move
					board << Board::MOVE(temp, Conn->LastMove);
					return true;
				}
				break;
			}
			else {
				//	Reject move
				if (!Conn->SendGoodMove(false))
					return false;
			}
		}
	}

	// Players can move only 8 times
	Moves++;
	return true;
}

//	Checking board for end
bool Game::CheckBoard() {
	for (int i = 0; i < 8; ++i) {
		unsigned int MatchCounter = 0;
		for (int j = 0; j < 9; ++j) {
			if (Pattern[i][j] && board[j] == Conn->GetPlayer(ActualPlayer - 1)->Sign) {
				if (++MatchCounter == 3) {	//	there should be 3 sings in row
					GameState = END;
					Conn->Winner();
					return true;
				}
			}
		}
	}

	//	When nobody wins and board is full
	//	 it should by a draw
	if (Moves == 8) {
		GameState = END;
		Conn->Draw();
		return true;
	}

	//	Change actual player
	Conn->GetPlayer((ActualPlayer - 1))->isMyMove = false;
	ActualPlayer = (ActualPlayer == 1 ? 2 : 1);
	Conn->GetPlayer((ActualPlayer - 1))->isMyMove = true;
	return false;
}