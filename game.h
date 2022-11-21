#pragma once
#include "render.h"
#include "field.h"

class Game {
public:
    Game() { InitPlayers(); }
    ~Game() { DeletePlayers(); }
    void Render();

private:
    Player* players[countPlayers];
    Field field;

    void InitPlayers();
    void DeletePlayers();
};

