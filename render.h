void renderField();
float renderPlayerDiceSlots(float xStart, float yStart);

using kFloat = const float;

const int numberOfSlotRowsPerPlayer = 3;
const int numberOfSlotColsPerPlayer = 3;

//const int numberOfSlotsPerPlayer = numberOfSlotRowsPerPlayer * numberOfSlotColsPerPlayer;
const int numberOfPlayers = 2;


const float xFieldOrigin{ -0.6f };
const float yFieldOrigin{ 1.0f };

const float fieldLen    { 1.2f };
const float fieldHeight { 2.0f };


const float xSlotOffsetCoeff  { 0.25f }; //const
const float ySlotOffsetCoeff  { 0.85f }; //const

constexpr float CalcOffset(const float f, const float coeff, const float numberOf) {
    return f * coeff / ((coeff + 1) * numberOf + coeff);
}

const float xOffset{ CalcOffset(fieldLen,    xSlotOffsetCoeff, numberOfSlotRowsPerPlayer) };
const float yOffset{ CalcOffset(fieldHeight, ySlotOffsetCoeff, numberOfSlotColsPerPlayer) / numberOfPlayers };


const float xSlotOrigin { xFieldOrigin + xOffset};
const float ySlotOrigin { yFieldOrigin - yOffset };

const float slotLen     { xOffset / xSlotOffsetCoeff };
const float slotHeight  { yOffset / ySlotOffsetCoeff };
                    

namespace colors {
    const float windowBackgroundRed   { 96.0f / 256.0f };
    const float windowBackgroundGreen { 98.0f / 256.0f };
    const float windowBackgroundBlue  { 99.0f / 256.0f };
                                      
    const float fieldBackgroundRed    { 0.07f };
    const float fieldBackgroundGreen  { 0.13f };
    const float fieldBackgroundBlue   { 0.17f };

    const float diceSlotRed           { 170.0f / 256.0f };
    const float diceSlotGreen         { 170.0f / 256.0f };
    const float diceSlotBlue          { 170.0f / 256.0f };
}