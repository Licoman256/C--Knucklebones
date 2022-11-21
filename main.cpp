#include "game.h"

int main(void) {

    Game game;
    if (game.IsFailedOnInit()) {
        return -1;
    }
    game.RunMainLoop();

    return 0;
}

