#include "ShakingSlot.h"
#include "field.h"
#include "random.h"

ShakingSlot::ShakingSlot() {}

ShakingSlot::~ShakingSlot() {}

void ShakingSlot::Bind(Field* _field) {
	field = _field;
}

void ShakingSlot::Animate(float deltaTime) {
	// debug
	//deltaTime = 0.01f;

	float xShift = deltaTime * XShakeIntensity;
	float yShift = deltaTime * YShakeIntensity;
	if (random::Bool()) {
		xShift = -xShift;
	}
	if (random::Bool()) {
		yShift = -yShift;
	}
	xPos = xOrig + xShift;
	yPos = yOrig + yShift;
	curTime += deltaTime;

}

bool ShakingSlot::DoneAnimating() {
	return curTime >= maxTime;
}

void ShakingSlot::Reset() {
	curTime = 0.f;
	
	isInited = false;
}

bool ShakingSlot::CheckIfInited() {
	return isInited;
}

float ShakingSlot::GetXOrig() {
	return xOrig;
}

float ShakingSlot::GetYOrig() {
	return yOrig;
}

void ShakingSlot::Init(float x, float y) {
	xPos = x;
	xOrig = x;
	yPos = y;
	yOrig = y;

	isInited = true;
}

void ShakingSlot::Render(MyColor color) {
	field->RenderSlot(color, xPos, yPos);
}
