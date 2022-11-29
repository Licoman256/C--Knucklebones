#pragma once
#include "dice.h"
#include <vector>
const int countGroupsPerPlayer = 4;
const int countRowsPerGroup = 3;

class Group {
public:
	Group(int _rows);
	void FillRandomSlots();
	void Add(Dice &toplace);
	int GetScore() const;
	
	~Group();
	
	std::vector<Dice> dices;
};

class Player {
private:
	int totalScore;
public:
	std::vector<Group> groups;

	Player();
	void FillRandomSlots();
	void Add(Dice &toplace, Group &gr);
	void RecalcTotal();

	~Player();
};
