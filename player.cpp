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


void Player::FillRandomSlots() {
	for (auto& grp : groups) {
		grp.FillRandomSlots();
	}
	RecalcTotal();
}

void Group::FillRandomSlots() {
	for (int i = 0; i < dices.size(); i++) {
		Dice dummy;
		dummy.Throw();
		Add(dummy);
	}
}

void Player::Add(Dice &toplace, Group &gr) {
	gr.Add(toplace);
}

void Group::Add(Dice &toplace) {
	for (int i = dices.size() - 1; i >= 0; i--) {
		if (!dices[i].GetValue()) {
			toplace.MoveToField();
			dices[i] = toplace;
			return;
		}
	}
}


void Player::RecalcTotal() {
	totalScore = 0;
	for (const auto& grp : groups) {
		totalScore += grp.GetScore();
	}
}

int Group::GetScore() const { 
	int total = 0; 
	for (auto& dice : dices) {
		total += dice.GetValue();
	}
	return total;
}
