#pragma comment(lib, "ws2_32.lib")

#include "Connection.h"

bool Connection::CheckMove;
uint32_t Connection::Move;
uint32_t Connection::LastMove;

Connection::Connection(uint8_t* _ActualPlayer, const unsigned int PORT, bool BroadcastPublically) {
	CheckMove = false;
	ActualPlayer = _ActualPlayer;
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
	Packet::Client _packetType;
	while (true) {
		//	First get packet to know what to do next
		if (!Conptr->GetPacketType(Client_ID, _packetType))
			break;

		//	Next server do what they ask to do 	
		if (!Conptr->ProccessPacketType(Client_ID,_packetType))
			break;
	}
	std::cout << "Lost connection to client ID: " << Client_ID << std::endl;
	Conptr->PlayerCounter--;
	closesocket(Conptr->Players[Client_ID].socket);
}

//	Function to manage PacketType
//	different packet == different action
bool Connection::ProccessPacketType(const unsigned int Client_ID, Packet::Client _packetType) {
	switch (_packetType) {
	//	Send information about name
	case Packet::Game_Name:
		if (!SendString(Client_ID, Conptr->Players[Client_ID].Name))
			return false;
		break;

	//	Send information about SecondPlayer (it's connected or not)
	case Packet::Conn_WaitForSecondPlayer:
		if (PlayerCounter < 2) {
			if (!SendPacketType(Client_ID, Packet::Conn_OponentNonConected))
				return false;
		}

		else if(!SendPacketType(Client_ID, Packet::Conn_OponentConnected))
			return false;
		break;

	//	Send information about actual player
	case Packet::Moving_Who:
		if (Client_ID == (*ActualPlayer - 1) && Players[Client_ID].isMyMove) {
			if(!SendPacketType(Client_ID, Packet::Moving_You))
				return false;
		}

		else {
			if (!SendPacketType(Client_ID, Packet::Moving_Oponent))
				return false;
		}
		break;

	//	Get move from player
	case Packet::Move_Sign:
		if (Client_ID == (*ActualPlayer - 1)) {
			if (!GetUInt32_t(Client_ID, Move))
				return false;
			CheckMove = true;
			LastMove = Move;
		}
		else {
			//	ERROR
		}
		break;

	//	Send oponent's move
	case Packet::Move_Oponent:
		if (!SendUInt32_t(Client_ID,LastMove))
			return false;
		break;

	//	Send information about sign
	case Packet::Game_Sign:
		if (Players[Client_ID].Sign == Board::EMPTY) {
			if (!SendUInt32_t(Client_ID, 2))
				return false;
		}
		else {
			uint32_t isO = (Players[Client_ID].Sign == Board::O ? 1 : 0);
			if (!SendUInt32_t(Client_ID, isO))
				return false;
		}
		break;
		
	//	Information about game (is ended (Win or draw) or not)
	case Packet::GameState:
		if (!isEnd) {
			if (!SendPacketType(Client_ID, Packet::GameState_InProgress))
				return false;
		}
		else {
			if (*ActualPlayer != 0) {
				if ((uint32_t)(*ActualPlayer - 1) == Client_ID) {
					if (!SendPacketType(Client_ID, Packet::GameState_WIN))
						return false;
				}
			}
			else {
				if (!SendPacketType(Client_ID, Packet::GameState_DRAW))
					return false;
			}
		}
		break;
	}
	return true;
}

// Send aprove or reject player's move
bool Connection::SendGoodMove(bool isGoodMove) {
	CheckMove = false;
	Move = 9;
	if (isGoodMove) {
		if (!SendPacketType((uint32_t)(*ActualPlayer - 1), Packet::Move_Good))
			return false;
		return true;
	}
	else {
		if (!SendPacketType((uint32_t)(*ActualPlayer - 1), Packet::Move_Bad))
			return false;
		return true;
	}
	return true;
}