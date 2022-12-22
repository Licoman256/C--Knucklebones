#include "game.h"
#include "stb/stb_image.h"
#include "random.h"
#include <iostream>
#include <cassert>
#include <chrono>
//#include <Windows.h>

Game::Game()
	: window(nullptr)
	, players(countPlayers) {
	_this = this;

	/* Initialize the library */
	if (!glfwInit())
		return;
	doneGlfwInit = true;

	window = field.CreateWindow();
	if (!window) {
		return;
	}

	mainState = ES_STARTUP;
}

std::chrono::steady_clock::duration timeChronoStart;
typedef long long unsigned int u64;

void ChronoStart() {
	timeChronoStart = std::chrono::high_resolution_clock::now().time_since_epoch();
}

u64 ChronoRound() {
	// calc delta from the previous round
	auto finish = std::chrono::high_resolution_clock::now().time_since_epoch();
	auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(finish - timeChronoStart).count();

	// start new round
	timeChronoStart = finish;

	return delta;
}


void Game::Tick() {
	// do FSM
	switch (mainState) {
	case ES_STARTUP:              OnStartup();				        break;
 	case ES_ANNOUNCE_ROUND:		  AnnounceRound();					break;
	case ES_THROW_DICE:			  OnThrowDice();					break;
	case ES_AI_INPUT:			  OnAISelectKeyToPress();			// no break
	case ES_WAIT_PLAYER_INPUT:	  HandlePressedKey();			    break;
	case ES_MOVE_DICE_TO_FIELD:	  OnMoveToField();					break;
	case ES_SLOT_SHAKING:		  OnSlotShaking();					break;
	case ES_DESTROY_DICES:		  OnDestroyDices();					break;
	case ES_REODER_IN_GROUPS:	  OnReorderInGroups();				break;
	case ES_UPDATE_SCORE:		  OnUpdateScore();			        break;
	case ES_CHANGE_ACTIVE_PLAYER: ChangeActivePlayer();				break;
	case ES_GAME_END_WIN:											break;
	case ES_GAME_END_DRAW:											break;
	case ES_ASK_FOR_RESTART:										break;
	default:														break;
	}
	pressedKey = 0;

	// always animate
	Animate();
}

void Game::OnThrowDice() {
	// throw the dice
	players[curPlayerIdx].StartTurn();

	// play animation

	// decide next state
	if (players[curPlayerIdx].isAI) {
		mainState = ES_AI_INPUT;
	} else {
		mainState = ES_WAIT_PLAYER_INPUT;
	}
}

void Game::OnAISelectKeyToPress() {
	assert(players[curPlayerIdx].isAI);
	// "think"
	//Sleep(50);
	// for now AI players hit random keys
	pressedKey = '1' + random::Group();
}

void Game::HandlePressedKey() {
	players[curPlayerIdx].isThinking = true;
	// input is from any of two: player or AI
	
	// is it anything meaningful?
	bool isAcceptable = ('1' <= pressedKey && pressedKey < '1' + countGroupsPerPlayer);
	if (!isAcceptable) {
		return;
	}

	// convert input to action
	selectedGroupIdx = pressedKey - '1';

	// try to perform the action
	auto& curPlayer = players[curPlayerIdx];
	if (curPlayer.TryAddingToGroup(selectedGroupIdx)) {
		field.PrepareArc(curPlayer);

		// proceed to draw and animate the arc
		mainState = ES_MOVE_DICE_TO_FIELD;
		players[curPlayerIdx].isThinking = false;
	}
}

void Game::OnMoveToField() {
	// play animation
	field.arc.Animate(deltaTime);
	
	// done => next state
	if (field.movingDice.DoneAnimating()) {
		players[curPlayerIdx].SetDicesOnField();
		field.movingDice.Reset();
		mainState = ES_SLOT_SHAKING;
	}
}

void Game::OnSlotShaking() {
	if (field.shakingSlot.DoneAnimating()) {
		players[curPlayerIdx].RecalcScore();
		field.shakingSlot.Reset();
		mainState = ES_DESTROY_DICES;
	}
}

