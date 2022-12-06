#pragma once
class Dice {
public:
	Dice();
	void MoveToField();

	void Throw();
	int GetValue() const;

	int GetPower() const;
	void SetPower(int pw);
	void Destroy();
	~Dice();	
	int value;
private:
	
	bool isOnField;
	int power;
};
