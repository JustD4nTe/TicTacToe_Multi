#pragma once
#include <iostream>

#include "Player.h"
#include "Packet.h"

class Connection : private _PacketType{
private:
	SOCKADDR_IN addr; // Address that will bind listening socket to
	int addrlen = sizeof(addr); // Length of the address (required for accept call)
	SOCKET sListen;
	Player Players[2];

	unsigned int PlayerCounter = 0;
	

public:
	Connection(unsigned int PORT, bool BroadcastPublically = false);
	bool ListenForNewConnection();

private:
	bool SendString(const unsigned int Client_ID, const std::string& Message);
	bool SendPacket(const unsigned int Client_ID, Packet& p);
	bool SendUInt32_t(const unsigned int Client_ID, uint32_t _UInt32_t);

	bool Send(const unsigned int Client_ID, char* data, uint32_t _UInt32_t);
};