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

    GLuint textureNames[COUNT_TEX_NAMES];
    void PrepareTextures();
    void PrepareShaders();
    void EnableTransparancy();

    static const int WINDOW_WIDTH = 1200;
    static const int WINDOW_HEIGHT = 800;
    // Needed to compensate for dimension difference so we can use slotHeight as x coordinate and slotLen as y
    float dimCoef;
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

    const float slotLen   { xOffset / xSlotOffsetCoeff };
    const float slotHeight{ yOffset / ySlotOffsetCoeff };

    const float xBoxOrigin{ xSlotOrigin - (slotLen + 1.5f * xOffset)};

    struct Layout {
        const void* key;
        float   ySlotOrigin;
        float   yBoxOrigin;
        MyColor color;
        Layout() : key(nullptr), ySlotOrigin(0) {}
    } mapLayouts[countPlayers];

    void ClearLayout();
    Layout GetLayout(const void* key);

    void RenderSlot(MyColor& lay, float xCur, float yCur);
    void Render(const Dice& dice, float xCur, float yCur);

    bool ChangeColor(const Dice& dice);
    void ChangeTexture(int idxTx);

    bool LoadTexture(int idxTx, char const* filename);
    void RenderTexture(float xStart, float yStart, float xFinish, float yFinish, const MyColor& color, int idxTx);
};