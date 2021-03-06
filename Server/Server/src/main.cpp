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