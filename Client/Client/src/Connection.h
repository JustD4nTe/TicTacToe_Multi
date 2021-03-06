#pragma once
#include <WinSock.h>
#include <string>

#include "Packet.h"

class Connection {
private:
	//	Socket to send and receive data
	SOCKET Conn;

	// Address that will bind listening socket to
	SOCKADDR_IN addr;

	// Length of the address (required for accept call)
	int sizeofaddr = sizeof(addr);

	//	Methods to send data
	bool Receive(char* data, const unsigned int totablBytes);
	bool GetUInt32_t(uint32_t& _int32_t);
	bool GetString(std::string& _string);

	//	Methods to receive data
	bool Send(char* data, const unsigned int totalBytes);
	bool SendUInt32_t(uint32_t _int32_t);
	

public:
	Connection(const std::string IP, const unsigned int PORT);
	bool ConnectToServer();
	
	void GetName(std::string& _Name);
	bool GetSign(uint32_t& _isO);

	bool SendPacketType(const Packet::Client _packetType);
	bool GetPacketType(Packet::Server& _packetType );
	bool isGoodMove(const unsigned int Move);
	bool isOponentEndMove();
	bool isEnd();

	bool RequestAboutOponentMove(uint32_t& OponentMove);
};