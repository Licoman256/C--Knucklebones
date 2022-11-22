#pragma once

const int countSlotRowsPerPlayer = 3;
const int countSlotColsPerPlayer = 3;


class Player {
private:
	int totalScore = 0;
	int rows;
	int cols;
public:
	int** diceValues;
	Player(int _rows, int _cols);
	void AddDice(int row, int col, int value);
	~Player();
};
