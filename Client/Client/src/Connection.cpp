#pragma comment(lib, "ws2_32.lib")

#include "Connection.h"

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