#include "game.h"

Player::Player(int _rows, int _cols)
	: rows(_rows)
	, cols(_cols) 
{
	diceValues = new int* [rows];
	for (int i = 0; i < rows; i++) {
		diceValues[i] = new int[cols];
	}
	totalScores = new int[cols + 1];

	// fill with 0
	for (int i = 0; i < rows; i++) {
		totalScores[i] = 0;
		for (int j = 0; j < cols; j++) {
			diceValues[i][j] = 0;
		}
	}

	
}

Player::~Player()
{
	for (int i = 0; i < rows; i++) {
		delete[] diceValues[i];
	}
	delete[] diceValues;
}

void Player::AddDice(int row, int col, int value) {
	diceValues[row][col] = value;
	RecalcTotal();
}

void Player::RecalcTotal() {
	int totalSum = 0;
	for (int i = 0; i < cols; i++) {
		int colSum = 0;
		for (int j = 0; j < rows; j++) {
			colSum += diceValues[i][j];
		}
		totalScores[i] = colSum;
		totalSum += colSum;
	}
	totalScores[cols] = totalSum;
}