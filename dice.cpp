#include "dice.h"
#include "random.h"

Dice::Dice()
	: value(0)
	, isOnField(false)
	, power(1) {}

void Dice::Throw() {
	value = random::randomDice(random::rng);
	// animation of dice spinning in the box
}

int Dice::GetValue() const {
	return value;
}

void Dice::SetPower(int pw) {
	 power = pw;
}

int Dice::GetPower() const {
	return power;
}

void Dice::MoveToField() {
	isOnField = true;
}

void Dice::Destroy() {
	isOnField = false;
	value = 0;
	power = 1;
}

Dice::~Dice() {}