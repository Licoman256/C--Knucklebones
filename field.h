#pragma once

#include "player.h"

static const int countPlayers = 3;

class ScreenOffsetsAndSizes {
protected:
    const float xFieldOrigin{ -0.6f };
    const float yFieldOrigin{ 1.0f };
    const float fieldLen{ 1.2f };
    const float fieldHeight{ 2.0f };

    const float xSlotOffsetCoeff{ 0.25f }; // offset to slot ratio
    const float ySlotOffsetCoeff{ 0.25f };
    constexpr float CalcOffset(const float f, const float coeff, const int count, int offSetsBetween) {
        return f * coeff / ((coeff + 1) * count + coeff * offSetsBetween);
    }
    const float xOffset{ CalcOffset(fieldLen,    xSlotOffsetCoeff, countGroupsPerPlayer, 1) };
    const float yOffset{ CalcOffset(fieldHeight, ySlotOffsetCoeff, countRowsPerGroup, 3) / countPlayers };

    const float xSlotOrigin{ xFieldOrigin + xOffset };
    const float ySlotOrigin{ yFieldOrigin - yOffset };

    const float slotLen{ xOffset / xSlotOffsetCoeff };
    const float slotHeight{ yOffset / ySlotOffsetCoeff };

    const float xBoxOrigin{ xSlotOrigin - (slotLen + 1.5f * xOffset) };
};

class Field : public ScreenOffsetsAndSizes {
public:
    Field();
    ~Field();
    void AddToLayout(int idx, const Player &player);
    void RenderCommon(GLFWwindow* window);
    void Render(const Player& player);

    GLuint textureNames[COUNT_TEX_NAMES];
    void PrepareTextures();
    void PrepareShaders();
    void EnableTransparancy();
    void PrepareFont();

    static const int WINDOW_WIDTH = 1200;
    static const int WINDOW_HEIGHT = 800;
private:
    struct Layout {
        const void* key;
        float   ySlotOrigin;
        float   yBoxOrigin;
        MyColor color;
        Layout() : key(nullptr), ySlotOrigin(0) {}
    } mapLayouts[countPlayers];

    void ClearLayout();
    Layout GetLayout(const void* key);

    float dimCoef = 1.f;
    void UpdateDimCoeff(GLFWwindow* window);

    void RenderSlot(MyColor& lay, float xCur, float yCur);
    void Render(const Dice& dice, float xCur, float yCur);

    bool ChangeColor(const Dice& dice); // not used
    void ChangeDiceColor(int pow, MyColor& color);
    void ChangeTexture(int idxTx);

    bool LoadTexture(int idxTx, char const* filename);
    struct Vert {
        float x; float y;
    };
    void RenderTexture(Vert &rectangleStart, Vert &rectangleFinish, const MyColor& color, int idxTx, Vert texStart, Vert texFinish);
};