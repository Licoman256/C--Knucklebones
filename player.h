#pragma once
#include "dice.h"
#include <vector>
const int countGroupsPerPlayer = 3;
const int countRowsPerGroup = 3;

class Group {
public:
	Group(int _rows);
	void FillRandomSlots();
	bool Add(Dice &toplace);
	int GetScore() const;
	
	~Group();
	
	std::vector<Dice> dices;
};

class Player {
private:
	int totalScore;
public:
	std::vector<Group> groups;
	Dice boxDice;
	bool isCur;
	Player();
	void FillRandomSlots();
	void StartTurn();
	bool EndTurn(int grIdx);
	bool Add(Dice &toplace, Group &gr);
	void RecalcTotal();

	~Player();
};
