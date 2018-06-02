#pragma once
#include "Connection.h"
#include "Board.h"

class Game {
private:
	Board board;
	Connection* Conn;
	std::string PlayerName;
	Board::X_OR_O Sign;
	Board::X_OR_O OponentSign;

	enum GAMESTATE {
		NOT_STARTED,
		IN_PROGRESS,
		END
	};

	GAMESTATE GameState;

	void ShowBoard();
	Packet::Server CheckPosition(const unsigned int PlayerMove);
	Packet::Server SendMove(const unsigned int Move);

public:
	enum  PlayerType {
		ME,
		ENEMY,
		NO_ONE
	};

	PlayerType ActualPlayer;

	Game();
	void Connect();

	bool AskForOponent();
	bool RequestForSign();

	void Start() { GameState = IN_PROGRESS; };

	void YourMove();
	void OponentMove();

	bool isEnd();
};