#pragma once
#include <vector>
#include <queue>
#include "render.h"
#include "dice.h"

const int countGroupsPerPlayer = 4;
const int countRowsPerGroup = 6;

class Group {
public:
	Group(int _rows);
	void FillRandomSlots();
	bool Add(Dice &toplace);
	void DestroyDices(int diceVal);
	bool FallDown();
	int GetScore() const;
	void SetPowers();
	~Group();
	
	std::vector<Dice> dices;
	int countDices = 0;
	bool isFull = false;
	bool isUnderAttack = false;
};

class Player : public RenderElement {
public:
	std::vector<Group> groups;
	Dice boxDice;
	bool isActive;
	int totalScore;
	bool isAI;
	bool isFull = false;

	Player();
	void Bind(class Field* _field, int idx);
	void StartTurn();
	void DestroyDices(int diceVal, int grIdx);
	bool FallDown();
	bool TryAddingToGroup(int grIdx);
	void RecalcScore();

	~Player();
	// debug
	void FillRandomSlots();
private:
	bool Add(Dice& toplace, Group& gr);
	class Field* field = nullptr;
	virtual void Render();
};

