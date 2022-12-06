#include "game.h"
#include "stb/stb_image.h"
#include "random.h"

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
	FillRandomSlots();

	// part of game logic
	players[0].isAI = false;
	players[0].StartTurn();
}

Game::~Game() {
	if (doneGlfwInit) {
		glfwTerminate();
	}
}

void Game::FillRandomSlots()
{
#ifdef FILLSLOTS	
	for (auto& player : players) {
		player.FillRandomSlots();
	}
#endif // FILLSLOTS
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
	if (ES_ANNOUNCE_ROUND < mainState && mainState < ES_GAME_END_WIN) {
		for (auto& player : players) {
			rQueue.push_back(&player);
		}
	}

	// 
	// fill render queue depending on main state
	// popup.Render();
}

void Game::RunMainLoop() {
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		Render();
		glfwPollEvents();
		Tick();
	}
}
 
Game* Game::_this = nullptr;
void Game::resize_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	_this->Render();
}

void Game::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		_this->pressedKey = key;
	}
	if (key == GLFW_KEY_ESCAPE) {
		 glfwSetWindowShouldClose(window, 1);
	}
}

void Game::Tick() {
	// ai players do random moves
	if (players[curPlayerIdx].isAI) {
		pressedKey = random::randomGroup(random::rng) + '1';
	}

	// player turn
	if ('1' <= pressedKey && pressedKey < '1' + countGroupsPerPlayer) {
		int grIdx = pressedKey - '1';
		
		auto diceVal = players[curPlayerIdx].boxDice.GetValue();
		auto& curPlayer = players[curPlayerIdx];
		if (curPlayer.EndTurn(grIdx)) {
			// tell other players to remove their dices
			for (auto &plr: players ) {
				if (!plr.isActive) {
					plr.DestroyDices(diceVal, grIdx);
				}
			}
			// end current turn
			curPlayer.isActive = false;

			if (true) {

			}

			// loop around
			curPlayerIdx++;
			curPlayerIdx %= countPlayers;

			players[curPlayerIdx].StartTurn();
		}
	}

	if (pressedKey == ' ') {
		mainState = ES_THROW_DICE;
	}

	pressedKey = 0;

}
