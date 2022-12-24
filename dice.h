#pragma once
#include "render.h"
class Dice {
public:
	Dice();
	void Destroy();
	~Dice();

	void Throw();
	void MoveToField();
	bool IsOnField() const { return isOnField; }

	int  GetValue() const { return value; }
	void SetValue(int v) { value = v; }

	int  GetMul() const;
	void SetMul(int pw);

	float fallProgress = 1;
private:
	bool isOnField;
	int value;
	int multiplier;
};

class MovingDice : public RenderElement, public Animated {
public:
	virtual void Animate(float deltaTime);
	virtual bool DoneAnimating();
	virtual void Reset();

	void Bind(class Field* _field, class LightArc* _arc);
	void SetValue(int val);
private:
	LightArc* arc = nullptr;
	Field* field = nullptr;
	virtual void Render(void);
	int value = 0;
	float travelDist = 0.f;
	const float startingSpeed = 0.2f;
	const float maxSpeed = 20.0f;
	const float accel = 0.02f;
	float speed = startingSpeed;
};
