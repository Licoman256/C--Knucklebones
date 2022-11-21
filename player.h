#pragma once
class Player {
private:
	int totalScore = 0;
	int** diceValues;
	int rows;
	int cols;
public:
	Player(int mrows, int mcols): 
		        rows(mrows), cols(mcols) {
		diceValues = new int* [rows];
		for (int i = 0; i < rows; i++) {
			diceValues[i] = new int[cols];
		}
	}
	~Player() {
		for (int i = 0; i < rows; i++) {
			delete[] diceValues[i];
		}
		delete[] diceValues;
	}
};
