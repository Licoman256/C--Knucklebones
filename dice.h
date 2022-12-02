#pragma once
class Dice {
public:
	Dice();
	void MoveToField();

	void Throw();
	int GetValue() const;

	int GetPower() const;
	void SetPower(int pw);
	~Dice();	

private:
	int value;
	bool isOnField;
	int power;
};
