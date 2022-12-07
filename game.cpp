#include "game.h"
#include "stb/stb_image.h"
#include "random.h"
#include <iostream>
#include <cassert>

Game::Game()
	: window(nullptr)
	, players(countPlayers) {
	_this = this;

	/* Initialize the library */
	if (!glfwInit())
		return;
	doneGlfwInit = true;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(field.WINDOW_WIDTH, field.WINDOW_HEIGHT, "Knucklebones", NULL, NULL);
	if (!window) {
		return;
	}

	mainState = ES_STARTUP;
	return;
}

void Game::Tick() {
	switch (mainState) {
	case ES_STARTUP:                OnStartup();       break;
	case ES_ANNOUNCE_ROUND: mainState = ES_THROW_DICE;   break;
	case ES_THROW_DICE:
		mainState = ES_WAIT_PLAYER_INPUT;
		break;

	case ES_AI_INPUT:
		OnAISelectKeyToPress();
		// no break
	case ES_WAIT_PLAYER_INPUT:
		HandlePressedKey();
		break;

	case ES_MOVE_DICE_TO_FIELD:
		OnMoveToField();
		break;

	case ES_DESTROY_DICES:
		OnDestroyDices();
		break;

	case ES_REODER_IN_GROUPS:
		break;

	case ES_UPDATE_SCORE:
		break;
	case ES_CHANGE_ACTIVE_PLAYER:
		break;
	case ES_GAME_END_WIN:
		break;
	case ES_GAME_END_DRAW:
		break;
	case ES_ASK_FOR_RESTART:
		break;
	default:
		break;
	}

	pressedKey = 0;
}

void Game::OnAISelectKeyToPress() {
	assert(players[curPlayerIdx].isAI);

	// for now AI players hit random keys
	pressedKey = '1' + random::Group();
}

void Game::HandlePressedKey() {
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
		mainState = ES_MOVE_DICE_TO_FIELD;
	}
}

void Game::OnMoveToField() {
	// play animation

	// done => next state
	mainState = ES_DESTROY_DICES;
}

void Game::OnDestroyDices() {
	auto diceVal = players[curPlayerIdx].boxDice.GetValue();
	auto& curPlayer = players[curPlayerIdx];

	// tell other players to remove their dices
	for (auto& plr : players) {
		if (!plr.isActive) {
			plr.DestroyDices(diceVal, selectedGroupIdx);
		}
	}
	// end current turn
	curPlayer.isActive = false;

	// loop around
	curPlayerIdx++;
	curPlayerIdx %= countPlayers;

	// check for game end
	for (auto& plr : players) {
		if (plr.isFull) {
			End();
			break;
		}
	}

	// decide next state
	if (players[curPlayerIdx].isAI) {
		mainState = ES_AI_INPUT;
	} else {
		mainState = ES_WAIT_PLAYER_INPUT;
	}
	players[curPlayerIdx].StartTurn();
}

void Game::OnStartup() {

	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, resize_callback);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// tell OpenGL where to render
	glViewport(0, 0, field.WINDOW_WIDTH, field.WINDOW_HEIGHT);

	// bind all players
	for (int i = 0; i < countPlayers; i++) {
		players[i].Bind(&field, i);
	}

	// gfx
	field.PrepareTextures();
	field.PrepareShaders();
	field.EnableTransparancy();

	// debug
	#ifdef FILLSLOTS	
		FillRandomSlots();
	#endif

	// part of game logic
	players[0].isAI = false;
	//players[1].isAI = false;
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
	FillRQueue();
	for (auto rElem : rQueue) {
		rElem->Render();
	}

	// Swap front and back buffers
	glfwSwapBuffers(window);
}

void Game::FillRQueue() {
	rQueue.clear();

	// do we need players?
	if (ES_ANNOUNCE_ROUND < mainState && mainState <= ES_GAME_END_DRAW) {
		for (auto& player : players) {
			rQueue.push_back(&player);
		}
	}

	// 
	// fill render queue depending on main state
	// popup.Render();
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