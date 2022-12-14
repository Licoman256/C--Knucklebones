#include "dice.h"
#include "random.h"
#include "LightArc.h"
#include "field.h"

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
	travelTime = 0;
}

bool MovingDice::DoneAnimating() {
	if (travelTime >= arc->COUNT_QUADS - 1) {
		return true;
	}
	return false;
}

void MovingDice::Animate(float deltaTime) {
	static float speed = 20.f;
	travelTime += speed * deltaTime;
}

void MovingDice::Render() {
	//if (travelTime >= arc->COUNT_QUADS){
	//	return;
	//}
	
	// get point of center of arc
	Vert midPoint = arc->GetPoint(travelTime);

	// place dice
	float xSlotStart = midPoint.x - slotLen / 2;
	float ySlotStart = midPoint.y + slotHeight / 2;

	Dice dummy;
	dummy.SetValue(value);
	field->Render(dummy, xSlotStart, ySlotStart);
}

Vert LightArc::GetPoint(float travelTime) {
	// which quad we are using
	int quadIdx = static_cast<int>(travelTime);
	if (quadIdx + 1 >= COUNT_QUADS) {
		return Vert();
	}

	// calucalate which part of middle line we need
	Vert middleStart = { (upSide[quadIdx].x + upSide[quadIdx].x) / 2,
						 (dnSide[quadIdx].y + dnSide[quadIdx].y) / 2 };
	Vert middleFinish = { (upSide[quadIdx + 1].x + upSide[quadIdx + 1].x) / 2,
						  (dnSide[quadIdx + 1].y + dnSide[quadIdx + 1].y) / 2 };

	Vert middleDelta = { middleFinish.x - middleStart.x,
						 middleFinish.y - middleStart.y};

	float fraction = travelTime - quadIdx;

	Vert result = { middleStart.x + middleDelta.x * fraction,
					middleStart.y + middleDelta.y * fraction };
	return result;
}
