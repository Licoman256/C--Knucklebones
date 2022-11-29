#include "game.h"

Game::Game()
	: window(nullptr)
	, players(countPlayers)
{ 
	/* Initialize the library */
	if (!glfwInit())
		return;
	doneGlfwInit = true;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(Field::WINDOW_WIDTH, Field::WINDOW_HEIGHT, "Knucklebones", NULL, NULL);
	if (!window) {
		return;
	}
	glfwSetKeyCallback(window, key_callback);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// tell OpenGL where to render
	glViewport(0, 0, Field::WINDOW_WIDTH, Field::WINDOW_HEIGHT);

	// calc graphic sizes
	for (int i = 0; i < countPlayers; i++) {
		field.AddToLayout(i, players[i]);
	}

	// debug
	FillRandomSlots();

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

void Game::RunMainLoop() {
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		Turn();
		pressedKey = ' ';
		field.RenderCommon();
		for (const auto &player : players) {
			field.Render(player);
		}
		
		// popup.Render();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
		// ui.HandleCommands();
		// Tick();
	}
}

char Game::pressedKey;
void Game::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		pressedKey = key;
	}
}

void Game::Turn() {
	if ('0' <= pressedKey && pressedKey < '0' + countGroupsPerPlayer) {
		if (lastPlayerMoved >= countPlayers) {
			lastPlayerMoved = 0;
		}

		if (players[lastPlayerMoved].Turn(pressedKey - '0')) {
			lastPlayerMoved++;
		}
	}
}
