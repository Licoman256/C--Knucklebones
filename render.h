#pragma once
#include <GLFW/glfw3.h>

struct MyColor {
    float red;
    float green;
    float blue;
    MyColor(float mred, float mgreen, float mblue): 
                  red(mred / 256.0f),
                  green(mgreen / 256.0f),
                  blue(mblue / 256.0f) {}
};

namespace colors {
    //gray
    const MyColor windowBackground{96, 98, 99};                                     
    //dark blue
    const MyColor fieldBackground {12, 22, 29 };
    
    const MyColor diceSlot[] =  { {177, 99, 101}, // red
                                  {99, 131, 177}, // blue
                                  {163, 177, 99}, // yellow
                                  {160, 99, 177}, // purple
                                  {99, 177, 129}, // green
                                };
}
