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
	
	// Types of packets which we can send/receive
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

	//	Methods to send data
	bool Receive(char* data, const unsigned int totablBytes);
	bool GetUInt32_t(uint32_t& _int32_t);
	bool GetString(std::string& _string);

	//	Methods to receive data
	bool Send(char* data, const unsigned int totalBytes);
	bool SendUInt32_t(uint32_t _int32_t);
	bool SendPacketType(PacketType _packetType);

public:
	Connection(const std::string IP, const unsigned int PORT);
	bool ConnectToServer();
	
	//	TODO: change that :<
	void GetName(std::string& _Name);
};