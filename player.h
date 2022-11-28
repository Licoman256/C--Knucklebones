#pragma once
#include "dice.h"
#include <vector>
const int countGroupsPerPlayer = 4;
const int countRowsPerGroup = 3;

class Group {
public:
	Group(int _rows);
	std::vector<Dice> dices;
	~Group();
	int GetScore() const;
	void FillRandomSlots();
};

class Player {
private:
	int totalScore;
public:
	std::vector<Group> groups;

	Player();
	void RecalcTotal();
	void FillRandomSlots();

	~Player();
};
