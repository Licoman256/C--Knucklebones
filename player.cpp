#include "game.h"
void Game::InitPlayers() {

	for (int i = 0; i < numberOfPlayers; i++) {
		players[i] = new Player(numberOfSlotRowsPerPlayer, numberOfSlotColsPerPlayer);
	}
}

void Game::DeletePlayers() {
	for (int i = 0; i < numberOfPlayers; i++) {
		delete players[i];
	}
}

