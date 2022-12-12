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
    E_DICE_1,
    E_DICE_2,
    E_DICE_3,
    E_DICE_4,
    E_DICE_5,
    E_DICE_6,
    E_FIELD,
    E_SLOT,
    E_NUMBERS,
    E_LIGHTNING,
    TEXTURE_LAST
};

const GLsizei COUNT_TEX_NAMES = TEXTURE_LAST;

class RenderElement {
public:
    virtual void Render() = 0;
};
