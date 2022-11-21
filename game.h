#pragma once
#include "player.h"
#include "render.h"

class Game {
public:
    Game() { InitPlayers(); }
    ~Game() { DeletePlayers(); }
    void render();
    void renderField();
    float renderPlayerDiceSlots(float xStart, float yStart, const MyColor& color);
    const int WINDOW_WIDTH = 1200;
    const int WINDOW_HEIGHT = 800;

    static const int numberOfPlayers = 2;
    void InitPlayers();
    void DeletePlayers();
    Player* players[numberOfPlayers];
private:
    const int numberOfSlotRowsPerPlayer = 3;
    const int numberOfSlotColsPerPlayer = 3;

    const float xFieldOrigin{ -0.6f };
    const float yFieldOrigin{ 1.0f };
    const float fieldLen{ 1.2f };
    const float fieldHeight{ 2.0f };

    const float xSlotOffsetCoeff{ 0.25f }; // offset to slot ratio
    const float ySlotOffsetCoeff{ 0.25f };
    constexpr float CalcOffset(const float f, const float coeff, const int numberOf) {
        return f * coeff / ((coeff + 1) * numberOf + coeff);
    }
    const float xOffset{ CalcOffset(fieldLen,    xSlotOffsetCoeff, numberOfSlotRowsPerPlayer) };
    const float yOffset{ CalcOffset(fieldHeight, ySlotOffsetCoeff, numberOfSlotColsPerPlayer) / numberOfPlayers };

    const float xSlotOrigin{ xFieldOrigin + xOffset };
    const float ySlotOrigin{ yFieldOrigin - yOffset };
    const float slotLen{ xOffset / xSlotOffsetCoeff };
    const float slotHeight{ yOffset / ySlotOffsetCoeff };
};