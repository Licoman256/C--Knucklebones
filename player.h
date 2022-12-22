#pragma once
#include <vector>
#include <queue>
#include "render.h"
#include "dice.h"

class Group {
public:
	Group(int _rows);
	void FillRandomSlots();
	bool Add(Dice &toplace);
	void MoveToField();
	void DestroyDices(int diceVal);
	bool FallDown();
	void SetScore();
	int GetScore() const;
	void SetPowers();
	~Group();
	
	std::vector<Dice> dices;
	int addingTo = -1;
	int countDices = 0;
	int score = 0;

	bool isFull = false;
	bool isUnderAttack = false;
};

class Player : public RenderElement {
public:
	std::vector<Group> groups;
	Dice boxDice;

	bool isActive;
	bool isThinking = false;
	int totalScore;

	bool isAI;
	bool isFull = false;

	int addingTo = 0;

	Player();
	void Bind(class Field* _field, int idx);
	void StartTurn();
	void DestroyDices(int diceVal, int grIdx);
	bool FallDown();
	bool TryAddingToGroup(int grIdx);
	void SetDicesOnField();
	void RecalcScore();

	~Player();
	// debug
	void FillRandomSlots();
private:
	bool Add(Dice& toplace, Group& gr);
	class Field* field = nullptr;
	virtual void Render();
};

