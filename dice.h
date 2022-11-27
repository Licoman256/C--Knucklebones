#pragma once
class Dice {
public:
	Dice();
	void Throw();
	void MoveToField();
	int GetValue();
	~Dice();	

private:
	int value;
	bool isOnField;
};
