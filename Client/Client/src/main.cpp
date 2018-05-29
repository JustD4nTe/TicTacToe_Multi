#include <iostream>

#include "Game.h"

int main() {
	Game* game = new Game();
	
	//	Connect to Server
	game->Connect();

	//	Wait for oponent
	std::cout << "Wait for oponent.";
	while (!game->AskForOponent()) {
		std::cout << '.';
		Sleep(500);
	}
	std::cout << "\nFound!\n";
	for (;;) {}
	//	Get Packet with informationa about 
	//	which player start

	//	Loop until Win/Lose/Draw:
	//		Get sign position (it must be 0 - 8)
	//		Send to Server and wait for response
	//		if position was OK then
	//			Show board and wait for oponent then
	//				Show board
	//		else
	//			go to beginning of loop
	

	//	Display information about endGame
	//	Clear board


	return 0;
}