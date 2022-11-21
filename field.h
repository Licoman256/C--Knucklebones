#pragma once
#include "player.h"

static const int countPlayers = 2;

class Field {
public:
    void Render();

    static const int WINDOW_WIDTH = 1200;
    static const int WINDOW_HEIGHT = 800;

private:
    float renderPlayerDiceSlots(float xStart, float yStart, const MyColor& color);

    const float xFieldOrigin{ -0.6f };
    const float yFieldOrigin{ 1.0f };
    const float fieldLen{ 1.2f };
    const float fieldHeight{ 2.0f };

    const float xSlotOffsetCoeff{ 0.25f }; // offset to slot ratio
    const float ySlotOffsetCoeff{ 0.25f };
    constexpr float CalcOffset(const float f, const float coeff, const int count) {
        return f * coeff / ((coeff + 1) * count + coeff);
    }
    const float xOffset{ CalcOffset(fieldLen,    xSlotOffsetCoeff, countSlotRowsPerPlayer) };
    const float yOffset{ CalcOffset(fieldHeight, ySlotOffsetCoeff, countSlotColsPerPlayer) / countPlayers };

    const float xSlotOrigin{ xFieldOrigin + xOffset };
    const float ySlotOrigin{ yFieldOrigin - yOffset };
    const float slotLen{ xOffset / xSlotOffsetCoeff };
    const float slotHeight{ yOffset / ySlotOffsetCoeff };
};