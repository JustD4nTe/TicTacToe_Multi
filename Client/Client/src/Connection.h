#pragma once
#include <WinSock.h>
#include <string>

class Connection {
private:
	//	Socket to send and receive data
	SOCKET Conn;

	// Address that will bind listening socket to
	SOCKADDR_IN addr;

	// Length of the address (required for accept call)
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

	bool Receive(char* data, unsigned int totablBytes);
	bool GetUInt32_t(uint32_t& _int32_t);

public:
	Connection(std::string IP, unsigned int PORT);
	bool ConnectToServer();
	
	bool  GetString(std::string& _string);
};