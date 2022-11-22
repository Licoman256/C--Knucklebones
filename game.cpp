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

	//tell opengl where to render
	glViewport(0, 0, Field::WINDOW_WIDTH, Field::WINDOW_HEIGHT);
}

Game::~Game()
{ 
	if (doneGlfwInit) {
		glfwTerminate();
	}

	DeletePlayers(); 
}

void Game::RunMainLoop() {
#ifdef DEBUG
{
		//fill all slots with random dices
		std::random_device rd;     // Only used once to initialise (seed) engine
		std::mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
		std::uniform_int_distribution<int> uni(0, 6); // Guaranteed unbiased

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 2; k++) {
					auto random_integer = uni(rng);
					players[k]->AddDice(i, j, random_integer);
				}
			}
		}
}
#endif // DEBUG

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		field.Render(players);
		
		//popup.Render();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
		//ui.HandleCommands();
		//Tick();
	}

}

void Game::InitPlayers() {
	for (int i = 0; i < countPlayers; i++) {
		players[i] = new Player(countSlotRowsPerPlayer, countSlotColsPerPlayer);
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


