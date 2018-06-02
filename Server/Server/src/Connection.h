#pragma once
#include <iostream>

#include "Player.h"
#include "Packet.h"

#define PLAYERS_COUNT 2

class Connection{
private:
	// Address that will bind listening socket to
	SOCKADDR_IN addr; 

	// Length of the address (required for accept call)
	int addrlen = sizeof(addr);

	//	Socket to listening
	SOCKET sListen;	

	Player Players[PLAYERS_COUNT];
	unsigned int PlayerCounter = 0;

	const uint8_t* ActualPlayer;
	bool isEnd = false;
	

public:
	Connection(uint8_t* _ActualPlayer, const unsigned int PORT, bool BroadcastPublically = false);

	static bool CheckMove;
	static uint32_t Move;
	static uint32_t LastMove;

	bool ListenForNewConnection();

	// Get pointer to Player only when they exist
	//	Index start from 0 :<
	Player* GetPlayer(const unsigned int Player_ID) { 
		return (Player_ID >= PlayerCounter ? nullptr : &Players[Player_ID]);
	};

	bool SendGoodMove(bool isGoodMove = true);

	void Winner() {isEnd = true;};
	void Draw() { isEnd = true; ActualPlayer = 0; };

private:
	//	Methods to send data
	//bool SendPacket(const unsigned int Client_ID, Packet& p);
	bool SendString(const unsigned int Client_ID, const std::string& Message);	
	bool SendPacketType(const unsigned int Client_ID, const Packet::Server _packetType);
	bool SendUInt32_t(const unsigned int Client_ID, uint32_t _UInt32_t);
	bool Send(const unsigned int Client_ID, char* data, const uint32_t _UInt32_t);

	//	Methods to get data
	bool GetPacketType(const unsigned int Client_ID, Packet::Client& _packetType);
	bool GetUInt32_t(const unsigned int Client_ID, uint32_t& _UInt32_t);
	bool Receive(const unsigned int Client_ID, char* data, const uint32_t totablBytes);


	static void ClientHandlerThread(const unsigned int Client_ID);

	bool ProccessPacketType(const unsigned int Client_ID, Packet::Client _packetType);
};

static Connection* Conptr;