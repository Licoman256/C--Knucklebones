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

void MovingDice::ResetTime() {
	travelDist = 0;
}

bool MovingDice::DoneAnimating() {
	if (travelDist >= arc->COUNT_QUADS - 1) {
		return true;
	}
	return false;
}

void MovingDice::Animate(float deltaTime) {
	static float speed = 20.f;
	travelDist += speed * deltaTime;
}

void MovingDice::Render() {
	//if (travelTime >= arc->COUNT_QUADS){
	//	return;
	//}
	
	// get point of center of arc
	Vert midPoint = arc->GetPoint(travelDist);

	// place dice
	float xSlotStart = midPoint.x - slotLen * .5f;
	float ySlotStart = midPoint.y + slotHeight * .5f;

	Dice dummy;
	dummy.SetValue(value);
	field->Render(dummy, xSlotStart, ySlotStart);
}

// IN: [m]
Vert LightArc::GetPoint(float travelDist) {
	// convert distance to travelled part of the trajectory [0, COUNT_QUADS] 
	float travelledTraj = travelDist;

	// which quad we are using
	int quadIdx = static_cast<int>(travelledTraj);
	assert(quadIdx < COUNT_QUADS - 1);

	// calucalate which part of middle line we need
	Vert middleStart = { (upSide[quadIdx].x + dnSide[quadIdx].x) * .5f,
						 (dnSide[quadIdx].y + upSide[quadIdx].y) * .5f };
	Vert middleFinish = { (upSide[quadIdx + 1].x + dnSide[quadIdx + 1].x) * .5f,
						  (dnSide[quadIdx + 1].y + upSide[quadIdx + 1].y) * .5f };

	Vert middleDelta = { middleFinish.x - middleStart.x,
						 middleFinish.y - middleStart.y};

	float fraction = travelledTraj - quadIdx;

	Vert result = { middleStart.x + middleDelta.x * fraction,
					middleStart.y + middleDelta.y * fraction };
	return result;
}
