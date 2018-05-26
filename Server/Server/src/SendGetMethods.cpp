#include "Connection.h"

bool Connection::SendPacket(const unsigned int Client_ID, Packet& p) {
	switch (p.GetPacketType()) {
	case _PacketType::Name:
		if (!SendString(Client_ID, p.GetString()))
			return false;
		break;
	case _PacketType::Conn_OponentDisconnected:
		break;
	case _PacketType::Conn_OponentConnected:
		break;
	case _PacketType::Conn_WaitForSecondPlayer:
		break;
	case _PacketType::Move_Oponent:
		break;
	case _PacketType::Move_Bad:
		break;
	case _PacketType::Move_Good:
		break;
	case _PacketType::Game_Sign:
		break;
	case _PacketType::GameState_WIN:
		break;
	case _PacketType::GameState_LOSE:
		break;
	case _PacketType::GameState_DRAW:
		break;
	default:
		break;
	}
	return true;
}

//	Function to send data to Client
//	Client_ID
//	*data => where store data, 
//	totalBytes => how much bytes to recv
bool Connection::Send(const unsigned int Client_ID,char* data, const uint32_t totalBytes) {
	//	When receiving is failed => return false
	return (send(Players[Client_ID].socket, data, totalBytes, NULL) == SOCKET_ERROR ? false : true);
}

bool Connection::SendUInt32_t(const unsigned int Client_ID, uint32_t _UInt32_t) {
	_UInt32_t = htonl(_UInt32_t);
	if (!Send(Client_ID, (char*)&_UInt32_t, sizeof(_UInt32_t)))
		return false;
	return true;
}

bool Connection::SendString(const unsigned int Client_ID, const std::string& Message) {
	if (!SendUInt32_t(Client_ID, Message.length()))
		return false;
	if (!Send(Client_ID, (char*)Message.c_str(), Message.length()))
		return false;
	return true;
}