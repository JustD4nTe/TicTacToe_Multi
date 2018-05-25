#pragma once
#include <WinSock.h>
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

	bool Recvall(char* data, unsigned int totablBytes);
	bool GetUInt32_t(uint32_t& _int32_t);

public:
	Connection(std::string IP, unsigned int PORT);
	bool ConnectToServer();
	
	bool  GetString(std::string& _string);
};