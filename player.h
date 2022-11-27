#pragma once
#include "dice.h"

const int countSlotRowsPerPlayer = 3;
const int countSlotColsPerPlayer = 3;


class Player {
private:
	int rows;
	int cols;
	int* colScores;
	int totalScore;
public:
	Dice** dices;
	Player(int _rows, int _cols);
	void AddDice(int row, int col);
	void RecalcTotal();
	~Player();
};
