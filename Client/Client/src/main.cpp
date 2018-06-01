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


	//	Get Packet with informationa about 
	//	which player start
	std::cout << "Wait for sign";
	while (!game->RequestForSign()) {
		std::cout << ".";
		Sleep(100);
	}
	std::cout << "\nGot sign!\n";

	do {
		if (game->ActualPlayer == game->ME)
			game->YourMove();		
		else
			game->OponentMove();

	} while (!game->isEnd());

	//	Display information about endGame
	//	Clear board

	return 0;
}