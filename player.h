#pragma once

const int countSlotRowsPerPlayer = 3;
const int countSlotColsPerPlayer = 3;


class Player {
private:
	int rows;
	int cols;
	int* totalScores;
public:
	int** diceValues;
	Player(int _rows, int _cols);
	void AddDice(int row, int col, int value);
	void RecalcTotal();
	~Player();
};
