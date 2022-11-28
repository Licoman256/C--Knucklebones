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

void Game::FillRandomSlots()
{
#ifdef DEBUG	
	for (auto& player : players) {
		player.FillRandomSlots();
	}
#endif // DEBUG
}

Game::~Game()
{ 
	if (doneGlfwInit) {
		glfwTerminate();
	}

}

void Game::RunMainLoop() {
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
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
