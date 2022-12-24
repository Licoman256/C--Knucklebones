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
	curTime += deltaTime;
	Vert shake = GetShakingOffsets();

	Vert pos = field->GetSlotCenter(groupIdx, rowIdx, yPlayerPos);
	float xCur = pos.x - slotLen * .5f;
	float yCur = pos.y + slotHeight * .5f;

	shakenPos = {
		xCur + shake.x,
		yCur + shake.y
	};
}

Vert ShakingSlot::GetShakingOffsets() {
	const float eps = 1e-6f;
	float aaa = curTime * 3.14f * (groupIdx + 1) / maxTime;
	if (aaa < eps) {
		return { 0, 0 };
	}

	float shift = abs(sinf(aaa) / sqrt(aaa));
	return { shift * xShakeIntensity,
			 shift * yShakeIntensity * shakingDirection };
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

	Animate(0.f);
}

void ShakingSlot::Render() {
	// slot with its dice
	field->RenderSlot(color, shakenPos.x, shakenPos.y, slotLen, slotHeight);
	if (dice && dice->IsOnField()) {
		field->Render(*dice, shakenPos.x, shakenPos.y);
	}
}

