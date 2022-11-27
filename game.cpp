#include "game.h"

Game::Game()
	: window(nullptr)
{ 
	// players
	InitPlayers();

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

	// tell opengl where to render
	glViewport(0, 0, Field::WINDOW_WIDTH, Field::WINDOW_HEIGHT);

	// debug
	FillRandomSlots();

}

void Game::FillRandomSlots()
{
#ifdef DEBUG	
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 2; k++) {
				players[k]->AddDice(i, j);
			}
		}
	}
#endif // DEBUG
}

Game::~Game()
{ 
	if (doneGlfwInit) {
		glfwTerminate();
	}

	DeletePlayers(); 
}

void Game::RunMainLoop() {
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		field.RenderCommon();
		for (auto player : players) {
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

void Game::InitPlayers() {
	for (int i = 0; i < countPlayers; i++) {
		players[i] = new Player(countSlotRowsPerPlayer, countSlotColsPerPlayer);
		field.AddToLayout(i, players[i]);
	}
}

void Game::DeletePlayers() {
	for (int i = 0; i < countPlayers; i++) {
		if (players[i]) {
			delete players[i];
			players[i] = nullptr;
		}
	}
}
