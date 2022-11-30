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

    static Game* _this; // to use within static callbacks
    char pressedKey;

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void resize_callback(GLFWwindow* window, int width, int height);

    void Render();
    int curPlayerIdx = 0;
    void Turn();
    void FillRandomSlots();
};
