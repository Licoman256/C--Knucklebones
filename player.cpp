#include "game.h"

Player::Player(int _rows, int _cols)
	: rows(_rows)
	, cols(_cols) 
{
	diceValues = new int* [rows];
	for (int i = 0; i < rows; i++) {
		diceValues[i] = new int[cols];
	}
	//fill with 0
	for (int i = 0; i < rows; i++) {
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
}

