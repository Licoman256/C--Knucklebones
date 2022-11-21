#include <GLFW/glfw3.h>
#include "game.h"

void Field::Render() {
    //window background
    glClearColor(colors::windowBackground.red, colors::windowBackground.green, colors::windowBackground.blue, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //field background
    glColor3f(colors::fieldBackground.red, colors::fieldBackground.green, colors::fieldBackground.blue);
    glRectf(xFieldOrigin, yFieldOrigin, xFieldOrigin + fieldLen, yFieldOrigin - fieldHeight);

    //slots
    float yStart = ySlotOrigin;
    for (int i = 0; i < countPlayers; i++) {
        //shift start position to y of last slot of prev player
        yStart = renderPlayerDiceSlots(xSlotOrigin, yStart, colors::diceSlot[i]);
        //add additional spacing between players
        yStart -= yOffset;
    }  
}

float Field::renderPlayerDiceSlots(float xStart, float yStart, const MyColor& color) {
    //choose the color of slots
    glColor3f(color.red, color.green, color.blue);

    float yCur = yStart;
    for (int i = 0; i < countSlotColsPerPlayer; i++, yCur -= (slotHeight + yOffset)) {
        float xCur = xStart;
        for (int j = 0; j < countSlotRowsPerPlayer; j++, xCur += (slotLen + xOffset)) {
            //render the slot
            glRectf(xCur,              
                    yCur,              
                    xCur + slotLen,    
                    yCur - slotHeight);
        }
    }
    //return last y coordinate so next player's slots can render there
    return yCur;
}