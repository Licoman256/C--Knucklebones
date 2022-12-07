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
	, isAI(true)
{
	groups.reserve(countGroupsPerPlayer);
	Group dummy(countRowsPerGroup);
	for (int i = 0; i < countGroupsPerPlayer; i++) {
		groups.push_back(dummy);
	}
}

Player::~Player()
{}

void Player::StartTurn() {
	boxDice.Throw();
	isActive = true;
}

void Player::DestroyDices(int diceVal, int grIdx) {	
		groups[grIdx].DestroyDices(diceVal);
		RecalcScore();
}

void Group::DestroyDices(int diceVal) {
	bool destroyed = false;
	for (auto& dice : dices) {
		if (dice.GetValue() == diceVal) {
			dice.Destroy();
			destroyed = true;
			countDices--;
		}
	}

	if (destroyed) {
		FallDown();
		isFull = false;
	}
}

void Group::FallDown() {
	for (int i = static_cast<int>(dices.size()); --i >= 0;) {
		// save for later
		auto val = dices[i].GetValue();
		auto pow = dices[i].GetPower();
		if (val) {
			countDices--;
			dices[i].Destroy();

			// copy as low as possible
			Dice toPlace;
			toPlace.value = val;
			toPlace.SetPower(pow);
			toPlace.MoveToField();
			
			Add(toPlace);
		}
	}
}

bool Player::TryAddingToGroup(int grIdx) {
	return Add(boxDice, groups[grIdx]);
}

bool Player::Add(Dice &toplace, Group &gr) {
	bool added = gr.Add(toplace);
	RecalcScore();
	return added;
}

bool Group::Add(Dice &toplace) {
	for (int i = static_cast<int>(dices.size()); --i >= 0;) {
		if (!dices[i].GetValue()) {
			toplace.MoveToField();
			dices[i] = toplace;
			countDices++;
			if (countDices == countRowsPerGroup) {
				isFull = true;
			}
			return true;
		}
	}
	return false;
}

void Player::RecalcScore() {
	int fullness = 0;
	totalScore = 0;
	for (auto& grp : groups) {
		grp.SetPowers();
		totalScore += grp.GetScore();
		fullness += grp.isFull;
	}
	if (fullness == countGroupsPerPlayer) {
		isFull = true;
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

