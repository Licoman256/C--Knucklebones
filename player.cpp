#include "game.h"
#include "dice.h"

Group::Group(int _rows = countRowsPerGroup)
	: dices(_rows)
{}
Group::~Group()
{}

Player::Player()
	: totalScore(0)
	, isActive(false)
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
	boxDice.Throw();
	isActive = true;
}

bool Player::EndTurn(int grIdx) {
	bool added = Add(boxDice, groups[grIdx]);
	if (added) {
		isActive = false;
	}
	return added;
}

bool Player::Add(Dice &toplace, Group &gr) {
	bool added = gr.Add(toplace);
	RecalcTotal();
	return added;
}

bool Group::Add(Dice &toplace) {
	for (int i = static_cast<int>(dices.size()); --i >= 0;) {
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
	for (auto& grp : groups) {
		grp.SetPowers();
		totalScore += grp.GetScore();
	}
}

void Group::SetPowers() {
	// prepare array
	int vals[6];
	for (int i = 0; i < 6; i++) {
		vals[i] = 0;
	}

	// count dices of same value
	for (auto& dice : dices) {
		int val = dice.GetValue();
		if (val) {
			vals[val - 1]++;
		}
	}

	// set powers
	for (auto& dice : dices) {
		int val = dice.GetValue();
		if (val) {
			dice.SetPower(vals[val - 1]);
		}
	}
}

int Group::GetScore() const {
	int total = 0;
	for (auto& dice : dices) {
		total += dice.GetValue() * dice.GetPower();
	}
	return total;
	
}

void Player::Bind(Field* _field, int idx) 	{
	// we'll need it on render
	field = _field;

	// calc graphic sizes
	field->AddToLayout(idx, *this);
}

void Player::Render() {
	field->Render(*this);
}
