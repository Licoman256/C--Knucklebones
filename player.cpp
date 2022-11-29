#include "game.h"
#include "dice.h"
Group::Group(int _rows = countRowsPerGroup)
	: dices(_rows)
{}
Group::~Group()
{}

Player::Player()
	: totalScore(0)
	, isCur(false)
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

void Player::StartTurn() {
	Dice dummy;
	dummy.Throw();
	boxDice = dummy;
	isCur = true;
}

bool Player::EndTurn(int grIdx) {
	bool added = Add(boxDice, groups[grIdx]);
	if (added) {
		isCur = false;
	}
	return added;
}

bool Player::Add(Dice &toplace, Group &gr) {
	return gr.Add(toplace);
}

bool Group::Add(Dice &toplace) {
	for (int i = dices.size() - 1; i >= 0; i--) {
		if (!dices[i].GetValue()) {
			toplace.MoveToField();
			dices[i] = toplace;
			return true;
		}
	}
	return false;
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
