#include "dice.h"
#include "random.h"
#include "LightArc.h"
#include "field.h"
#include <cassert>

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

bool Dice::CheckIfOnField() const {
	return isOnField;
}

void Dice::Destroy() {
	isOnField = false;
	value = 0;
	multiplier = 1;
}

Dice::~Dice() {}

void MovingDice::Bind(Field* _field, LightArc* _arc) {
	field = _field;
	arc = _arc;
}

void MovingDice::SetValue(int val) {
	value = val;
}

void MovingDice::Reset() {
	travelDist = 0;
	speed = startingSpeed;
}

bool MovingDice::DoneAnimating() {
	return arc->DoneAnimating(travelDist);
}

void MovingDice::Animate(float deltaTime) {
	// debug
	//deltaTime = 0.01;
	
	if (speed <= maxSpeed) {
		speed += accel;
	}
	travelDist += speed * deltaTime;
}

void MovingDice::Render() {
	
	// get point of center of arc
	Vert midPoint = arc->GetPoint(travelDist);

	// place dice
	float xSlotStart = midPoint.x - slotLen * .5f;
	float ySlotStart = midPoint.y + slotHeight * .5f;

	Dice dummy;
	dummy.SetValue(value);
	field->Render(dummy, xSlotStart, ySlotStart);
}

bool LightArc::DoneAnimating(float travelDist) {
	if (travelDist >= elems[COUNT_QUADS - 1].trvDist) {
		return true;
	}
	return false;
}

// linear interpolation
float Lerp(float from, float frac, float to) {
	return from * (1.f - frac) + to * frac;
}

// IN: [m]
Vert LightArc::GetPoint(float travelDist) {
	// convert distance to travelled part of the trajectory [0, COUNT_QUADS] 
	int quadIdx;
	float fraction;
	ConvertTravelDist(travelDist, quadIdx, fraction);
	assert(quadIdx < COUNT_QUADS);

	// lerp
	Vert result = { Lerp(elems[quadIdx].side.md.x, fraction, elems[quadIdx + 1].side.md.x),
					Lerp(elems[quadIdx].side.md.y, fraction, elems[quadIdx + 1].side.md.y) };

	return result;
}

void LightArc::ConvertTravelDist(float travelDist, int& quadIdx, float& fraction) {
	for (int i = 0; i < COUNT_QUADS; i++) {
		if (elems[i].trvDist > travelDist) {
			quadIdx = i - 1;
			fraction = (travelDist       - elems[i - 1].trvDist)
					 / (elems[i].trvDist - elems[i - 1].trvDist);
			return;
		}
	}
}
