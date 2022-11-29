#include "dice.h"
#include "random.h"

Dice::Dice()
	: value(0)
	, isOnField(false) {}

void Dice::Throw() {
	value = random::uni(random::rng);
	// animation of dice spinning in the box
}

int Dice::GetValue() const {
	return value;
}

void Dice::MoveToField() {
	isOnField = true;
}

Dice::~Dice() {}