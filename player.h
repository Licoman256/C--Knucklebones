#pragma once
#include <vector>
#include <queue>

#include "dice.h"

const int countGroupsPerPlayer = 4;
const int countRowsPerGroup = 3;

class Group {
public:
	Group(int _rows);
	void FillRandomSlots();
	bool Add(Dice &toplace);
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
	Player();
	void Bind(class Field* _field, int idx);
	void FillRandomSlots();
	void StartTurn();
	bool EndTurn(int grIdx);
	void RecalcTotal();

	~Player();
private:
	bool Add(Dice& toplace, Group& gr);

	class Field* field = nullptr;
	virtual void Render();
};

