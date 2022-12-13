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

void MovingDice::ResetTime() {
	travelTime = 0;
}

void MovingDice::Animate(float deltaTime) {
	static float speed = 100.f;
	travelTime += speed * deltaTime;
}

void MovingDice::Render() {
	if (travelTime >= arc->COUNT_QUADS){
		return;
	}
	MyColor color = colors::white;
	glColor3d(color.red, color.green, color.blue);
	
	int quadIdx = travelTime;
	field->RenderTexture(arc->upSide[quadIdx], arc->dnSide[quadIdx], colors::white, E_DICE_6, Vert{1,1}, Vert{0, 0});
}
