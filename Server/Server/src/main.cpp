#include "Game.h"

int main() {
	Game* game = new Game();

	// Connect with 2 players
	game->Connect();

	//	Cast lots about which player should start ( O <= always starts)
	//	Send information about that
	if (!game->Shuffle()) {
		std::cout << "Err!" << __LINE__;
		return 1;
	}

	game->Start();

	do {
		if (game->CheckMove()) {
			if (game->CheckBoard())
				break;				
		}
		//	Loop until Win/Lose/Draw:
		//		Wait for Packet about sign position 
		//		Check if it's OK
		//		if not then:
		//			Response about bad position and back to beggining of loop
		//		else:
		//			Response about good position
		//			Check if game is over, if yes then:
		//				End loop					
		//			Change player
		//			Send information about new position from previous player
	} while (game->InProgress());
	std::cout << "END";
	for (;;) {

	}

	//	Send information to players about GameEnd 
	//	(Who won/lost or aboout draw)

	//	 Clear board
	//	 Delete both players

	return 0;
}