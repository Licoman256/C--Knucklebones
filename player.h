#pragma once

const int countSlotRowsPerPlayer = 3;
const int countSlotColsPerPlayer = 3;


class Player {
private:
	int totalScore = 0;
	int** diceValues;
	int rows;
	int cols;
public:
	Player(int _rows, int _cols);
	~Player();
};
