#include "game.h"
#include "stb/stb_image.h"

#include <GLFW/glfw3.h>


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

	// calc graphic sizes
	for (int i = 0; i < countPlayers; i++) {
		field.AddToLayout(i, players[i]);
	}

	// gfx
	field.PrepareTextures();
	field.PrepareShaders();

	// debug
	FillRandomSlots();

	// part of game logic
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

float Game::CalcDimCoeff() {
	int height, width;
	glfwGetWindowSize(window, &width, &height);
	return static_cast<float>(height) / static_cast<float>(width);
}

void Game::Render() {
	field.dimCoef = CalcDimCoeff();
	field.RenderCommon();
	for (const auto& player : players) {
		field.Render(player);
	}
	// popup.Render();

	/* Swap front and back buffers */
	glfwSwapBuffers(window);
}

void Game::RunMainLoop() {
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		Render();
		/* Poll for and process events */
		glfwPollEvents();

		// ui.HandleCommands();
		Turn();
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
	if (key == GLFW_KEY_E || key == GLFW_KEY_ESCAPE) {
		 glfwSetWindowShouldClose(window, 1);
	}
}

void Game::Turn() {

	if ('0' <= pressedKey && pressedKey < '0' + countGroupsPerPlayer) {
		int grIdx = pressedKey - '0';
		if (players[curPlayerIdx].EndTurn(grIdx)) {
			// loop around
			curPlayerIdx++;
			curPlayerIdx %= countPlayers;

			players[curPlayerIdx].StartTurn();
		}
	}

	pressedKey = ' ';
}
