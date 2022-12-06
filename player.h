#pragma once
#include <vector>
#include <queue>
#include "render.h"
#include "dice.h"

const int countGroupsPerPlayer = 4;
const int countRowsPerGroup = 3;

class Group {
public:
	Group(int _rows);
	void FillRandomSlots();
	bool Add(Dice &toplace);
	void DestroyDices(int diceVal);
	void FallDown();
	int GetScore() const;
	void SetPowers();
	~Group();
	
	std::vector<Dice> dices;
};

class Player : public RenderElement {
public:
	std::vector<Group> groups;
	Dice boxDice;
	bool isActive;
	int totalScore;
	bool isAI;

	Player();
	void Bind(class Field* _field, int idx);
	void StartTurn();
	void DestroyDices(int diceVal, int grIdx);
	bool EndTurn(int grIdx);
	void RecalcTotal();

	~Player();
	// debug
	void FillRandomSlots();
private:
	bool Add(Dice& toplace, Group& gr);
	class Field* field = nullptr;
	virtual void Render();
};

