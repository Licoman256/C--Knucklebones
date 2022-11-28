#include "game.h"
#include "dice.h"
Group::Group(int _rows = countRowsPerGroup)
	: dices(_rows)
{}
Group::~Group()
{}

Player::Player()
	: totalScore(0)
{
	groups.reserve(countGroupsPerPlayer);
	Group dummy(countRowsPerGroup);
	for (int i = 0; i < countGroupsPerPlayer; i++) {
		groups.push_back(dummy);
	}
}

Player::~Player()
{}

void Player::RecalcTotal() {
	totalScore = 0;
	for (const auto &grp : groups) {
		totalScore += grp.GetScore();
	}
}

void Player::FillRandomSlots() {
	for (auto& grp : groups) {
		grp.FillRandomSlots();
	}
	RecalcTotal();
}

void Group::FillRandomSlots() {
	for (auto& dice : dices) {
		dice.Throw();
		dice.MoveToField();
	}
}

int Group::GetScore() const { 
	int total = 0; 
	for (auto& dice : dices) {
		total += dice.GetValue();
	}
	return total;
}


