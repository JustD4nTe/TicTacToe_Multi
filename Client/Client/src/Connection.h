#pragma once
#include <winsock.h>
#include <string>

class Connection {
private:
	SOCKET Conn;
	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);

	enum PacketType {
		Name,
		Conn_OponentDisconnected,
		Conn_OponentConnected,
		Conn_WaitForSecondPlayer,
		Move_Oponent,
		Move_Bad,
		Move_Good,
		Game_Sign,
		GameState_WIN,
		GameState_LOSE,
		GameState_DRAW
	};

public:
	Connection(std::string IP, unsigned int PORT);
	bool Connect();
};