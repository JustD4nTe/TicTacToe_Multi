#pragma comment(lib, "ws2_32.lib")

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

bool Connection::ConnectToServer() {
	Conn = socket(AF_INET, SOCK_STREAM, NULL); // Set Connection socket
	if (connect(Conn, (SOCKADDR*)&addr, sizeofaddr) != 0) { // If we are unable to connect...
		MessageBox(NULL, "Failed to Connection", "Error", MB_OK | MB_ICONERROR);
		return false; // Failed to Connect
	}

	return true;
}

//	*data => where store data, totalBytes => how much bytes to recv
bool Connection::Recvall(char* data, unsigned int totalBytes) {
	//	When receiving is failed => return false
	return (recv(Conn, data, totalBytes, NULL) == SOCKET_ERROR ? false : true);
}

bool Connection::GetUInt32_t(uint32_t& _int32_t){
	if (!Recvall((char*)&_int32_t, sizeof(uint32_t))) 	//	Try to recv int
		return false;	//	Return false: int not successfully received

	_int32_t = ntohl(_int32_t);	//	Convert long from Network Byte Order to Host Byte Order
	return true;	// Return true if we were successful in retrieving the int
}

bool Connection::GetString(std::string& _string) {
	unsigned int bufferLength; // Holds length of string
	//	Get length of string and store it in bufferLength
	if (!GetUInt32_t(bufferLength))
		return false;

	//	 Allocate buffer
	char* buffer = new char[bufferLength + 1];	
	buffer[bufferLength] = '\0';	//	Add null at end

	// Get string
	if (!Recvall(buffer, bufferLength)) {
		// Dellocate buffer memory (cleanup to prevent memory leak)
		delete[] buffer;
		return false;
	}

	_string = buffer;

	// Dellocate buffer memory (cleanup to prevent memory leak)
	delete[] buffer;
	
	return true;
}