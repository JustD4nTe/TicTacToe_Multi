#include "Connection.h"

Connection::Connection(std::string IP, unsigned int PORT) {
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

bool Connection::Connect() {
	Conn = socket(AF_INET, SOCK_STREAM, NULL); // Set Connection socket
	if (connect(Conn, (SOCKADDR*)&addr, sizeofaddr) != 0) { // If we are unable to connect...
		MessageBox(NULL, "Failed to Connection", "Error", MB_OK | MB_ICONERROR);
		return false; // Failed to Connect
	}

	return true;
}