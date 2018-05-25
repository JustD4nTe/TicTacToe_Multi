#include <string>

#include "Connection.h"

Connection::Connection(unsigned int PORT, bool BroadcastPublically = false) {
	// Winsock Startup
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 1), &wsaData) != 0) { // If WSAStartup returns anything other than 0, then that means an error has occured in the WinSock Startup.
		MessageBox(NULL, "Winsock startup failed", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}


	if (BroadcastPublically) // If server is open to public
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
	else // If server is only for our router
		addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Broadcast locally

	addr.sin_port = htons(PORT); // Port
	addr.sin_family = AF_INET; // IPv4 Socket

	sListen = socket(AF_INET, SOCK_STREAM, NULL); // Create socket to listen for new connections

	// Bind the address to the socket, if we fail to bind the address..
	if (bind(sListen, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR) {
		std::string ErrorMsg = "Failed to bind the address to our listening socket. Winsock Error: " + std::to_string(WSAGetLastError());
		MessageBoxA(NULL, ErrorMsg.c_str(), "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	// Places sListen socket in a state in which it is listening for an incoming connection. Note:SOMAXCONN = Socket Oustanding Max Connections
	if (listen(sListen, SOMAXCONN) == SOCKET_ERROR) {
		std::string ErrorMsg = "Failed to listen on listening socket. Winsock Error: " + std::to_string(WSAGetLastError());
		MessageBoxA(NULL, ErrorMsg.c_str(), "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}
}