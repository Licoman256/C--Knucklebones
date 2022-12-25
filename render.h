#pragma once
#include <GLFW/glfw3.h>

struct MyColor {
    float red;
    float green;
    float blue;
    MyColor(float mred = 0, float mgreen = 0, float mblue = 0): 
                  red(mred / 256.0f),
                  green(mgreen / 256.0f),
                  blue(mblue / 256.0f) {}
};

namespace colors {
    // gray
    const MyColor windowBackground { 96, 98, 99};                                     
    // dark blue
    const MyColor fieldBackground { 126, 126, 126};
    
    const MyColor diceSlot[] =  { {177, 99, 101}, // red
                                  {99, 131, 177}, // blue
                                  {163, 177, 99}, // yellow
                                  {160, 99, 177}, // purple
                                  {99, 177, 129}, // green
                                };
    const MyColor white = { 256, 256, 256 };

    const MyColor dicePowers[] = { white,
                                   {177, 99, 101},
                                   {99, 131, 177},
                                   {163, 177, 99},
                                   {160, 99, 177},
                                   {99, 177, 129}
                                  };
};

struct Vert {
    float x; 
    float y;
    float Len(void);
};

enum {
    E_BACKGROUND = 0,
    E_FIELD,
    E_SLOT,
    E_NUMBERS,
    E_LIGHTNING,
    E_DEBUG_YELLOW,
    E_DICE_1,
    E_DICE_2,
    E_DICE_3,
    E_DICE_4,
    E_DICE_5,
    E_DICE_6,
    TEXTURE_LAST
};

const GLsizei COUNT_TEX_NAMES = TEXTURE_LAST;

class Constants {
public:
    const float xFieldOrigin{ -0.6f };
    const float yFieldOrigin{ 1.0f };
    const float fieldLen{ 1.2f };
    const float fieldHeight{ 2.0f };

    const float xSlotOffsetCoeff{ 0.25f }; // offset to slot ratio
    const float ySlotOffsetCoeff{ 0.25f };
    constexpr float CalcOffset(const float f, const float coeff, const int count, int offSetsBetween) {
        return f * coeff / ((coeff + 1) * count + coeff * offSetsBetween);
    }

    static const int countPlayers = 3;
    static const int countGroupsPerPlayer = 4;
    static const int countRowsPerGroup = 3;

    const float xOffset{ CalcOffset(fieldLen,    xSlotOffsetCoeff, countGroupsPerPlayer, 1) };
    const float yOffset{ CalcOffset(fieldHeight, ySlotOffsetCoeff, countRowsPerGroup, 3) / countPlayers };

    const float xSlotOrigin{ xFieldOrigin + xOffset };
    const float ySlotOrigin{ yFieldOrigin - yOffset };

    const float slotLen{ xOffset / xSlotOffsetCoeff };
    const float slotHeight{ yOffset / ySlotOffsetCoeff };
    const float digitLen = xOffset / 2;

    const float xBoxOrigin{ xSlotOrigin - (slotLen + 1.5f * xOffset) };

    const float diceSlotOccupation = 0.8f;

    const float reducedSlotLen = slotLen * diceSlotOccupation;
    const float reducedSlotHeight = slotHeight * diceSlotOccupation;

    const int WINDOW_WIDTH = 1200;
    const int WINDOW_HEIGHT = 800;
};

class Animated {
public:
    virtual void Animate(float deltaTime) = 0;
    virtual bool DoneAnimating() = 0;
    virtual void Reset() = 0;
};

class RenderElement : public Constants {
public:
    virtual void Render() = 0;
};
