#include "game.h"
#include <iostream>
#include "random.h"

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
		glfwPollEvents();

		FillQueues();
		Render();
		OperateFSM();
		Animate();

		// debug
		//Sleep(50);
	}
}
