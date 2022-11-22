#include <GLFW/glfw3.h>
#include "game.h"

void Field::Render(Player **players) {
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
        yStart = RenderPlayerDiceSlots(xSlotOrigin, yStart, colors::diceSlot[i], *players[i]);
        //add additional spacing between players
        yStart -= yOffset;
    }  
}

float Field::RenderPlayerDiceSlots(float xStart, float yStart, const MyColor& color, Player& player) {
    
    float xCur = xStart;
    float yCur;
    for (int i = 0; i < countSlotRowsPerPlayer; i++, xCur += (slotLen + xOffset)) {
        
        yCur = yStart;
        for (int j = 0; j < countSlotColsPerPlayer; j++, yCur -= (slotHeight + yOffset)) {
            //choose the color of slots        
            glColor3f(color.red, color.green, color.blue);
            //render the slot
            glRectf(xCur,              
                    yCur,              
                    xCur + slotLen,    
                    yCur - slotHeight);
            // switch color according to dice value
            switch (player.diceValues[i][j]) {
            case 0:
                break;
            case 1:
                glColor3f(1.0f, 0.0f, 0.0f); // red
                break;
            case 2:
                glColor3f(1.0f, 0.5f, 0.0f); // orange
                break;
            case 3:
                glColor3f(1.0f, 1.0f, 0.0f); // yellow
                break;
            case 4:
                glColor3f(0.0f, 1.0f, 0.0f); // green
                break;
            case 5:
                glColor3f(0.0f, 0.0f, 1.0f); // blue
                break;
            case 6:
                glColor3f(0.65f, 0.0f, 1.0f); // purple
                break;
            default:
                break;
            }
            
            // render dice
            glRectf(xCur + 0.1f,
                    yCur - 0.1f,
                    xCur + slotLen - 0.1f,
                    yCur - slotHeight + 0.1f);
            
        }
    }
    //return last y coordinate so next player's slots can render there
    return yCur;
}
