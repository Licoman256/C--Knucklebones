#pragma once
#include "dice.h"

const int countGroupsPerPlayer = 4;
const int countRowsPerGroup = 3;

class Group {
	int rows;
	// Dice* dices;
};

class Player {
private:
	int rows;
	int cols;
	int* colScores;
	int totalScore;
public:
	Dice** dices;

	//Group* groups;
	int countGroups;

	Player(int _rows, int _cols);
	void AddDice(int row, int col);
	void RecalcTotal();
	~Player();
};
