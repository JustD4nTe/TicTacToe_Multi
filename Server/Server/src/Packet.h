#pragma once

namespace Packet{
	// Types of packets which
	//	can clients send to server
	enum Client {
		Conn_WaitForSecondPlayer,
		Game_Name,
		Game_Sign,
		Moving_Who,
		Move_Sign,
		Move_Oponent,
		GameState
	};

	// Types of packets which
	//	can server send to clients
	enum Server {
		Conn_OponentConnected,
		Conn_OponentNonConected,
		Moving_Oponent,
		Moving_You,
		Move_Bad,
		Move_Good,
		GameState_InProgress,
		GameState_End,
		GameState_WIN,
		GameState_LOSE,
		GameState_DRAW
	};
}