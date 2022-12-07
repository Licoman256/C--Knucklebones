#include "game.h"
#include <iostream>

int main(void) {
    Game game;
    if (game.IsFailedOnInit()) {
        return -1;
    }
    game.RunMainLoop();

    return 0;
}

void Game::RunMainLoop() {
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		Render();
		glfwPollEvents();
		Tick();
	}
}

