#pragma once
//#define FILLSLOTS
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
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static char pressedKey; // TODO add inline
    int lastPlayerMoved = 0;
    void Turn();
    void FillRandomSlots();
};
