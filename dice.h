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
private:
	class LightArc* arc = nullptr;
	class Field* field = nullptr;
	virtual void Render(void);
	float travelTime = 0.f;
public:
	void Bind(Field* _field, LightArc* _arc);
	void Animate(float deltaTime);
	void ResetTime();
};
