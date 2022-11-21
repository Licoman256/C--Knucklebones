#pragma once
#include "render.h"
#include "field.h"

class Game {
public:
    Game();
    bool IsFailedOnInit() { return (window == nullptr); }
    void RunMainLoop();
    ~Game();

private:
    GLFWwindow* window;
    Player* players[countPlayers];
    Field field;
    bool doneGlfwInit = false;

    void InitPlayers();
    void DeletePlayers();
    
};

