#include "Connection.h"

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

bool Connection::SendPacketType(const unsigned int Client_ID, const Packet::Server _packetType) {
	return SendUInt32_t(Client_ID, (uint32_t)_packetType);
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
	if (!Receive(Client_ID, (char*)&_UInt32_t, sizeof(uint32_t)))
		return false;
	_UInt32_t = ntohl(_UInt32_t);
	return true;
}

bool Connection::GetPacketType(const unsigned int Client_ID, Packet::Client& _packetType) {
	uint32_t packetDump;
	if (!GetUInt32_t(Client_ID, packetDump))
		return false;
	_packetType = (Packet::Client)packetDump;
	return true;
}
