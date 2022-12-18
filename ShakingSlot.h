#pragma once
#include "render.h"

class ShakingSlot {
	class Field* field = nullptr;
public:

	ShakingSlot();
	void Bind(Field* _field);

	void Animate(float deltaTime);
	bool DoneAnimating();
	void Render(MyColor color);
	
	bool CheckIfInited();
	void Init(float x, float y);

	float GetXOrig();
	float GetYOrig();

	void Reset();
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
