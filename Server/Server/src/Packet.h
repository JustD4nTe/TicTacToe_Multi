#pragma once

enum PacketType {
	Name,
	Conn_OponentDisconnected,
	Conn_OponentConnected,
	Conn_WaitForSecondPlayer,
	Move_Oponent,
	Move_Bad,
	Move_Good,
	Game_Sign,
	GameState_WIN,
	GameState_LOSE,
	GameState_DRAW
};

class Packet {
private:
	std::string m_String;
	PacketType m_PacketType;

public:
	Packet(PacketType _packetType, std::string _string) : m_String(_string), m_PacketType(_packetType) {};

	// Get private members
	PacketType GetPacketType() { return m_PacketType; };
	std::string GetString() { return m_String; };
};