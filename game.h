#pragma once
//#define FILLSLOTS
#include "render.h"
#include "field.h"

enum MainState {
    ES_STARTUP,
        // within one session:
        ES_ANNOUNCE_ROUND,
            // within a round:
            ES_THROW_DICE,
            ES_WAIT_PLAYER_INPUT,
            ES_MOVE_DICE_TO_FIELD,
            ES_REODER_IN_GROUPS,
            ES_DESTROY_DICES,
            ES_UPDATE_SCORE,
            ES_CHANGE_ACTIVE_PLAYER,
        ES_GAME_END_WIN,
        ES_GAME_END_DRAW,
    ES_ASK_FOR_RESTART
};

class Game {

public:
    Game();
    bool IsFailedOnInit() { return (window == nullptr); }
    void RunMainLoop();
    ~Game();

private:
    // render part
    bool doneGlfwInit = false;
    GLFWwindow* window = nullptr;
    Field field;
    std::deque< RenderElement* > rQueue;
    void Render();
    void FillRQueue();

    // game logic part
    int curPlayerIdx = 0;
    std::vector<Player> players;
    MainState mainState = ES_STARTUP;
    void Tick();

    // UI part
    static Game* _this; // to use within static callbacks
    char pressedKey;
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void resize_callback(GLFWwindow* window, int width, int height);

    // debug
    void FillRandomSlots();
};
