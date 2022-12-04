#include "game.h"

Field::Field() {
    ClearLayout();
}
Field::~Field() {
    // may call ClearLayout();
}

void Field::ClearLayout()
{
    for (auto layout : mapLayouts) {
        layout.key = nullptr;
        layout.ySlotOrigin = 0.f;
    }
}

Field::Layout Field::GetLayout(const void* p) {
    for (const auto layout : mapLayouts) {
        if (layout.key == p) {
            return layout;
        }
    }
    return Layout();
}

void Field::AddToLayout(int idx, const Player& player) {
    // safety
    if (idx < 0 || countPlayers <= idx) {
        return;
    }

    // place
    mapLayouts[idx].key = &player;
    mapLayouts[idx].color = colors::diceSlot[idx];

    // origin calc
    switch(idx) {
        case 0:
            mapLayouts[idx].ySlotOrigin = ySlotOrigin;
            break;
        default:
            mapLayouts[idx].ySlotOrigin = 
                mapLayouts[idx-1].ySlotOrigin 
                - (slotHeight + yOffset) * countRowsPerGroup
                - yOffset * 3;
    }

    // left box depends on slot
    mapLayouts[idx].yBoxOrigin =
        mapLayouts[idx].ySlotOrigin
        - (slotHeight + yOffset) * (countRowsPerGroup - 1) / 2;
}

void Field::UpdateDimCoeff(GLFWwindow* window) {
    int height, width;
    glfwGetWindowSize(window, &width, &height);
    dimCoef = static_cast<float>(height) / static_cast<float>(width);
}

void Field::RenderCommon(GLFWwindow* window) {
    // dimensions
    UpdateDimCoeff(window);

    // clear prev frame
    glClearColor(colors::windowBackground.red, colors::windowBackground.green, colors::windowBackground.blue, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // window background
    RenderTexture(-1.0, 1.0, 1.0, -1.0, colors::white, E_BACKGROUND);

    // field background
    RenderTexture(xFieldOrigin, yFieldOrigin, xFieldOrigin + fieldLen, yFieldOrigin - fieldHeight, colors::fieldBackground, E_FIELD);
}

void Field::RenderSlot(MyColor& color, float xCur, float yCur) {

    float xStart  = xCur;
    float yStart  = yCur;
    float xFinish = xCur + slotLen;
    float yFinish = yCur - slotHeight;

    RenderTexture(xStart, yStart, xFinish, yFinish, color, E_SLOT);
}

void Field::ChangeTexture(int idxTx) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureNames[idxTx]);
}

void Field::RenderTexture(float xStart, float yStart, float xFinish, float yFinish, const MyColor& color, int idxTx) {

    glColor3f(color.red, color.green, color.blue);
    ChangeTexture(idxTx);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0); glVertex2f(xStart, yStart);
        glTexCoord2f(1.0, 0.0); glVertex2f(xFinish, yStart);
        glTexCoord2f(1.0, 1.0); glVertex2f(xFinish, yFinish);
        glTexCoord2f(0.0, 1.0); glVertex2f(xStart, yFinish);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void Field::Render(const Player& player) {
    Layout lay = GetLayout(&player);
    float xCur = xSlotOrigin;
    RenderSlot(lay.color, xBoxOrigin, lay.yBoxOrigin);

    if (player.isActive) {
        Render(player.boxDice, xBoxOrigin, lay.yBoxOrigin);
    }

    for (int i = 0; i < countGroupsPerPlayer; i++, xCur += (slotLen + xOffset)) {
        
        float yCur = lay.ySlotOrigin;
        for (int j = 0; j < countRowsPerGroup; j++, yCur -= (slotHeight + yOffset)) {
            RenderSlot(lay.color, xCur, yCur);

            // render dice over the slot
            Render(player.groups[i].dices[j], xCur, yCur);
        }
    }
}

bool Field::ChangeColor(const Dice& dice) {
    // switch color according to dice value
    switch (dice.GetValue()) {
    case 0:
        return false;
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
    return true;
}

void Field::ChangeDiceColor(int pow, MyColor& color) {
    color = colors::dicePowers[pow - 1];
}

void Field::Render(const Dice &dice, float xCur, float yCur) {
    auto value = dice.GetValue();
    if (!value) {
        return;
    }

    float leftDiceOffset  = (slotLen    - slotHeight * dimCoef) / 2;
    float rightDiceOffset = (slotLen    + slotHeight * dimCoef) / 2 - slotLen;
    float upDiceOffset    = (slotHeight - slotLen    / dimCoef) / 2;
    float downDiceOffset  = (slotHeight + slotLen    / dimCoef) / 2 - slotHeight;

    if (slotLen > slotHeight * dimCoef) {
        upDiceOffset   = 0;
        downDiceOffset = 0;

    } else {
        leftDiceOffset  = 0;
        rightDiceOffset = 0;   
    }

    float xStart = xCur + leftDiceOffset;
    float yStart = yCur - upDiceOffset;
    float xFinish = xCur + rightDiceOffset + slotLen;
    float yFinish = yCur - downDiceOffset - slotHeight;

    int shift = value - 1;
    MyColor color;
    ChangeDiceColor(dice.GetPower(), color);
    RenderTexture(xStart, yStart, xFinish, yFinish, color, E_DICE_1 + shift);

}