void Game::OnDestroyDices() {
	// tell other players to remove their dices
	auto diceVal = players[curPlayerIdx].boxDice.GetValue();
	for (auto& plr : players) {
		if (!plr.isActive) {
			plr.DestroyDices(diceVal, selectedGroupIdx);
		}
	}

	// animation

	mainState = ES_REODER_IN_GROUPS;
}

void Game::OnReorderInGroups() {
	bool doneFalling = true;

	// allow all players to fall down
	for (auto& plr : players) {
		if (!plr.isActive) {
			doneFalling = plr.FallDown() && doneFalling;
		}
	}

	if (doneFalling) {
		mainState = ES_UPDATE_SCORE;
	}
}

void Game::OnUpdateScore() {

	// all players to recalculate score
	for (auto& plr : players) {
		if (!plr.isActive) {
			plr.RecalcScore();
		}
	}

	// animation
	mainState = ES_CHANGE_ACTIVE_PLAYER;
}

void Game::ChangeActivePlayer() {
	// end current turn
	auto& curPlayer = players[curPlayerIdx];
	curPlayer.isActive = false;

	// check for game end
	if (curPlayer.isFull) {
		End();
		return;
	}

	// loop around
	curPlayerIdx++;
	curPlayerIdx %= countPlayers;

	// game continues
	mainState = ES_THROW_DICE;
}
	

void Game::AnnounceRound() {
	// play animation
	mainState = ES_THROW_DICE;
}

void Game::OnStartup() {
	ChronoStart();

	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, resize_callback);

	// bind all players
	for (int i = 0; i < countPlayers; i++) {
		players[i].Bind(&field, i);
	}

	// gfx
	field.LoadMainBlockTex();
	field.PrepareShaders();
	field.EnableTransparancy();

	// debug
	#ifdef FILLSLOTS	
		FillRandomSlots();
	#endif

	// part of game logic
	players[0].isAI = false;
	//players[2].isAI = false;
	players[0].StartTurn();

	// next state
	mainState = ES_ANNOUNCE_ROUND;
}

Game::~Game() {
	if (doneGlfwInit) {
		glfwTerminate();
	}
}

void Game::Render() {
	// part that renders always 
	field.RenderCommon(window);

	// other depends on the main state
	FillRendQueue();
	for (auto rElem : rQueue) {
		rElem->Render();
	}

	// Swap front and back buffers
	glfwSwapBuffers(window);
}

void Game::FillRendQueue() {
	rQueue.clear();

	// do we need players?
	if (ES_ANNOUNCE_ROUND < mainState && mainState <= ES_GAME_END_DRAW) {
		for (auto& player : players) {
			rQueue.push_back(&player);
		}
	}

	if (mainState == ES_MOVE_DICE_TO_FIELD) {
		rQueue.push_back(&field.shakingSlot);
		rQueue.push_back(&field.arc);
		rQueue.push_back(&field.movingDice);
	}
	
	if (mainState == ES_SLOT_SHAKING) {
		rQueue.push_back(&field.shakingSlot);
	}

	// 
	// fill render queue depending on main state
	// popup.Render();
}

void Game::Animate() {
	// how much time is spent
	deltaTime = ChronoRound() / 1000.f;
	FillAnimQueue();
	for (auto aElem : aQueue) {
		aElem->Animate(deltaTime);
	}
}

void Game::FillAnimQueue() {
	aQueue.clear();

	if (mainState == ES_MOVE_DICE_TO_FIELD) {
		aQueue.push_back(&field.movingDice);
	}

	if (mainState == ES_SLOT_SHAKING) {
		aQueue.push_back(&field.shakingSlot);
	}

}

void Game::End() {
	// find out max score
	int maxScore = -1;
	for (int i = static_cast<int>(players.size()); --i >= 0;) {
		if (maxScore < players[i].totalScore) {	
			maxScore = players[i].totalScore;
		}
	}

	// mark all winners
	int countOfWinners = 0;
	for (int i = static_cast<int>(players.size()); --i >= 0;) {
		if (maxScore == players[i].totalScore) {
			countOfWinners++;
			std::cout << "Player " << i + 1 << " wins with total score " << maxScore << std::endl; // TDODODD
		}
	}

	// stop playing, start rendering the result
	mainState = ES_GAME_END_WIN;
}
