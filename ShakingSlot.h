#pragma once
#include "player.h"

class ShakingSlot: public RenderElement, public Animated {
	class Field* field = nullptr;
public:
	ShakingSlot();
	void Bind(Field* _field);

	virtual void Render();
	virtual void Animate(float deltaTime);
	virtual bool DoneAnimating();
	virtual void Reset();

	void SetParams(Player& player, int rwIdx, int grIdx, MyColor clr, float yPlayerPos, int shakingDirection, float _maxTime);
	bool LaysUpon(int group, int row, bool playerIsActive);

	~ShakingSlot();
private:
	float xShakeIntensity;
	float yShakeIntensity;
	int shakingDirection = -1; // +1/-1

	float maxTime = 0.5f; // [s]
	float curTime = 0.f;   // [s]

	Vert shakenPos;

	const Dice *dice = nullptr;
	int rowIdx;
	int groupIdx;
	MyColor color;
	float yPlayerPos;
	Vert GetShakingOffsets();
	void ClearTarget();
};
