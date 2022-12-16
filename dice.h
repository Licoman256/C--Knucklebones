#pragma once
#include "render.h"
class Dice {
public:
	Dice();
	void Destroy();
	~Dice();

	void Throw();
	void MoveToField();
	bool CheckIfOnField() const;

	int  GetValue() const;
	void SetValue(int v) { value = v; }
	int  GetMul() const;
	void SetMul(int pw);

	float fallProgress = 1;
private:
	bool isOnField;
	int value;
	int multiplier;
};

class MovingDice : public RenderElement {
public:
	void Bind(class Field* _field, class LightArc* _arc);
	void Animate(float deltaTime);
	void SetValue(int val);
	void ResetTime();
	bool DoneAnimating();
private:
	LightArc* arc = nullptr;
	Field* field = nullptr;
	virtual void Render(void);
	int value = 0;
	float travelDist = 0.f;
	const float startingSpeed = 0.f;
	const float maxSpeed = 2.0f;
	const float accel = 0.02f;
	float speed = startingSpeed;
};
