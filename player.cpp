#include "game.h"
#include "dice.h"

Player::Player(int _rows, int _cols)
	: rows(_rows)
	, cols(_cols)
	, totalScore(0)
{
	// TO DEL
	rows = 4;
	cols = 4;

	// ok
	dices = new Dice* [rows];
	for (int i = 0; i < rows; i++) {
		dices[i] = new Dice[cols];
	}
	colScores = new int[cols];

	// TO DEL
	rows = _rows;
	cols = _cols;
}

Player::~Player()
{
	for (int i = 0; i < rows; i++) {
		delete[] dices[i];
	}
	delete[] dices;
}

void Player::AddDice(int row, int col) {
	dices[row][col].Throw();
	dices[row][col].MoveToField();
	RecalcTotal();
}

void Player::RecalcTotal() {
	int totalSum = 0;
	for (int i = 0; i < cols; i++) {
		int colSum = 0;
		for (int j = 0; j < rows; j++) {
			colSum += dices[i][j].GetValue();
		}
		colScores[i] = colSum;
		totalSum += colSum;
	}
	totalScore = totalSum;
}