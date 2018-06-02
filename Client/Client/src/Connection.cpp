#pragma comment(lib, "ws2_32.lib")

#include "Connection.h"

#define NOT_SIGN 2

Connection::Connection(const std::string IP, const unsigned int PORT) {
	// Winsock Startup
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 1), &wsaData) != 0) {
		MessageBox(NULL, "Winsock startup failed", "Error", MB_OK | MB_ICONERROR);
		exit(0);
	}

	addr.sin_addr.s_addr = inet_addr(IP.c_str()); // Address == localhost
	addr.sin_port = htons(PORT); // Port = 1111
	addr.sin_family = AF_INET; // IPv4 Socket
}

bool Connection::ConnectToServer() {
	Conn = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Conn, (SOCKADDR*)&addr, sizeofaddr) != 0) {
		MessageBox(NULL, "Failed to Connection", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	return true;
}

void Connection::GetName(std::string& _Name) {
	SendPacketType(Packet::Name);
	GetString(_Name);
}

bool Connection::GetSign(uint32_t& _isO) {
	SendPacketType(Packet::Game_Sign);

	uint32_t isO;
	GetUInt32_t(isO);

	if (isO == NOT_SIGN)
		return false;

	_isO = isO;
	return true;
}

bool Connection::isGoodMove(const unsigned int Move) {
	if (!SendPacketType(Packet::Move_Sign))
		return false;
	if (!SendUInt32_t(Move))
		return false;

	Packet::Server MoveType;

	if (!GetPacketType(MoveType))
		return false;
	//	Serer should response this two answers
	if (MoveType == Packet::Move_Bad || MoveType == Packet::Move_Good)
		return true;

	return false;
}
bool Connection::isEnd() {
	if (!SendPacketType(Packet::GameState))
		return false;

	Packet::Server GameState;

	if (!GetPacketType(GameState))
		return false;
	if (GameState == Packet::GameState_End)
		return true;

	return false;
}