#pragma once
class Dice {
public:
	Dice();
	void Destroy();
	~Dice();

	void Throw();
	void MoveToField();

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
