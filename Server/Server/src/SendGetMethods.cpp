#include "Connection.h"

//bool Connection::SendPacket(const unsigned int Client_ID, Packet& p) {
//	switch (p.GetPacketType()) {
//	case PacketType::Name:
//		if (!SendString(Client_ID, p.GetString()))
//			return false;
//		break;
//	case PacketType::Conn_OponentDisconnected:
//		break;
//	case PacketType::Conn_OponentConnected:
//		break;
//	case PacketType::Conn_WaitForSecondPlayer:
//		break;
//	case PacketType::Move_Oponent:
//		break;
//	case PacketType::Move_Bad:
//		break;
//	case PacketType::Move_Good:
//		break;
//	case PacketType::Game_Sign:
//		break;
//	case PacketType::GameState_WIN:
//		break;
//	case PacketType::GameState_LOSE:
//		break;
//	case PacketType::GameState_DRAW:
//		break;
//	default:
//		break;
//	}
//	return true;
//}

//	Function to send data to Client
//	Client_ID
//	*data => where store data, 
//	totalBytes => how much bytes to send
bool Connection::Send(const unsigned int Client_ID,char* data, const uint32_t totalBytes) {
	//	When receiving is failed => return false
	return (send(Players[Client_ID].socket, data, totalBytes, NULL) == SOCKET_ERROR ? false : true);
}

bool Connection::SendUInt32_t(const unsigned int Client_ID, uint32_t _UInt32_t) {
	_UInt32_t = htonl(_UInt32_t);
	return Send(Client_ID, (char*)&_UInt32_t, sizeof(_UInt32_t));
}

bool Connection::SendString(const unsigned int Client_ID, const std::string& Message) {
	if (!SendUInt32_t(Client_ID, Message.length()))
		return false;
	if (!Send(Client_ID, (char*)Message.c_str(), Message.length()))
		return false;
	return true;
}

//	Function to get data to Client
//	Client_ID
//	*data => where store data, 
//	totalBytes => how much bytes to recv
bool Connection::Receive(const unsigned int Client_ID, char* data, const uint32_t totalBytes) {
	//	When receiving is failed => return false
	return (recv(Players[Client_ID].socket, data, totalBytes, NULL) == SOCKET_ERROR ? false : true);
}

bool Connection::GetUInt32_t(const unsigned int Client_ID, uint32_t& _UInt32_t) {
	return (Receive(Client_ID, (char*)&_UInt32_t, sizeof(uint32_t)));
}

bool Connection::GetPacketType(const unsigned int Client_ID, PacketType& _packetType) {
	uint32_t packetDump;
	if (!GetUInt32_t(Client_ID, packetDump))
		return false;
	_packetType = (PacketType)packetDump;
	return true;
}