#include "game.h"
#include <string>

Field::Field() {
    ClearLayout();
    arc.Bind(this);
    movingDice.Bind(this, &arc);
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
    // Needed to compensate for dimension difference so we can use slotHeight as x coordinate and slotLen as y
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
    Vert start { -1.0, 1.0 };
    Vert finish{ 1.0, -1.0 };
    Vert txStart { 0.0, 0.0 };
    Vert txFinish{ 1.0, 1.0 };
    RenderTexture(start, finish, colors::white, E_BACKGROUND, txStart, txFinish);

    // field background
    start =  { xFieldOrigin,            yFieldOrigin };
    finish = { xFieldOrigin + fieldLen, yFieldOrigin - fieldHeight};
    RenderTexture(start, finish, colors::fieldBackground, E_FIELD, txStart, txFinish);
}

void Field::RenderSlot(MyColor& color, float xCur, float yCur) {

    Vert start  { xCur,           yCur };
    Vert finish { xCur + slotLen, yCur - slotHeight };
    Vert txStart{ 0.0, 0.0 };
    Vert txFinish{ 1.0, 1.0 };
    RenderTexture(start, finish, color, E_SLOT, txStart, txFinish);
}

void Field::ChangeTexture(int idxTx) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureNames[idxTx]);
}

void Field::RenderTexture(Vert &rectangleStart, Vert &rectangleFinish, const MyColor& color, int idxTx, Vert texStart, Vert texFinish) {

    glColor3f(color.red, color.green, color.blue);
    ChangeTexture(idxTx);

    glBegin(GL_QUADS);
        glTexCoord2f(texStart.x,  texStart.y); glVertex2f( rectangleStart.x,  rectangleStart.y);
        glTexCoord2f(texFinish.x, texStart.y); glVertex2f( rectangleFinish.x, rectangleStart.y);
        glTexCoord2f(texFinish.x, texFinish.y); glVertex2f(rectangleFinish.x, rectangleFinish.y);
        glTexCoord2f(texStart.x,  texFinish.y); glVertex2f(rectangleStart.x,  rectangleFinish.y);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void Field::Render(const Player& player) {
    Layout lay = GetLayout(&player);
    float xCur = xSlotOrigin;

    // box
    RenderSlot(lay.color, xBoxOrigin, lay.yBoxOrigin);
    Render(player.totalScore, xBoxOrigin, lay.yBoxOrigin - (slotHeight + yOffset));
    if (player.isActive) {
        Render(player.boxDice, xBoxOrigin, lay.yBoxOrigin);
    }
    
    // all slots
    for (int i = 0; i < countGroupsPerPlayer; i++, xCur += (slotLen + xOffset)) {
        
        float yCur = lay.ySlotOrigin;
        for (int j = 0; j < countRowsPerGroup; j++, yCur -= (slotHeight + yOffset)) {
            RenderSlot(lay.color, xCur, yCur);

            // render dice over the slot
            auto& dice = player.groups[i].dices[j];
            if (dice.CheckIfOnField()) {
                Render(dice, xCur, yCur);
            }
            
        }
        // render group score
        Render(player.groups[i].GetScore(), xCur, yCur);
    }
}

void Field::Render(int score, float xCur, float yCur) {
    // count digits
    float numOfDigits = (score == 0 ? 1.f : 0.f);
    score = abs(score); // handle negative numbers as well
    auto tmpScore = score;
    while (tmpScore > 0) {
        numOfDigits++;
        tmpScore /= 10;
    }

    // process
    Vert texStart{ 0.9f, 0.0f };
    Vert texFinish{ 1.0f, 1.0f };
    const float slotCentre = xCur + slotLen / 2;
    Vert rectangleStart { slotCentre       + digitLen * (numOfDigits / 2 - 1),  yCur };
    Vert rectangleFinish{ rectangleStart.x + digitLen,                          yCur - yOffset };

    tmpScore = score;
    for (int i = 0; i < numOfDigits; i++, tmpScore /= 10) {
        // choose texture coordinates according to char
        texStart.x = 0.1f * (tmpScore % 10);
        texFinish.x = texStart.x + 0.1f;

        // render
        RenderTexture(rectangleStart, rectangleFinish, colors::white, E_NUMBERS, texStart, texFinish);

        // move to next digit
        rectangleStart.x -= digitLen;
        rectangleFinish.x -= digitLen;
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

void Field::Render(const Dice &dice, float slotStartX, float slotStartY) {
    auto value = dice.GetValue();
    if (!value) {
        return;
    }
    int digit = value - 1;

    // shrink the slot
    float reducedSlotLen    = slotLen    * diceSlotOccupation;
    float reducedSlotHeight = slotHeight * diceSlotOccupation;
    float reducedSlotStartX = slotStartX + slotLen    * (1 - diceSlotOccupation) / 2;
    float reducedSlotStartY = slotStartY - slotHeight * (1 - diceSlotOccupation) / 2;

    // select where an offset is
    float diceOffsetX  = (reducedSlotLen - reducedSlotHeight * dimCoef) / 2;
    float diceOffsetY  = (reducedSlotHeight - reducedSlotLen / dimCoef) / 2;
    if (reducedSlotLen > reducedSlotHeight * dimCoef) {
        diceOffsetY   = 0;
    } else {
        diceOffsetX  = 0;
    }

    MyColor color;
    ChangeDiceColor(dice.GetMul(), color);
    Vert start =  { reducedSlotStartX + diceOffsetX,                  reducedSlotStartY - diceOffsetY};
    Vert finish = { reducedSlotStartX - diceOffsetX + reducedSlotLen, reducedSlotStartY + diceOffsetY - reducedSlotHeight };
    Vert txStart{ 0.0, 0.0 };
    Vert txFinish{ 1.0, 1.0 };
    RenderTexture(start, finish, color, E_DICE_1 + digit, txStart, txFinish);
}
