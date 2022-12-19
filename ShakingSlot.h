#pragma once
#include "render.h"

class ShakingSlot: public AnimatingPhase {
	class Field* field = nullptr;
public:
	void Animate(float deltaTime);
	bool DoneAnimating();
	void Reset();

	ShakingSlot();
	void Bind(Field* _field);

	void Render(MyColor color);
	bool CheckIfInited();
	void Init(float x, float y);

	float GetXOrig();
	float GetYOrig();

	~ShakingSlot();
private:

	const float YShakeIntensity = 0.3f;
	const float XShakeIntensity = 0.3f;
	// [s]
	float maxTime = 0.15;
	float curTime = 0.f;

	float xPos;
	float yPos;

	float xOrig;
	float yOrig;

	bool isInited = false;
};
