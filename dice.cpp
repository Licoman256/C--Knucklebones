#include "dice.h"
#include "random.h"

Dice::Dice()
	: value(0)
	, isOnField(false)
	, multiplier(1) {}

void Dice::Throw() {
	value = random::Dice();
	// animation of dice spinning in the box
}

int Dice::GetValue() const {
	return value;
}

void Dice::SetMul(int pw) {
	 multiplier = pw;
}

int Dice::GetMul() const {
	return multiplier;
}

void Dice::MoveToField() {
	isOnField = true;
}

void Dice::Destroy() {
	isOnField = false;
	value = 0;
	multiplier = 1;
}

Dice::~Dice() {}