#pragma once
#define DEBUG
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
    std::vector<Player> players;
    Field field;
    bool doneGlfwInit = false;
  
    void FillRandomSlots();
};

