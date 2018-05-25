#pragma once
#include <winsock.h>

class Connection {
private:
	SOCKADDR_IN addr; // Address that will bind listening socket to
	int addrlen = sizeof(addr); // Length of the address (required for accept call)
	SOCKET sListen;

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
	Connection(unsigned int PORT, bool BroadcastPublically = false);
};