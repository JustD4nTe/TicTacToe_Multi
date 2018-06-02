#pragma once

namespace Packet {
	// Types of packets which
	//	can clients send to server
	enum Client {
		Name,
		Conn_OponentConnected,
		Conn_WaitForSecondPlayer,
		Moving_Who,
		Move_Sign,
		Game_Sign,
		GameState
	};

	// Types of packets which
	//	can server send to clients
	enum Server {
		Conn_OponentConnected,
		Conn_WaitForSecondPlayer,
		Moving_Oponent,
		Moving_Me,
		Move_Bad,
		Move_Good,
		GameState_InProgress,
		GameState_End,
		GameState_WIN,
		GameState_LOSE,
		GameState_DRAW
	};
}