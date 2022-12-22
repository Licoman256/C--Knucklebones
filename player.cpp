#include "game.h"
#include "dice.h"

Group::Group(int _rows = Constants::countRowsPerGroup)
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
}

void Group::DestroyDices(int diceVal) {
	for (auto& dice : dices) {
		if (dice.GetValue() == diceVal) {
			dice.Destroy();
			isUnderAttack = true;
			isFull = false;
			countDices--;
		}
	}
}

// RET: true => done falling
bool Player::FallDown() {
	bool doneFalling = true;
	for (auto& gr: groups) {
		doneFalling = gr.FallDown() && doneFalling;
	}
	return doneFalling;
}

// RET: true => done falling
bool Group::FallDown() {
	if (!isUnderAttack) {
		return true;
	}
	isUnderAttack = false;

	// make animation smoother by slowing it down
	//Sleep(200);

	// killed dices are now holes
	// they should drift up, one step at a time
	for (int i = static_cast<int>(dices.size()); --i > 0;) {
		if (0 == dices[i].GetValue() && 
			0 != dices[i-1].GetValue()) {
			std::swap<Dice>(dices[i], dices[i-1]);
			i--;
			isUnderAttack = true;
		}
	}

	return false;
}

bool Player::TryAddingToGroup(int grIdx) {
	addingTo = grIdx;
	return Add(boxDice, groups[grIdx]);
}

bool Player::Add(Dice &toplace, Group &gr) {
	bool added = gr.Add(toplace);
	return added;
}

bool Group::Add(Dice &toplace) {
	for (int i = static_cast<int>(dices.size()); --i >= 0;) {
		if (!dices[i].GetValue()) {
			dices[i] = toplace;
			addingTo = i;
			countDices++;
			if (countDices == Constants::countRowsPerGroup) {
				isFull = true;
			}
			return true;
		}
	}
	return false;
}

void Player::SetDicesOnField() {
	groups[addingTo].MoveToField();
}

void Group::MoveToField() {
	dices[addingTo].MoveToField();
}

void Player::RecalcScore() {
	int fullness = 0;
	totalScore = 0;
	for (auto& grp : groups) {
		grp.SetPowers();
		grp.SetScore();
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
			dice.SetMul(vals[val - 1]);
		}
	}
}

int Group::GetScore() const {	
	return score;	
}

void Group::SetScore() {
	score= 0;
	for (auto& dice : dices) {
		score += dice.GetValue() * dice.GetMul();
	}
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
