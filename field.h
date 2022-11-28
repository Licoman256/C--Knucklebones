#pragma once
#include "player.h"
#include "render.h"

static const int countPlayers = 2;

class Field {
public:
    Field();
    ~Field();
    void AddToLayout(int idx, const Player &player);
    void RenderCommon();
    void Render(const Player& player);
  
    static const int WINDOW_WIDTH = 1200;
    static const int WINDOW_HEIGHT = 800;

private:

    const float xFieldOrigin{ -0.6f };
    const float yFieldOrigin{ 1.0f };
    const float fieldLen{ 1.2f };
    const float fieldHeight{ 2.0f };

    const float xSlotOffsetCoeff{ 0.25f }; // offset to slot ratio
    const float ySlotOffsetCoeff{ 0.25f };
    constexpr float CalcOffset(const float f, const float coeff, const int count) {
        return f * coeff / ((coeff + 1) * count + coeff);
    }
    const float xOffset{ CalcOffset(fieldLen,    xSlotOffsetCoeff, countGroupsPerPlayer) };
    const float yOffset{ CalcOffset(fieldHeight, ySlotOffsetCoeff, countRowsPerGroup) / countPlayers };

    const float xSlotOrigin{ xFieldOrigin + xOffset };
    const float ySlotOrigin{ yFieldOrigin - yOffset };
    const float slotLen{ xOffset / xSlotOffsetCoeff };
    const float slotHeight{ yOffset / ySlotOffsetCoeff };

    struct Layout {
        const void* key;
        float   yOrigin;
        MyColor color;
        Layout() : key(nullptr), yOrigin(0) {}
    } mapLayouts[countPlayers];

    void ClearLayout();
    Layout GetLayout(const void* key);
    void Render(const Dice& dice, float xCur, float yCur);
};