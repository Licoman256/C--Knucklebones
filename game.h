#pragma once
//#define FILLSLOTS
#include "render.h"
#include "field.h"

class Game {
public:
    Game();
    bool IsFailedOnInit() { return (window == nullptr); }
    void RunMainLoop();
    float CalcDimCoeff();
    ~Game();

private:
    GLFWwindow* window;
    int curPlayerIdx = 0;
    std::vector<Player> players;
    Field field;
    bool doneGlfwInit = false;

    static Game* _this; // to use within static callbacks
    char pressedKey;

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void resize_callback(GLFWwindow* window, int width, int height);

    void PrepareTextures();
    void PrepareShaders();
    void Render();

    void Turn();
    void FillRandomSlots();
};
