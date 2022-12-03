#pragma once
#include "dice.h"
#include <vector>
const int countGroupsPerPlayer = 4;
const int countRowsPerGroup = 3;

class Group {
public:
	Group(int _rows);
	void FillRandomSlots();
	bool Add(Dice &toplace);
	int GetScore() const;
	void SetPowers();
	~Group();
	
	std::vector<Dice> dices;
};

class Player {
public:
	std::vector<Group> groups;
	Dice boxDice;
	bool isActive;
	Player();
	void FillRandomSlots();
	void StartTurn();
	bool EndTurn(int grIdx);
	void RecalcTotal();

	~Player();
private:
	int totalScore;
	bool Add(Dice& toplace, Group& gr);
};
