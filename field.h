#pragma once

#include "player.h"
#include "LightArc.h"
#include "ShakingSlot.h"

// Texture Dictionary
class TexDic {
public:
    int dummy;

};

class Field : public Constants, public TexDic {
public:
    Field();
    ~Field();
    GLFWwindow* CreateWindow();
    void AddToLayout(int idx, const Player &player);
   
    void RenderCommon(GLFWwindow* window);
    void Render(const Player& player);
    void Render(const Dice& dice, float xCur, float yCur);
    void RenderSlot(MyColor& color, float xCur, float yCur, float slLen, float slHeight);
    Vert GetSlotCoords(int groupIdx, int rowIdx, float ySlOrigin);

    LightArc arc;
    MovingDice movingDice;
    ShakingSlot shakingSlot;

    GLuint textureNames[COUNT_TEX_NAMES];
    void StartupTextures();
    void LoadMainBlockTex();
    void PrepareShaders();
    void EnableTransparancy();
    void PrepareFont();
    void PrepareArc(Player& player);
    bool DoneShaking();

    void ChangeTexture(int idxTx);
    void RenderTexture(Vert& rectangleStart, 
                       Vert& rectangleFinish, 
                       const MyColor& color, 
                       int idxTx, 
                       Vert texStart  = { 0, 0 },
                       Vert texFinish = { 1, 1 }  );
private:
    struct Layout {
        const void* key;
        float   ySlotOrigin;
        float   yBoxOrigin;
        MyColor color;
        Layout() : key(nullptr), ySlotOrigin(0) {}
    };
    std::vector<Layout> mapLayouts;

    void ClearLayout();
    Layout GetLayout(const void* key);

    float dimCoef = 1.f;
    void UpdateDimCoeff(GLFWwindow* window);

    void Render(int score, float xCur, float yCur);

    bool ChangeColor(const Dice& dice); // not used
    void ChangeDiceColor(int pow, MyColor& color);

    bool LoadTexture(int idxTx, char const* filename);
};