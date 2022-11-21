#include "game.h"

Player::Player(int _rows, int _cols)
	: rows(_rows)
	, cols(_cols) 
{
	diceValues = new int* [rows];
	for (int i = 0; i < rows; i++) {
		diceValues[i] = new int[cols];
	}
}

Player::~Player()
{
	for (int i = 0; i < rows; i++) {
		delete[] diceValues[i];
	}
	delete[] diceValues;
}

