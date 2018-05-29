#pragma comment(lib, "ws2_32.lib")

#include "Connection.h"

Connection::Connection(const unsigned int PORT, bool BroadcastPublically) {
	// Winsock Startup
	WSADATA wsaData;
	// If WSAStartup returns anything other than 0, then that means an error has occured in the WinSock Startup.
	if (WSAStartup(MAKEWORD(2, 1), &wsaData) != 0) { 
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

	// Places sListen socket in a state in which it is listening for an incoming connection. Note: SOMAXCONN = Socket Oustanding Max Connections
	if (listen(sListen, SOMAXCONN) == SOCKET_ERROR) {
		std::string ErrorMsg = "Failed to listen on listening socket. Winsock Error: " + std::to_string(WSAGetLastError());
		MessageBoxA(NULL, ErrorMsg.c_str(), "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	Conptr = this;	
}


bool Connection::ListenForNewConnection() {
	// Socket to holds the client's connection
	SOCKET newConnection;
	newConnection = accept(sListen, (SOCKADDR*)&addr, &addrlen);

	// If failed
	if (newConnection == 0) {
		std::cout << "Failed to accept the client's connection." << std::endl;
		return false;
	}

	std::cout << "Connected" << std::endl;

	Players[PlayerCounter].socket = newConnection;
	Players[PlayerCounter].Name = (PlayerCounter == 0 ? "PlayerOne" : "PlayerTwo");

	//	Create thread to manage client's packets
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandlerThread, (LPVOID)PlayerCounter, NULL, NULL);

	PlayerCounter++;
	return true;
}

//	Function to manage client's packets
void Connection::ClientHandlerThread(const unsigned int Client_ID) {
	PacketType _packetType;
	while (true) {
		//	First get packet to know what to do next
		if (!Conptr->GetPacketType(Client_ID, _packetType))
			break;

		//	Next server do what they ask to do 	
		if (!Conptr->ProccessPacketType(Client_ID,_packetType))
			break;
	}
	std::cout << "Lost connection to client ID: " << Client_ID << std::endl;
	closesocket(Conptr->Players[Client_ID].socket);
}

//	Function to manage PacketType
//	different packet == different action
bool Connection::ProccessPacketType(const unsigned int Client_ID, PacketType _packetType) {
	switch (_packetType) {
	case PacketType::Name:
		if (!SendString(Client_ID, Conptr->Players[Client_ID].Name))
			return false;
		break;
	case PacketType::Conn_OponentDisconnected:
		break;
	case PacketType::Conn_OponentConnected:
		break;
	case PacketType::Conn_WaitForSecondPlayer:
		break;
	case PacketType::Move_Oponent:
		break;
	case PacketType::Move_Bad:
		break;
	case PacketType::Move_Good:
		break;
	case PacketType::Game_Sign:
		break;
	case PacketType::GameState_WIN:
		break;
	case PacketType::GameState_LOSE:
		break;
	case PacketType::GameState_DRAW:
		break;
	default:
		break;
	}
	return true;
}