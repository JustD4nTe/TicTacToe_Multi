#include "Connection.h"

//	Get data from Server
//	*data => where store data, 
//	totalBytes => how much bytes to recv
bool Connection::Receive(char* data, const unsigned int totalBytes) {
	//	When receiving is failed => return false
	return (recv(Conn, data, totalBytes, NULL) == SOCKET_ERROR ? false : true);
}

bool Connection::GetUInt32_t(uint32_t& _int32_t) {
	if (!Receive((char*)&_int32_t, sizeof(uint32_t))) 	//	Try to recv int
		return false;	//	Return false: int not successfully received

	_int32_t = ntohl(_int32_t);	//	Convert long from Network Byte Order to Host Byte Order
	return true;	// Return true if we were successful in retrieving the int
}

bool Connection::GetString(std::string& _string) {
	unsigned int bufferLength; // Holds length of string
							   //	Get length of string and store it in bufferLength
	if (!GetUInt32_t(bufferLength))
		return false;

	//	Allocate buffer
	char* buffer = new char[bufferLength + 1];
	buffer[bufferLength] = '\0';	//	Add null at end

									// Get string
	if (!Receive(buffer, bufferLength)) {
		// Dellocate buffer memory (cleanup to prevent memory leak)
		delete[] buffer;
		return false;
	}

	_string = buffer;

	// Dellocate buffer memory (cleanup to prevent memory leak)
	delete[] buffer;

	return true;
}

//	Semd data from Server
//	*data => where store data, 
//	totalBytes => how much bytes to send
bool Connection::Send(char* data, const unsigned int totalBytes) {
	//	When receiving is failed => return false
	return (send(Conn, data, totalBytes, NULL) == SOCKET_ERROR ? false : true);
}

bool Connection::SendUInt32_t(uint32_t _uint32_t) {
	_uint32_t = htonl(_uint32_t);
	return Send((char*)&_uint32_t, sizeof(uint32_t));
}


bool Connection::SendPacketType(PacketType _packetType) {
	return SendUInt32_t((uint32_t)_packetType);
}