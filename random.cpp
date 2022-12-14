#include "random.h"
#include "field.h"

namespace random {
	// init
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> randomDice(1, 6);
	std::uniform_int_distribution<int> randomGroup(0, Constants::countGroupsPerPlayer);
	std::uniform_int_distribution<int> randomBool(0, 1);


	// getters
	int Group() {
		return randomGroup(rng);
	}
	int Dice() {
		return randomDice(rng);
	}
	int Bool() {
		return randomBool(rng);
	}
}

float Vert::Len(void) {
	return sqrtf( x*x + y*y );
}

// -------------------------
// --- debug area
#include "game.h"

void Game::FillRandomSlots() {
	for (auto& player : players) {
		player.FillRandomSlots();
	}
}

void Player::FillRandomSlots() {
	for (auto& grp : groups) {
		grp.FillRandomSlots();
	}
	RecalcScore();
}

void Group::FillRandomSlots() {
	for (int i = 0; i < dices.size(); i++) {
		Dice dummy;
		dummy.Throw();
		Add(dummy);
	}
}
