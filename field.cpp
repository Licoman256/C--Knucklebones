#include <GLFW/glfw3.h>
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
                - yOffset;
    }

    // left box depends on slot
    mapLayouts[idx].yBoxOrigin =
        mapLayouts[idx].ySlotOrigin
        - (slotHeight + yOffset) * (countRowsPerGroup - 1) / 2;
}

void Field::RenderCommon() {
    // window background
    glClearColor(colors::windowBackground.red, colors::windowBackground.green, colors::windowBackground.blue, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // field background
    glColor3f(colors::fieldBackground.red, colors::fieldBackground.green, colors::fieldBackground.blue);
    glRectf(xFieldOrigin, yFieldOrigin, xFieldOrigin + fieldLen, yFieldOrigin - fieldHeight);
}

void Field::RenderSlot(MyColor& color, float xCur, float yCur) {
    glColor3f(color.red, color.green,color.blue);
    glRectf(xCur, yCur,
            xCur + slotLen, yCur - slotHeight);
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

void Field::Render(const Dice &dice, float xCur, float yCur) {
    // switch color according to dice value
    switch (dice.GetValue()) {
    case 0:
        return;
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

    glRectf(xCur + 0.1f,
            yCur - 0.1f,
            xCur + slotLen - 0.1f,
            yCur - slotHeight + 0.1f);
}
