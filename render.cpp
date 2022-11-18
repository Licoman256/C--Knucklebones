#include <GLFW/glfw3.h>
#include "render.h"
void renderField() {
    //window background
    glClearColor(colors::windowBackgroundRed, colors::windowBackgroundGreen, colors::windowBackgroundBlue, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //field background
    glColor3f(colors::fieldBackgroundRed, colors::fieldBackgroundGreen, colors::fieldBackgroundBlue);
    glRectf(xFieldOrigin, yFieldOrigin, xFieldOrigin + fieldLen, yFieldOrigin - fieldHeight);

    //slots
    renderDiceSlots();
    
}

void renderDiceSlots() {

    glColor3f(colors::diceSlotRed, colors::diceSlotGreen, colors::diceSlotBlue);
    float xCur;
    float yCur = ySlotOrigin;
    //TODO for numberOfPlayers    numberOfSlotRowsPerPlayer
    for (int i = 0; i < numberOfSlotColsPerPlayer; i++) {
        xCur = xSlotOrigin;
        for (int j = 0; j < numberOfSlotRowsPerPlayer; j++) {
            glRectf(xCur,               //x up left
                    yCur,               //y up left
                    xCur + slotLen,     //x down right
                    yCur - slotHeight); //y down right
            
            xCur += (slotLen + xOffset);
        }
        yCur -= (slotHeight + yOffset);

    }

}