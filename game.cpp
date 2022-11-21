#include "game.h"


void Game::Render() {
	field.Render();
	//popup.Render();
}

void Game::InitPlayers() {

	for (int i = 0; i < countPlayers; i++) {
		players[i] = new Player(countSlotRowsPerPlayer, countSlotColsPerPlayer);
	}
}

void Game::DeletePlayers() {
	for (int i = 0; i < countPlayers; i++) {
		if (players[i]) {
			delete players[i];
			players[i] = nullptr;
		}
	}
}


