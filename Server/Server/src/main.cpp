#include "Game.h"

int main() {
	Game* game = new Game();

	//	Wait for PlayerOne
	//	Create class for him (Send name to him, save IP etc.)
	
	//	Wait for PlayerTwo
	//	Do same things with Player Two
	 
	//	Cast lots about which player should start ( O <= always starts)
	//	Send information about that

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
	
	//	Send information to players about GameEnd 
	//	(Who won/lost or aboout draw)

	//	 Clear board
	//	 Delete both players

	return 0;
}