#include "ShakingSlot.h"
#include "player.h"
#include "field.h"
#include "random.h"

ShakingSlot::ShakingSlot() {
	ClearTarget();
}

void ShakingSlot::ClearTarget()
{
	dice = nullptr;
	rowIdx = -1;
	groupIdx = -1;
}

ShakingSlot::~ShakingSlot() {}

void ShakingSlot::Bind(Field* _field) {
	field = _field;
}

void ShakingSlot::Animate(float deltaTime) {
	// debug
	//deltaTime = 0.01f;

	//float xShift = deltaTime * xShakeIntensity;
	//float yShift = deltaTime * yShakeIntensity;

	//xPos = xOrig + xShift;
	//yPos = yOrig + yShift;
	curTime += deltaTime;

	//float lenShift = -startLen * (1 - minLenCoeff) * 2 / maxTime;
	//float heightShift = -startHeight * (1 - minHeightCoeff) * 2 / maxTime;
	//if (curTime >= maxTime / 2 && !growing) {
	//	lenShift = -lenShift;
	//	heightShift = -heightShift;
	//	growing = true;
	//}

	//len += lenShift;
	//height += heightShift;
	//
	//xPos += (startLen - len) / 2;
	//yPos -= (startHeight - height) / 2;

}

bool ShakingSlot::DoneAnimating() {
	return curTime >= maxTime;
}

void ShakingSlot::Reset() {
	curTime = 0.f;
	ClearTarget();
}

bool ShakingSlot::LaysUpon(int group, int row, bool playerIsActive) {
	if (playerIsActive
		&& row == rowIdx
		&& group == groupIdx) {
		return true;
	}
	return false;
}

void ShakingSlot::SetParams(Player& player, int rwIdx, int grIdx, MyColor clr, float _yPlayerPos, int _shakingDirection, float _maxTime) {
	dice = &player.groups[grIdx].dices[rwIdx];
	rowIdx = rwIdx;
	groupIdx = grIdx;
	color = clr;
	yPlayerPos = _yPlayerPos;
	shakingDirection = _shakingDirection;
	maxTime = _maxTime;

	xShakeIntensity = maxTime / 15;
	yShakeIntensity = maxTime / 15;
}

void ShakingSlot::Render() {
	// slot with its dice
	Vert pos = field->GetSlotCoords(groupIdx, rowIdx, yPlayerPos);
	float xCur = pos.x - slotLen / 2;
	float yCur = pos.y + slotHeight / 2;
	
	Vert shake = GetShakingOffsets();
	xCur += shake.x;
	yCur += shake.y;

	field->RenderSlot(color, xCur, yCur, slotLen, slotHeight);
	if (dice && dice->IsOnField()) {
		field->Render(*dice, xCur, yCur);
	}
}

Vert ShakingSlot::GetShakingOffsets() {
	float aaa = curTime * 3.14f * (groupIdx + 1) / maxTime;
	if (aaa) {
		float shift = abs(sinf(aaa) / sqrt(aaa));
		return { shift * xShakeIntensity, shift * yShakeIntensity * shakingDirection };
	}
	return { 0, 0 };
}