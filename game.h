#pragma once
//#define FILLSLOTS
#include "render.h"
#include "field.h"

enum MainState {
    ES_STARTUP,
        // within one session:
        ES_ANNOUNCE_ROUND,
            ES_BLIND_MOVES,
            // within a round:
            ES_THROW_DICE,
            ES_AI_INPUT,
            ES_WAIT_PLAYER_INPUT,
            ES_MOVE_DICE_TO_FIELD,
            ES_SLOT_SHAKING,
            ES_DESTROY_DICES,
            ES_REODER_IN_GROUPS,
            ES_UPDATE_SCORE,
            ES_CHANGE_ACTIVE_PLAYER,
        ES_GAME_END_WIN,
        ES_GAME_END_DRAW,
    ES_ASK_FOR_RESTART
};

class Game : public Constants {

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
    std::deque< RenderElement* >  renderQ;
    void Render();

    std::deque< Animated* > animQ;
    void Animate();

    // states
    void OnStartup();

    // game logic part
    using Action = int;
    Action selectedGroupIdx = 0;
    int curPlayerIdx = 0;
    std::vector<Player> players;
    MainState mainState = ES_STARTUP;
    float deltaTime = 0.f;

    void FillQueues();
    void OperateFSM();
    void OnThrowDice();
    void AnnounceRound();
    void OnAISelectKeyToPress();
    void HandlePressedKey();
    void OnMoveToField();
    void OnSlotShaking();
    void OnDestroyDices();
    void OnUpdateScore();
    void ChangeActivePlayer();
    void OnReorderInGroups();
    void End();

    // UI part uses static callbacks
    static Game* _this;
    char pressedKey;
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void resize_callback(GLFWwindow* window, int width, int height);

    // debug
    void FillRandomSlots();
};
