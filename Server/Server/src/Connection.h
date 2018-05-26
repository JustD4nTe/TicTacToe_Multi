#pragma once
#include <iostream>

#include "Player.h"
#include "Packet.h"

#define PLAYERS_COUNT 2

class Connection : private _PacketType{
private:
	// Address that will bind listening socket to
	SOCKADDR_IN addr; 

	// Length of the address (required for accept call)
	int addrlen = sizeof(addr);

	//	Socket to listening
	SOCKET sListen;	

	Player Players[PLAYERS_COUNT];
	unsigned int PlayerCounter = 0;
	

public:
	Connection(const unsigned int PORT, bool BroadcastPublically = false);
	bool ListenForNewConnection();

private:
	bool SendString(const unsigned int Client_ID, const std::string& Message);
	bool SendPacket(const unsigned int Client_ID, Packet& p);
	bool SendUInt32_t(const unsigned int Client_ID, uint32_t _UInt32_t);

	bool Send(const unsigned int Client_ID, char* data, const uint32_t _UInt32_t);
};